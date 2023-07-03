#include "parka/validator/Validator.hpp"
#include "parka/ast/TypeAnnotation.hpp"
#include "parka/ir/Package.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/LocalSymbolTable.hpp"
#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/symbol/VariableEntry.hpp"
#include "parka/util/Array.hpp"

namespace parka::validator
{
	using namespace parka::ir;

	static bool validatePackage(Array<FunctionIr*>& functions, PackageSymbolTable& package)
	{
		bool success = true;

		for (auto& function : package.functions())
		{
			auto *ir = function.resolve();

			if (!ir)
			{
				success = false;
				continue;
			}

			functions.push(ir);
		}

		// TODO: Structs and packages
		// TODO: Implement this

		return success;
	}

	Optional<ir::Ir> validateAst(const ast::Ast& ast)
	{
		const auto& package = ast.globalPackage();
		auto symbolTable = PackageSymbolTable(package);

		return validatePackage(symbolTable);
	}

	Optional<ir::Ir> validatePackage(PackageSymbolTable& symbolTable)
	{
		auto functions = Array<FunctionIr*>();
		auto success = validatePackage(functions, symbolTable);

		if (!success)
			return {};

		return Ir(std::move(functions));
	}

	ir::FunctionIr *validateFunction(const ast::FunctionAst& ast, SymbolTable& parentSymbolTable)
	{
		auto symbolTable = LocalSymbolTable(&parentSymbolTable);
		auto prototype = validatePrototype(ast.prototype(), symbolTable);
		auto *body = validateExpression(ast.body(), symbolTable);

		if (!prototype || !body)
			return {};

		auto *context = new ir::FunctionIr(String(symbolTable.scope()), *prototype, *body);

		return context;
	}

	static Optional<ir::Type> validateReturnType(const Optional<ast::TypeAnnotationAst>& syntax, LocalSymbolTable& symbolTable)
	{
		if (!syntax)
			return ir::Type::voidType;

		return validateTypeAnnotation(*syntax, symbolTable);
	}

	Optional<ir::PrototypeIr> validatePrototype(const ast::PrototypeAst& prototype, LocalSymbolTable& symbolTable)
	{
		auto success = true;
		const auto parameterCount = prototype.parameters().length();
		auto parameters = Array<ir::ParameterIr*>(parameterCount);

		for (auto *parameterAst : prototype.parameters())
		{
			auto *context = validateParameter(*parameterAst, symbolTable);

			if (context == nullptr)
			{
				success = false;
				continue;
			}

			parameters.push(context);
		}

		auto returnType = validateReturnType(prototype.returnType(), symbolTable);

		if (!returnType)
			success = false;

		if (!success)
			return {};

		return ir::PrototypeIr(std::move(parameters), *returnType);
	}

	Optional<ir::Type> validateTypeAnnotation(const ast::TypeAnnotationAst&, SymbolTable&)
	{
		log::notImplemented(here());
	}

	ir::ParameterIr *validateParameter(const ast::ParameterAst& ast, LocalSymbolTable& symbolTable)
	{
		auto type = validateTypeAnnotation(ast.annotation(), symbolTable);

		if (!type)
			return {};

		return new ir::ParameterIr(*type);
	}

	ir::ExpressionIr *validateExpression(const ast::ExpressionAst& ast, LocalSymbolTable& symbolTable)
	{
		switch (ast.expressionType)
		{
			case ExpressionType::Binary:
				return validateBinaryExpression((const ast::BinaryExpressionAst&)ast, symbolTable);

			case ExpressionType::Block:
				return validateBlockExpression((const ast::BlockExpressionAst&)ast, symbolTable);

			case ExpressionType::Call:
				break;

			case ExpressionType::Conditional:
				break;

			case ExpressionType::Identifier:
				return validateIdentifierExpression((const ast::IdentifierExpressionAst&)ast, symbolTable);

			case ExpressionType::If:
				break;

			case ExpressionType::Subscript:
				break;

			case ExpressionType::MemberAccess:
				break;

			case ExpressionType::Prefix:
				break;

			case ExpressionType::BoolLiteral:
				break;

			case ExpressionType::CharLiteral:
				break;

			case ExpressionType::FloatLiteral:
				break;

			case ExpressionType::IntegerLiteral:
				return validateIntegerLiteral((const ast::IntegerLiteralAst&)ast, symbolTable);

			case ExpressionType::StringLiteral:
				break;

			default:
				break;
		}

		log::fatal("Unable to validate Expression with Type: $", ast.expressionType);
	}

	ir::BlockExpressionIr *validateBlockExpression(const ast::BlockExpressionAst& ast, LocalSymbolTable& symbolTable)
	{
		auto success = true;
		auto statements = Array<StatementIr*>(ast.statements().length());

		for (const auto *statement : ast.statements())
		{
			auto *ir = validateStatement(*statement, symbolTable);

			if (ir == nullptr)
			{
				success = false;
				continue;
			}

			statements.push(ir);
		}

		// TODO: Implement return type

		if (!success)
			return {};

		return new BlockExpressionIr(std::move(statements), Type(Type::voidType));
	}

