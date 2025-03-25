#include "ast.h"

using namespace metasonc;

METASONC_API peff::RcObjectPtr<AstNode> AstNode::doDuplicate(peff::Alloc *allocator) {
	// Unimplemented yet, terminate.
	std::terminate();
}

METASONC_API AstNode::AstNode(peff::Alloc *selfAllocator, AstNodeKind astNodeKind) : astNodeKind(astNodeKind), selfAllocator(selfAllocator) {
}

METASONC_API AstNode::AstNode(const AstNode &rhs, peff::Alloc *allocator) : astNodeKind(rhs.astNodeKind), selfAllocator(allocator) {
}

METASONC_API AstNode::~AstNode() {
}

METASONC_API peff::RcObjectPtr<AstNode> PropertyNode::doDuplicate(peff::Alloc *allocator) {
	peff::RcObjectPtr<NumberTypeNameNode> ptr(peff::allocAndConstruct<NumberTypeNameNode>(allocator, sizeof(std::max_align_t), *this, allocator));
	if (!ptr)
		return {};
	return ptr.get();
}

METASONC_API PropertyNode::PropertyNode(peff::Alloc *selfAllocator) : AstNode(selfAllocator, AstNodeKind::Property), name(selfAllocator) {
}

METASONC_API PropertyNode::PropertyNode(const PropertyNode &rhs, peff::Alloc *selfAllocator, bool &succeededOut) : AstNode(rhs, selfAllocator), name(selfAllocator) {
	if (!name.build(rhs.name)) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}

METASONC_API peff::RcObjectPtr<AstNode> InterfaceNode::doDuplicate(peff::Alloc *allocator) {
	peff::RcObjectPtr<NumberTypeNameNode> ptr(peff::allocAndConstruct<NumberTypeNameNode>(allocator, sizeof(std::max_align_t), *this, allocator));
	if (!ptr)
		return {};
	return ptr.get();
}

METASONC_API InterfaceNode::InterfaceNode(peff::Alloc *selfAllocator) : AstNode(selfAllocator, AstNodeKind::Interface), properties(selfAllocator) {
}

METASONC_API InterfaceNode::InterfaceNode(const InterfaceNode &rhs, peff::Alloc *selfAllocator, bool &succeededOut) : AstNode(rhs, selfAllocator), properties(selfAllocator) {
	for (auto i : rhs.properties) {
		peff::RcObjectPtr<PropertyNode> p = i.second->duplicate<PropertyNode>(selfAllocator);

		if (!p) {
			succeededOut = false;
			return;
		}

		properties.insert(p->name, std::move(p));
	}

	succeededOut = true;
}

METASONC_API TypeNameNode::TypeNameNode(peff::Alloc *selfAllocator, TypeKind typeKind) : AstNode(selfAllocator, AstNodeKind::TypeName), typeKind(typeKind) {
}

METASONC_API TypeNameNode::TypeNameNode(const TypeNameNode &rhs, peff::Alloc *allocator) : AstNode(rhs, allocator), typeKind(rhs.typeKind) {
}

METASONC_API TypeNameNode::~TypeNameNode() {
}

METASONC_API peff::RcObjectPtr<AstNode> NumberTypeNameNode::doDuplicate(peff::Alloc *allocator) {
	peff::RcObjectPtr<NumberTypeNameNode> ptr(peff::allocAndConstruct<NumberTypeNameNode>(allocator, sizeof(std::max_align_t), *this, allocator));
	if (!ptr)
		return {};
	return ptr.get();
}

METASONC_API NumberTypeNameNode::NumberTypeNameNode(peff::Alloc *selfAllocator) : TypeNameNode(selfAllocator, TypeKind::Number) {
}

METASONC_API NumberTypeNameNode::~NumberTypeNameNode() {
}

METASONC_API peff::RcObjectPtr<AstNode> ObjectTypeNameNode::doDuplicate(peff::Alloc *allocator) {
	peff::RcObjectPtr<ObjectTypeNameNode> ptr(peff::allocAndConstruct<ObjectTypeNameNode>(allocator, sizeof(std::max_align_t), *this, allocator));
	if (!ptr)
		return {};
	return ptr.get();
}

METASONC_API ObjectTypeNameNode::ObjectTypeNameNode(peff::Alloc *selfAllocator) : TypeNameNode(selfAllocator, TypeKind::Object) {
}

METASONC_API ObjectTypeNameNode::~ObjectTypeNameNode() {
}

METASONC_API peff::RcObjectPtr<AstNode> BooleanTypeNameNode::doDuplicate(peff::Alloc *allocator) {
	peff::RcObjectPtr<BooleanTypeNameNode> ptr(peff::allocAndConstruct<BooleanTypeNameNode>(allocator, sizeof(std::max_align_t), *this, allocator));
	if (!ptr)
		return {};
	return ptr.get();
}

METASONC_API BooleanTypeNameNode::BooleanTypeNameNode(peff::Alloc *selfAllocator) : TypeNameNode(selfAllocator, TypeKind::Boolean) {
}

METASONC_API BooleanTypeNameNode::~BooleanTypeNameNode() {
}

METASONC_API peff::RcObjectPtr<AstNode> ArrayTypeNameNode::doDuplicate(peff::Alloc *allocator) {
	peff::RcObjectPtr<ArrayTypeNameNode> ptr(peff::allocAndConstruct<ArrayTypeNameNode>(allocator, sizeof(std::max_align_t), *this, allocator));
	if (!ptr)
		return {};
	return ptr.get();
}

