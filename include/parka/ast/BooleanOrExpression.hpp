#ifndef PARKA_SYNTAX_EXPRESSION_BOOLEAN_OR_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_BOOLEAN_OR_SYNTAX_HPP

#include "parka/ast/Expression.hpp"

namespace parka
{
	class BooleanOrExpressionSyntax : public ExpressionSyntax
	{
		Snippet _snippet;
		ExpressionSyntax& _lhs;
		ExpressionSyntax& _rhs;

	public:

		BooleanOrExpressionSyntax(ExpressionSyntax& lhs, ExpressionSyntax& rhs) :
		_snippet(lhs.snippet() + rhs.snippet()),
		_lhs(lhs),
		_rhs(rhs)
		{}
		BooleanOrExpressionSyntax(BooleanOrExpressionSyntax&&) = default;
		BooleanOrExpressionSyntax(const BooleanOrExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::BooleanOr; }
		const Snippet& snippet() const { return _snippet; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
