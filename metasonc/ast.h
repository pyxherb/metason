#ifndef _METASONC_MODEL_H_
#define _METASONC_MODEL_H_

#include "basedefs.h"
#include <peff/containers/dynarray.h>
#include <peff/containers/hashmap.h>
#include <peff/containers/string.h>

namespace metasonc {
	struct TokenRange {
		size_t beginIndex = SIZE_MAX, endIndex = SIZE_MAX;

		inline TokenRange() = default;
		inline TokenRange(size_t index) : beginIndex(index), endIndex(index) {}
		inline TokenRange(size_t beginIndex, size_t endIndex) : beginIndex(beginIndex), endIndex(endIndex) {}

		METASONC_FORCEINLINE operator bool() {
			return beginIndex != SIZE_MAX;
		}
	};

	enum class AstNodeKind : uint8_t {
		TypeDef = 0,
		Interface,
		Enum,
		EnumItem,
		Property,
		TypeName,
		Comment
	};

	class AstNode : public peff::RcObject {
	protected:
		METASONC_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *allocator);

	public:
		peff::RcObjectPtr<peff::Alloc> selfAllocator;
		AstNodeKind astNodeKind;
		TokenRange tokenRange;

		METASONC_API AstNode(peff::Alloc *selfAllocator, AstNodeKind astNodeKind);
		METASONC_API AstNode(const AstNode &rhs, peff::Alloc *allocator);
		METASONC_API virtual ~AstNode();

		template <typename T>
		METASONC_FORCEINLINE peff::RcObjectPtr<T> duplicate(peff::Alloc *allocator) {
			return (T *)doDuplicate(allocator).get();
		}
	};

	class PropertyNode : public AstNode {
	protected:
		METASONC_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *allocator) override;

	public:
		peff::String name;

		METASONC_API PropertyNode(peff::Alloc *selfAllocator);
		METASONC_API PropertyNode(const PropertyNode &rhs, peff::Alloc *selfAllocator, bool &succeededOut);
	};

	class InterfaceNode : public AstNode {
	protected:
		METASONC_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *allocator) override;

	public:
		peff::HashMap<std::string_view, peff::RcObjectPtr<PropertyNode>> properties;

		METASONC_API InterfaceNode(peff::Alloc *selfAllocator);
		METASONC_API InterfaceNode(const InterfaceNode &rhs, peff::Alloc *selfAllocator, bool &succeededOut);
		METASONC_API virtual ~InterfaceNode();
	};

	enum class TypeKind : uint8_t {
		Number = 0,
		String,
		Object,
		Boolean,
		Array,
		Null,
		Union,
		InlineInterface,
		TypedArray,
		Custom
	};

	struct TypeName {
		TypeKind typeKind;
	};

	class TypeNameNode : public AstNode {
	public:
		TypeKind typeKind;

		METASONC_API TypeNameNode(peff::Alloc *selfAllocator, TypeKind typeKind);
		METASONC_API TypeNameNode(const TypeNameNode &rhs, peff::Alloc *allocator);
		METASONC_API virtual ~TypeNameNode();
	};

	class NumberTypeNameNode : public TypeNameNode {
	protected:
		METASONC_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *allocator) override;

	public:
		METASONC_API NumberTypeNameNode(peff::Alloc *selfAllocator);
		METASONC_API NumberTypeNameNode(const NumberTypeNameNode &rhs, peff::Alloc *allocator);
		METASONC_API virtual ~NumberTypeNameNode();
	};

	class ObjectTypeNameNode : public TypeNameNode {
	protected:
		METASONC_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *allocator) override;

	public:
		METASONC_API ObjectTypeNameNode(peff::Alloc *selfAllocator);
		METASONC_API ObjectTypeNameNode(const ObjectTypeNameNode &rhs, peff::Alloc *allocator);
		METASONC_API virtual ~ObjectTypeNameNode();
	};

	class BooleanTypeNameNode : public TypeNameNode {
	protected:
		METASONC_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *allocator) override;

	public:
		METASONC_API BooleanTypeNameNode(peff::Alloc *selfAllocator);
		METASONC_API BooleanTypeNameNode(const BooleanTypeNameNode &rhs, peff::Alloc *allocator);
		METASONC_API virtual ~BooleanTypeNameNode();
	};

	class ArrayTypeNameNode : public TypeNameNode {
	protected:
		METASONC_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *allocator) override;

	public:
		METASONC_API ArrayTypeNameNode(peff::Alloc *selfAllocator);
		METASONC_API ArrayTypeNameNode(const ArrayTypeNameNode &rhs, peff::Alloc *allocator);
		METASONC_API virtual ~ArrayTypeNameNode();
	};

	class NullTypeNameNode : public TypeNameNode {
	protected:
		METASONC_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *allocator) override;

	public:
		METASONC_API NullTypeNameNode(peff::Alloc *selfAllocator);
		METASONC_API NullTypeNameNode(const NullTypeNameNode &rhs, peff::Alloc *allocator);
		METASONC_API virtual ~NullTypeNameNode();
	};

	class UnionTypeNameNode : public TypeNameNode {
	protected:
		METASONC_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *allocator) override;

	public:
		peff::DynArray<peff::RcObjectPtr<TypeNameNode>> variants;

		METASONC_API UnionTypeNameNode(peff::Alloc *selfAllocator);
		METASONC_API UnionTypeNameNode(const UnionTypeNameNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		METASONC_API virtual ~UnionTypeNameNode();
	};

	class InlineInterfaceTypeNameNode : public TypeNameNode {
	protected:
		METASONC_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *allocator) override;

	public:
		peff::RcObjectPtr<InterfaceNode> inlinedInterface;

		METASONC_API InlineInterfaceTypeNameNode(peff::Alloc *selfAllocator);
		METASONC_API InlineInterfaceTypeNameNode(const InlineInterfaceTypeNameNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		METASONC_API virtual ~InlineInterfaceTypeNameNode();
	};

	class TypedArrayTypeNameNode : public TypeNameNode {
	protected:
		METASONC_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *allocator) override;

	public:
		peff::RcObjectPtr<TypeNameNode> elementType;

		METASONC_API TypedArrayTypeNameNode(peff::Alloc *selfAllocator);
		METASONC_API TypedArrayTypeNameNode(const TypedArrayTypeNameNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		METASONC_API virtual ~TypedArrayTypeNameNode();
	};

	class CustomTypeNameNode : public TypeNameNode {
	protected:
		METASONC_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *allocator);

	public:
		peff::String name;

		METASONC_API CustomTypeNameNode(peff::Alloc *selfAllocator);
		METASONC_API CustomTypeNameNode(const CustomTypeNameNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		METASONC_API virtual ~CustomTypeNameNode();
	};
}

#endif
