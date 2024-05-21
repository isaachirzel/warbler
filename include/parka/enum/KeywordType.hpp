#ifndef PARKA_ENUM_KEYWORD_TYPE_HPP
#define PARKA_ENUM_KEYWORD_TYPE_HPP

#include "parka/util/String.hpp"

namespace parka
{
	enum class KeywordType
	{
		None,
		Break,
		Case,
		Continue,
		Yield,
		Else,
		Enum,
		Export,
		False,
		For,
		In,
		Function,
		Operator,
		If,
		Import,
		Loop,
		Match,
		Mut,
		Private,
		Public,
		Return,
		Struct,
		Then,
		True,
		Type,
		Var,
		While,
		As
	};

	KeywordType toKeywordType(const char* text, usize length);
	KeywordType toKeywordType(const String& text);

	std::ostream& operator<<(std::ostream& out, const KeywordType& type);
}

#endif
