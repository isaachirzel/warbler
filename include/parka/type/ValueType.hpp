#ifndef PARKA_TYPE_VALUE_TYPE_HPP
#define PARKA_TYPE_VALUE_TYPE_HPP

#include "parka/util/Common.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/String.hpp"

namespace parka
{
	struct EntityContext;

	class ValueType
	{
	private:

		EntityContext& _entity;
		// TODO: Add pointer info
		// TODO: Add LiteralSyntax for better type inference?
		
	public:

		static const ValueType voidType;
		static const ValueType u8Type;
		static const ValueType u16Type;
		static const ValueType u32Type;
		static const ValueType u64Type;
		static const ValueType i8Type;
		static const ValueType i16Type;
		static const ValueType i32Type;
		static const ValueType i64Type;
		static const ValueType f32Type;
		static const ValueType f64Type;
		static const ValueType boolType;
		static const ValueType charType;
		static const ValueType stringType;
		
	public:

		ValueType(EntityContext& entity);
		ValueType(ValueType&&) = default;
		ValueType(const ValueType&) = default;

		bool canConvertTo(const ValueType& other) const;

		friend std::ostream& operator<<(std::ostream& out, const ValueType& type);
	};
}

#endif