	ir::BinaryExpressionIr *validateBinaryExpression(const ast::BinaryExpressionAst& ast, LocalSymbolTable& symbolTable)
	{
		auto *lhs = validateExpression(ast.lhs(), symbolTable);
		auto *rhs = validateExpression(ast.rhs(), symbolTable);

		// TODO: Operators

		if (!lhs || !rhs)
			return nullptr;

		const auto& lhsType = lhs->valueType();
		const auto& rhsType = rhs->valueType();

		if (!rhsType.canConvertTo(lhsType))
		{
			log::error(ast.snippet(), "$ cannot be added to $.", rhsType, lhsType);
			return nullptr;
		}

		return new ir::BinaryExpressionIr(*lhs, *rhs, ast.binaryExpressionType(), ir::Type(lhsType));
	}

	ir::IdentifierExpressionIr *validateIdentifierExpression(const ast::IdentifierExpressionAst& ast, LocalSymbolTable& symbolTable)
	{
		auto *resolution = symbolTable.resolve(ast.identifier());

		if (resolution == nullptr)
			return {};

		// TODO: Implement ir::Value that will be interface with anything with a Type
		// Member, variable, parameter, all expressions

		// TODO: Don't do it this way

		auto *value = dynamic_cast<Value*>(resolution);

		if (value == nullptr)
		{
			// TODO: Print resolvable type
			log::error("Unable to get value of `$`.", resolution->symbol());
			return {};
		}

		return new IdentifierExpressionIr(*value);
	}

	static Optional<u64> getIntegerValue(const Snippet& snippet)
	{
		u64 value = 0;
		const auto length = snippet.length();

		for (usize i = 0; i < length; ++i)
		{
			auto previousValue = value;

			value *= 10;
			value += snippet[i] - '0';

			auto isOverflown = value < previousValue;

			if (isOverflown)
			{
				log::error(snippet, "Integer literal is too large to fit in a 64 bit value.");
				return {};
			} 
		}
		
		return value;
	}

	static const ir::Type& getIntegerType(u64 value)
	{
		using ir::Type;

		if (value > 0xFFFFFFFF)
			return Type::u64Type;

		if (value > 0x0000FFFF)
			return Type::u32Type;

		if (value > 0x000000FF)
			return Type::u16Type;

		return Type::u8Type;
	}

	ir::IntegerLiteralIr *validateIntegerLiteral(const ast::IntegerLiteralAst& ast, LocalSymbolTable& symbolTable)
	{
		auto value = getIntegerValue(ast.snippet());

		if (!value)
			return {};

		const auto& type = getIntegerType(*value);

		return new ir::IntegerLiteralIr(*value, ir::Type(type));
	}

	ir::StatementIr *validateStatement(const ast::StatementAst& ast, LocalSymbolTable& symbolTable)
	{
		switch (ast.statementType)
		{
			case StatementType::Declaration:
				return validateDeclarationStatement((const ast::DeclarationStatementAst&)ast, symbolTable);

			// case StatementType::Expression:
			// 	break;

			// case StatementType::Jump:
			// 	break;

			default:
				break;
		}

		log::fatal("Unable to validate Statement with Type: $", ast.statementType);
	}

	ir::StatementIr *validateDeclarationStatement(const ast::DeclarationStatementAst& ast, LocalSymbolTable& symbolTable)
	{
		// FIXME: Update all expr an stmt validation to LocalSymbolTable
		auto *value = validateExpression(ast.value(), symbolTable);
		auto *variable = validateVariable(ast.variable(), value, symbolTable);
		auto *entry = symbolTable.declare(VariableEntry(ast.variable(), variable));

		if (!variable || !value || !entry)
			return {};

		return new ir::DeclarationStatementIr(*variable, *value);
	}

	static Optional<ir::Type> validateVariableType(const Optional<ast::TypeAnnotationAst>& annotation, ir::ExpressionIr *value, LocalSymbolTable& symbolTable)
	{
		if (!annotation)
		{
			if (!value)			
				return {};
			
			return value->valueType();
		}

		auto annotationType = validateTypeAnnotation(*annotation, symbolTable);

		if (!annotationType || !value)
			return {};

		auto Type = value->valueType();

		if (!Type.canConvertTo(*annotationType))
		{
			log::error("Unable to initialize variable of type $ with type $.", annotationType, Type);
			return {};
		}

		return annotationType;
	}

	ir::VariableIr *validateVariable(const ast::VariableAst& ast, ir::ExpressionIr *value, LocalSymbolTable& symbolTable)
	{
		auto type = validateVariableType(ast.annotation(), value, symbolTable);

		if (!type)
			return {};

		return new ir::VariableIr(String(ast.identifier().text()), *type);
	}
}
