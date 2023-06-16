#include "parka/ast/Member.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/ast/Keyword.hpp"
#include "parka/ast/TypeAnnotation.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	static bool parsePublicity(Token& token)
	{
		auto keywordType = KeywordSyntax::getKeywordType(token);

		if (keywordType == KeywordType::Public)
		{
			token.increment();
			return true;
		}

		if (keywordType == KeywordType::Private)
			token.increment();
		
		return false;
	}

	MemberSyntax *MemberSyntax::parse(Token& token)
	{
		auto first = Snippet(token);
		bool isPublic = parsePublicity(token);

		auto identifier = Identifier::parse(token);

		if (!identifier)
			return {};

		if (token.type() != TokenType::Colon)
		{
			log::parseError(token, "':''", "ValueType annotations are required for member declarations.");
			return {};
		}
		
		token.increment();

		auto annotation = TypeAnnotationSyntax::parse(token);

		if (!annotation)
			return {};
			
		auto snippet = first + annotation->snippet();
		auto *syntax = new MemberSyntax(snippet, *identifier, *annotation, isPublic);

		return syntax;
	}

	bool MemberSyntax::declareSelf(SymbolTable& parent)
	{
		_parent = &parent;

		return parent.declare(*this);
	}

	MemberContext *MemberSyntax::validate()
	{
		log::notImplemented(here());
	}

	String MemberSyntax::getSymbol() const
	{
		// TODO: Differentiate between static and regular

		return name();
	}
}
