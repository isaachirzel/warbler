#ifndef PARKA_SYNTAX_STATMENT_EXPRESSION_SYNTAX_HPP
#define PARKA_SYNTAX_STATMENT_EXPRESSION_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/StatementSyntax.hpp"
#include "parka/Token.hpp"
#include "parka/util/Optional.hpp"

#include <utility>

namespace parka
{
	class ExpressionStatementSyntax : public StatementSyntax
	{
		ExpressionSyntaxId _expression;

		ExpressionStatementSyntax(ExpressionSyntaxId&& expression) :
		_expression(std::move(expression))
		{}

	public:

		ExpressionStatementSyntax(ExpressionStatementSyntax&&) = default;
		ExpressionStatementSyntax(const ExpressionStatementSyntax&) = delete;

		static Optional<StatementSyntaxId> parse(Token& token);

		const auto& expression() const { return _expression; }
		StatementType statementType() const { return StatementType::Expression; }
	};
}

#endif
