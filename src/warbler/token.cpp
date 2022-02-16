#include <warbler/token.hpp>

// standard headers
#include <cstdio>
#include <cassert>

namespace warbler
{
	Token::Token() :
	_location("<no file>", ""),
	_type(TOKEN_END_OF_FILE)
	{}

	Token::Token(const Location& location, TokenType type, usize length) :
	_location(location.with_length(length)),
	_type(type)
	{}

	Location::Location() : Location("<no file>", "") {}

	Location::Location(const char *filename, const char *src, usize line, usize col, usize pos, usize length) :
	_filename(filename),
	_src(src),
	_line(line),
	_col(col),
	_pos(pos),
	_length(length)
	{}

	Location::Location(const char *filename, const char *src) :
	_filename(filename),
	_src(src),
	_line(0),
	_col(0),
	_pos(0),
	_length(0)
	{}

	Location Location::with_length(usize length) const
	{
		return { _filename, _src, _line, _col, _pos, length };
	}

	void Location::offset(usize offset)
	{
		_col += offset;
		_pos += offset;
	}

	Location::operator String() const
	{
		return String(pos_ptr(), length());
	}

	std::ostream& operator<<(std::ostream& out, const Location& location)
	{
		for (auto c : location)
			out << c;

		return out;
	}

	std::ostream& operator<<(std::ostream& out, const Token& token)
	{
		if (token._type == TOKEN_END_OF_FILE)
		{
			out << "<end of file>";
		}
		else
		{
			out << token.location();
		}

		return out;
	}
}
