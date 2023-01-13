#ifndef WARBLER_TYPE_H
#define WARBLER_TYPE_H



typedef enum OperatorType
{
	OPERATOR_PLUS
} OperatorType;

typedef enum AssignmentType
{
	ASSIGNMENT_BECOME,
	ASSIGNMENT_MULTIPLY,
	ASSIGNMENT_DIVIDE,
	ASSIGNMENT_MODULUS,
	ASSIGNMENT_ADD,
	ASSIGNMENT_SUBTRACT,
	ASSIGNMENT_LEFT_BIT_SHIFT,
	ASSIGNMENT_RIGHT_BIT_SHIFT,
	ASSIGNMENT_BITWISE_AND,
	ASSIGNMENT_BITWISE_OR,
	ASSIGNMENT_BITWISE_XOR
} AssignmentType;

typedef enum IfType
{
	IF_THEN,
	IF_THEN_ELSE,
	IF_THEN_ELSE_IF
} IfType;

typedef enum LoopType
{
	LOOP_FOR,
	LOOP_WHILE,
	LOOP
} LoopType;

typedef enum JumpType
{
	JUMP_CONTINUE,
	JUMP_BREAK,
	JUMP_RETURN,
	JUMP_YIELD
} JumpType;

typedef enum StatementType
{
	STATEMENT_EXPRESSION,
	STATEMENT_DECLARATION,
	STATEMENT_BLOCK
} StatementType;

typedef enum PrimitiveType
{
	PRIMITIVE_VOID,
	PRIMITIVE_UNSIGNED_INTEGER,
	PRIMITIVE_SIGNED_INTEGER,
	PRIMITIVE_FLOATING_POINT,
	PRIMITIVE_BOOLEAN,
	PRIMITIVE_CHARACTER,
	PRIMITIVE_STRING
} PrimitiveType;

typedef enum ExpressionType
{
	EXPRESSION_BLOCK,
	EXPRESSION_ASSIGNMENT,
	EXPRESSION_CONDITIONAL,
	EXPRESSION_BOOLEAN_OR,
	EXPRESSION_BOOLEAN_AND,
	EXPRESSION_BITWISE_OR,
	EXPRESSION_BITWISE_XOR,
	EXPRESSION_BITWISE_AND,
	EXPRESSION_EQUALITY,
	EXPRESSION_RELATIONAL,
	EXPRESSION_SHIFT,
	EXPRESSION_ADDITIVE,
	EXPRESSION_MULTIPLICATIVE,
	EXPRESSION_POSTFIX,
	EXPRESSION_PREFIX,
	EXPRESSION_LITERAL,
	EXPRESSION_SYMBOL
} ExpressionType;

typedef enum AdditiveType
{
	ADDITIVE_ADD,
	ADDITIVE_SUBTRACT
} AdditiveType;

typedef enum LiteralType
{
	LITERAL_INTEGER,
	LITERAL_CHARACTER,
	LITERAL_STRING,
	LITERAL_FLOAT,
	LITERAL_BOOLEAN
	// TODO: add LITERAL_OBJECT
} LiteralType;

typedef enum EqualityType
{
	EQUALITY_EQUALS,
	EQUALITY_NOT_EQUALS
} EqualityType;

typedef enum MultiplicativeType
{
	MULTIPLICATIVE_MULTIPLY,
	MULTIPLICATIVE_DIVIDE,
	MULTIPLICATIVE_MODULUS
} MultiplicativeType;

typedef enum RelationalType
{
	RELATIONAL_GREATER_THAN,
	RELATIONAL_LESS_THAN,
	RELATIONAL_GREATER_THAN_OR_EQUAL_TO,
	RELATIONAL_LESS_THAN_OR_EQUAL_TO
} RelationalType;

typedef enum PostfixType
{
	POSTFIX_INDEX,
	POSTFIX_FUNCTION_CALL,
	POSTFIX_MEMBER
} PostfixType;

typedef enum PrefixType
{
	PREFIX_REFERENCE,
	PREFIX_DEREFERENCE,
	PREFIX_POSITIVE,
	PREFIX_NEGATIVE,
	PREFIX_BITWISE_NOT,
	PREFIX_BOOLEAN_NOT
} PrefixType;

typedef enum BitShiftType
{
	BIT_SHIFT_LEFT,
	BIT_SHIFT_RIGHT
} BitShiftType;

typedef enum SymbolType
{
	SYMBOL_PACKAGE,
	SYMBOL_STRUCT,
	SYMBOL_PRIMITIVE,
	SYMBOL_FUNCTION,
	SYMBOL_VARIABLE,
	SYMBOL_PARAMETER
} SymbolType;

const char *constantTypeName(LiteralType type);
const char *symbolTypeName(SymbolType type);

#endif
