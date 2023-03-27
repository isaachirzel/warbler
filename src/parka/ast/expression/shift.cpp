#include "parka/ast/expression/shift.hpp"
#include "parka/ast/expression/additive.hpp"
#include "parka/entity/node_bank.hpp"

Optional<BitShiftType> parseBitShiftType(Token& token)
{
	switch (token.type())
	{
		case TokenType::LeftBitShift:
			return BitShiftType::Left;

		case TokenType::RightBitShift:
			return BitShiftType::Right;

		default:
			return {};
	}
}

Optional<ExpressionId> BitShiftExpression::parse(Token& token)
{
	auto lhs = AdditiveExpression::parse(token);

	if (!lhs)
		return {};

	auto type = parseBitShiftType(token);

	while (type)
	{
		token.increment();

		auto rhs = AdditiveExpression::parse(token);

		if (!rhs)
			return {};

		auto expression = BitShiftExpression(lhs.unwrap(), rhs.unwrap(), type.unwrap());
		auto id = NodeBank::add(std::move(expression));

		lhs = std::move(id);
		type = parseBitShiftType(token);
	}

	return lhs;
}
