#ifndef PARKA_SYNTAX_EXPRESSION_LITERAL_STRING_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_LITERAL_STRING_SYNTAX_HPP

#include "parka/ast/Expression.hpp"

namespace parka
{
	class StringLiteralContext : public ExpressionContext
	{
		String _value;

	public:

		StringLiteralContext(String&& value) :
		_value(std::move(value))
		{}
		StringLiteralContext(StringLiteralContext&&) = default;
		StringLiteralContext(const StringLiteralContext&) = delete;

		ExpressionType expressionType() const { return ExpressionType::StringLiteral; }
		const ValueType& valueType() const { return ValueType::stringType; }
		const auto& value() const { return _value; }
	};

	class StringLiteralSyntax : public ExpressionSyntax
	{
		Snippet _snippet;

	public:

		StringLiteralSyntax(const Snippet& snippet) :
		_snippet(snippet)
		{}
		StringLiteralSyntax(StringLiteralSyntax&&) = default;
		StringLiteralSyntax(const StringLiteralSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);
		
		ExpressionType expressionType() const { return ExpressionType::StringLiteral; }
		const Snippet& snippet() const { return _snippet; }
	};
}

#endif
