#ifndef PARKA_SYNTAX_MEMBER_SYNTAX_HPP
#define PARKA_SYNTAX_MEMBER_SYNTAX_HPP

#include "parka/ast/Entity.hpp"
#include "parka/ast/TypeAnnotation.hpp"
#include "parka/ast/Identifier.hpp"

namespace parka
{
	class MemberContext : public EntityContext
	{
		ValueType _valueType;

	public:

		MemberContext(ValueType&& valueType) :
		_valueType(std::move(valueType))
		{}
		MemberContext(MemberContext&&) = default;
		MemberContext(const MemberContext&) = delete;

		EntityType entityType() const { return EntityType::Member; }
		const ValueType *valueType() const { return &_valueType; }
	};

	class MemberSyntax : public EntitySyntax
	{
		Snippet _snippet;
		Identifier _identifier;
		TypeAnnotationSyntax _annotation;
		bool _isPublic;
		SymbolTable *_parent;
		// TODO: Add read/write count

	public:

		MemberSyntax(const Snippet& snippet, Identifier&& identifier, TypeAnnotationSyntax&& annotation, bool isPublic) :
		_snippet(snippet),
		_identifier(std::move(identifier)),
		_annotation(std::move(annotation)),
		_isPublic(isPublic)
		{}
		MemberSyntax(MemberSyntax&&) = default;
		MemberSyntax(const MemberSyntax&) = delete;

		static MemberSyntax *parse(Token& token);
		bool declareSelf(SymbolTable& parent);
		MemberContext *validate();
		EntityContext *context() { return validate(); }
		String getSymbol() const;

		const Identifier& identifier() const { return _identifier; }
		const String& name() const { return _identifier.text(); }
		EntityType entityType() const { return EntityType::Member; }
		const Snippet& snippet() const { return _snippet; }
		const auto& annotation() const { return _annotation; }
		const auto& isPublic() const { return _isPublic; }
	};
}

#endif
