#include <warbler/ast/expression/bitwise_and_expression.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <cstdlib>
#include <cassert>

namespace warbler
{
	BitwiseAndExpression::BitwiseAndExpression(EqualityExpression&& lhs, std::vector<EqualityExpression>&& rhs) :
	_lhs(lhs),
	_rhs(rhs)
	{}

	Result<BitwiseAndExpression> BitwiseAndExpression::parse(TokenIterator& iter)
	{
		auto lhs = EqualityExpression::parse(iter);

		std::vector<EqualityExpression> rhs;

		while (iter->type() == TOKEN_AMPERSAND)
		{
			iter += 1;

			auto res = EqualityExpression::parse(iter);
			
			if (res.has_error())
				return res.error();

			rhs.emplace_back(res.unwrap());
		}

		return BitwiseAndExpression(lhs.unwrap(), std::move(rhs));
	}

	void BitwiseAndExpression::print_tree(u32 depth) const
	{
		if (_rhs.size() > 0)
			depth += 1;

		_lhs.print_tree(depth);

		for (const auto& rhs : _rhs)
		{
			std::cout << tree_branch(depth - 1) << "&\n";
			rhs.print_tree(depth);
		}
	}
}
