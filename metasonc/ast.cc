#include "ast.h"

using namespace metasonc;

METASONC_API peff::RcObjectPtr<AstNode> AstNode::doDuplicate(peff::Alloc* allocator) {
	std::terminate();
}

METASONC_API AstNode::AstNode(peff::Alloc *selfAllocator, AstNodeKind astNodeKind) : astNodeKind(astNodeKind), selfAllocator(selfAllocator) {
}

METASONC_API AstNode::~AstNode() {
}

METASONC_API TypeNameNode::TypeNameNode(peff::Alloc *selfAllocator, TypeKind typeKind): AstNode(selfAllocator, AstNodeKind::TypeName), typeKind(typeKind) {
}

METASONC_API TypeNameNode ::~TypeNameNode() {
}