METASONC_API ArrayTypeNameNode::ArrayTypeNameNode(peff::Alloc *selfAllocator) : TypeNameNode(selfAllocator, TypeKind::Array) {
}

METASONC_API ArrayTypeNameNode::~ArrayTypeNameNode() {
}

METASONC_API peff::RcObjectPtr<AstNode> NullTypeNameNode::doDuplicate(peff::Alloc *allocator) {
	peff::RcObjectPtr<NullTypeNameNode> ptr(peff::allocAndConstruct<NullTypeNameNode>(allocator, sizeof(std::max_align_t), *this, allocator));
	if (!ptr)
		return {};
	return ptr.get();
}

METASONC_API NullTypeNameNode::NullTypeNameNode(peff::Alloc *selfAllocator) : TypeNameNode(selfAllocator, TypeKind::Null) {
}

METASONC_API NullTypeNameNode::~NullTypeNameNode() {
}

METASONC_API peff::RcObjectPtr<AstNode> UnionTypeNameNode::doDuplicate(peff::Alloc *allocator) {
	bool succeeded;
	peff::RcObjectPtr ptr(peff::allocAndConstruct<UnionTypeNameNode>(allocator, sizeof(std::max_align_t), *this, allocator, succeeded));
	if ((!ptr) || (!succeeded))
		return {};
	return ptr.get();
}

METASONC_API UnionTypeNameNode::UnionTypeNameNode(peff::Alloc *selfAllocator) : TypeNameNode(selfAllocator, TypeKind::Union), variants(selfAllocator) {
}

METASONC_API UnionTypeNameNode::UnionTypeNameNode(const UnionTypeNameNode &rhs, peff::Alloc *allocator, bool &succeededOut) : TypeNameNode(rhs, allocator), variants(allocator) {
	if (!variants.resize(rhs.variants.size())) {
		succeededOut = false;
		return;
	}

	for (size_t i = 0; i < variants.size(); ++i) {
		if (!(variants.at(i) = rhs.variants.at(i)->duplicate<TypeNameNode>(allocator))) {
			succeededOut = false;
			return;
		}
	}

	succeededOut = true;
}

METASONC_API UnionTypeNameNode::~UnionTypeNameNode() {
}

METASONC_API peff::RcObjectPtr<AstNode> InlineInterfaceTypeNameNode::doDuplicate(peff::Alloc *allocator) {
	bool succeeded;
	peff::RcObjectPtr<InlineInterfaceTypeNameNode> ptr(peff::allocAndConstruct<InlineInterfaceTypeNameNode>(allocator, sizeof(std::max_align_t), *this, allocator, succeeded));
	if ((!ptr) || (!succeeded))
		return {};
	return ptr.get();
}

METASONC_API InlineInterfaceTypeNameNode::InlineInterfaceTypeNameNode(peff::Alloc *selfAllocator) : TypeNameNode(selfAllocator, TypeKind::InlineInterface) {
}

METASONC_API InlineInterfaceTypeNameNode::InlineInterfaceTypeNameNode(const InlineInterfaceTypeNameNode &rhs, peff::Alloc *selfAllocator, bool &succeededOut) : TypeNameNode(rhs, selfAllocator) {
	if (!(inlinedInterface->duplicate<InterfaceNode>(selfAllocator))) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}

METASONC_API InlineInterfaceTypeNameNode::~InlineInterfaceTypeNameNode() {
}

METASONC_API peff::RcObjectPtr<AstNode> TypedArrayTypeNameNode::doDuplicate(peff::Alloc *allocator) {
	bool succeeded;
	peff::RcObjectPtr<TypedArrayTypeNameNode> ptr(peff::allocAndConstruct<TypedArrayTypeNameNode>(allocator, sizeof(std::max_align_t), *this, allocator, succeeded));
	if ((!ptr) || (!succeeded))
		return {};
	return ptr.get();
}

METASONC_API TypedArrayTypeNameNode::TypedArrayTypeNameNode(peff::Alloc *selfAllocator) : TypeNameNode(selfAllocator, TypeKind::TypedArray) {
}

METASONC_API TypedArrayTypeNameNode::TypedArrayTypeNameNode(const TypedArrayTypeNameNode &rhs, peff::Alloc *selfAllocator, bool &succeededOut) : TypeNameNode(rhs, selfAllocator) {
	if (!(elementType->duplicate<InterfaceNode>(selfAllocator))) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}

METASONC_API TypedArrayTypeNameNode::~TypedArrayTypeNameNode() {
}

METASONC_API peff::RcObjectPtr<AstNode> CustomTypeNameNode::doDuplicate(peff::Alloc *allocator) {
	bool succeeded;
	peff::RcObjectPtr<CustomTypeNameNode> ptr(peff::allocAndConstruct<CustomTypeNameNode>(allocator, sizeof(std::max_align_t), *this, allocator, succeeded));
	if ((!ptr) || (!succeeded))
		return {};
	return ptr.get();
}

METASONC_API CustomTypeNameNode::CustomTypeNameNode(const CustomTypeNameNode &rhs, peff::Alloc *selfAllocator, bool &succeededOut) : TypeNameNode(rhs, selfAllocator), name(selfAllocator) {
	if (!name.build(rhs.name)) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}

METASONC_API CustomTypeNameNode::CustomTypeNameNode(peff::Alloc *selfAllocator) : TypeNameNode(selfAllocator, TypeKind::Custom), name(selfAllocator) {
}

METASONC_API CustomTypeNameNode::~CustomTypeNameNode() {
}