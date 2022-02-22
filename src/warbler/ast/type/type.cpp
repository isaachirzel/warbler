#include <warbler/ast/type/type.hpp>

#include <warbler/print.hpp>

namespace warbler::ast
{
	Type::Type(Identifier&& name, Ptr<TypeDefinition>&& definition) :
	_name(std::move(name)),
	_definition(std::move(definition))
	{}

	Result<Type> Type::parse(TokenIterator& iter)
	{
		// skip 'type' keyword
		iter += 1;

		auto name = Identifier::parse(iter);

		if (!name)
			return {};

		if (iter->type() != TOKEN_COLON)
		{
			parse_error(iter, "':' after type name");
			return {};
		}

		iter += 1;

		auto definition = TypeDefinition::parse(iter);

		if (!definition)
			return {};

		return Type { name.unwrap(), definition.unwrap() };
	}

	bool Type::validate(semantics::ModuleContext& mod_ctx)
	{
		_context.name = _name.text();

		return _definition->validate(mod_ctx, _context);
	}

	void Type::print_tree(u32 depth) const
	{
		std::cout << "type " << _name.text() << ":\n";
		_definition->print_tree(depth + 1);
	}	

	Member *Type::get_member(const String& member_name) const
	{
		auto iter = _context.members.find(member_name);

		return iter != _context.members.end()
			? iter->second
			: nullptr;
	}
}
