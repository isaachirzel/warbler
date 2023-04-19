#include "parka/syntax/StringLiteralSyntax.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	Optional<ExpressionSyntaxId> StringLiteralSyntax::parse(Token& token)
	{
		if (token.type() != TokenType::StringLiteralSyntax)
		{
			printParseError(token, "string");
			return {};
		}

		auto literal = StringLiteralSyntax(token, token.text());
		auto id = ExpressionSyntaxId::create(std::move(literal));

		token.increment();

		return id;
	}
}
