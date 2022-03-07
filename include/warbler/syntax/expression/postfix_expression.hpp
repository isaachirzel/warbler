#ifndef WARBLER_SYNTAX_EXPRESSION_POSTFIX_EXRESSION_HPP
#define WARBLER_SYNTAX_EXPRESSION_POSTFIX_EXRESSION_HPP

#include <warbler/syntax/expression/expression.hpp>
#include <warbler/syntax/identifier.hpp>
#include <warbler/util/ptr.hpp>

namespace warbler::syntax
{
	enum class PostfixType
	{
		Index,
		FunctionCall,
		Member
	};

	class PostfixExpression : public Expression
	{
	private:

		Ptr<Expression> _expression;

		union
		{
			Ptr<Expression> _index;
			Array<Ptr<Expression>> _arguments;
			Identifier _member;
		};

		PostfixType _type;

	public:

		PostfixExpression(Ptr<Expression>&& expression, Ptr<Expression>&& index);
		PostfixExpression(Ptr<Expression>&& expression, Array<Ptr<Expression>>&& arguments);
		PostfixExpression(Ptr<Expression>&& expression, Identifier&& member);
		PostfixExpression(PostfixExpression&& other);
		PostfixExpression(const PostfixExpression& other) = delete;
		~PostfixExpression();
		
		static Result<Ptr<Expression>> parse(lexicon::Token& token);

		bool validate(semantics::SymbolTable& symbols);
		Type *get_type();
		const lexicon::Token& token() const;
		void print_tree(u32 depth = 0) const;
	};
}

#endif
