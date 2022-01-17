#include <warbler/ast/expression/equality_expression.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <cstdlib>
#include <cassert>

namespace warbler
{
	EqualityExpression::EqualityExpression(ComparisonExpression&& lhs, std::vector<EqualityRhs>&& rhs) :
	_lhs(lhs),
	_rhs(rhs)
	{}

	EqualityExpression::EqualityExpression(EqualityExpression&& other) :
	_lhs(std::move(other._lhs)),
	_rhs(std::move(other._rhs))
	{}

	EqualityExpression::EqualityExpression(const EqualityExpression& other) :
	_lhs(other._lhs),
	_rhs(other._rhs)
	{}


	Result<EqualityExpression> EqualityExpression::parse(TokenIterator& iter)
	{
		auto lhs = ComparisonExpression::parse(iter);

		if (lhs.has_error())
			return lhs.error();

		std::vector<EqualityRhs> rhs;

		while (true)
		{
			bool should_break = false;

			EqualityType type;
			switch (iter->type())
			{
				case TOKEN_EQUALS:
					type = EQUALITY_EQUALS;
					break;

				case TOKEN_NOT_EQUALS:
					type = EQUALITY_NOT_EQUALS;
					break;

				default:
					should_break = true;
					break;
			}

			if (should_break)
				break;

			iter += 1;

			auto res = ComparisonExpression::parse(iter);

			if (res.has_error())
				return res.error();

			rhs.emplace_back(EqualityRhs { res.unwrap(), type });
		}

		return EqualityExpression(lhs.unwrap(), std::move(rhs));
	}

	void EqualityExpression::print_tree(u32 depth) const
	{
		if (_rhs.size() > 0)
			depth += 1;

		_lhs.print_tree(depth);

		for (const auto& rhs : _rhs)
		{
			const char *symbol = rhs.type == EQUALITY_EQUALS
				? "==\n"
				: "!=\n";

			std::cout << tree_branch(depth - 1) << symbol;
			rhs.expr.print_tree(depth);
		}
	}
}
