#ifndef WARBLER_AST_STATEMENT_DECLARATION_STATEMENT_HPP
#define WARBLER_AST_STATEMENT_DECLARATION_STATEMENT_HPP

// local headers
#include <warbler/ast/identifier.hpp>
#include <warbler/ast/typename.hpp>
#include <warbler/ast/expression/conditional_expression.hpp>
#include <warbler/ast/statement/statement.hpp>

namespace warbler::ast
{
	class DeclarationStatement : public Statement
	{
	private:

		Identifier _name;
		Typename _type;
		ConditionalExpression _value;

	public:

		DeclarationStatement(Identifier&& name, Typename&& type, ConditionalExpression&& value);

		static Result<DeclarationStatement> parse(TokenIterator& iter);

		bool validate(semantics::Context& context);
		void print_tree(u32 depth = 0) const;
	};
}

#endif
