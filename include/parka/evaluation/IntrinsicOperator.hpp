#ifndef PARKA_EVALUATION_INTRINSIC_OPERATOR_HPP
#define PARKA_EVALUATION_INTRINSIC_OPERATOR_HPP

#include "parka/evaluation/LocalState.hpp"
#include "parka/evaluation/Value.hpp"

namespace parka::evaluation
{
	using IntrinsicOperator = std::function<Value& (Value& left, Value& right, LocalState& state)>;

	extern IntrinsicOperator intrinsicOperators[];
	extern const usize intrinsicOperatorCount;
}

#endif
