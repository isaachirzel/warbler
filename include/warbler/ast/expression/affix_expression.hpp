#ifndef WARBLER_AST_PRIMARY_EXPRESSION_HPP
#define WARBLER_AST_PRIMARY_EXPRESSION_HPP

// local headers
#include <warbler/ast/expression/prefix.hpp>
#include <warbler/ast/expression/postfix.hpp>

namespace warbler::ast
{
	class AffixExpression
	{
	private:

		Array<Prefix> _prefixes;
		Ptr<Expression> _expression;
		Array<Postfix> _postfixes;

	public:

		AffixExpression() = delete;
		AffixExpression(Array<Prefix>&& prefixes, Ptr<Expression>&& expression, Array<Postfix>&& postfixes);
		AffixExpression(AffixExpression&& other) = default;
		AffixExpression(const AffixExpression&) = delete;

		static Result<AffixExpression> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx, bool expect_lvalue = false);
		Type *get_type(semantics::ModuleContext& mod_ctx) const;
		const Location& location() const;
		void print_tree(u32 depth = 0) const;

		AffixExpression& operator=(AffixExpression&& other) = default;
		AffixExpression& operator=(const AffixExpression&) = delete;
	};
}
#endif
