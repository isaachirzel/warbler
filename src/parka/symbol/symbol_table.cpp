#include "parka/symbol/symbol_table.hpp"
#include "parka/ast/primitive.hpp"
#include "parka/entity/entity.hpp"
#include "parka/entity/node_bank.hpp"
#include "parka/util/print.hpp"

#include <cstdlib>
#include <cassert>
#include <cstring>


bool SymbolTable::declareGlobal(EntityId id)
{
	// TODO: Add tokens for highlighting
	auto& entity = NodeBank::get(id);
	const auto& symbol = entity.symbol();
	auto result = _globalSymbols.insert({ symbol,  id });

	if (!result.second)
	{
		// TODO: get previous entity
		auto previousId = result.first->second;
		auto& previous = NodeBank::get(previousId);

		//TODO: invalidate entity previous.invalidate();

		printError( "'%s' is already declared in this package.", symbol.c_str());
	}

	return result.second;
}

bool SymbolTable::declareLocal(EntityId id)
{
	auto& entity = NodeBank::get(id);
	usize blockIndex = _blocks.length() > 0
		? _blocks.back()
		: 0;
	
	usize i = _localSymbols.length();

	while (i > blockIndex)
	{
		i -= 1;

		auto previousId = _localSymbols[i];
		auto& previous = NodeBank::get(previousId);

		if (entity.symbol() == previous.symbol())
			return false;
		// TODO: Invalidate entity
	}

	return true;
}

Optional<EntityId> SymbolTable::resolve(const Token& token)
{
	// TODO: Optimize
	auto identifier = token.text();

	usize i = _localSymbols.length();

	while (i > 0)
	{
		i -= 1;

		auto id = _localSymbols[i];
		auto& entity = NodeBank::get(id);

		if (token == entity.symbol())
			return id;
	}

	i = _scope.count();

	while (i > 0)
	{
		i -= 1;

		auto symbol = _scope.createSymbolN(identifier, i);
		auto iter = _globalSymbols.find(symbol);

		if (iter != _globalSymbols.end())
			return EntityId(iter->second);
	}

	printTokenError(token, "Unable to find '%s' in this scope.", identifier.c_str());

	return {};
}

void SymbolTable::setScope(const String& symbol)
{
	_scope = Scope::from(symbol);
}

void SymbolTable::clearLocalSymbols()
{
	_blocks.clear();
	_localSymbols.clear();
}

void SymbolTable::pushBlock()
{
	auto offset = _localSymbols.length();

	_blocks.push(offset);
}

void SymbolTable::popBlock()
{
	_blocks.pop();
}
