#include "node.h"

// Node ctors start //
IBinaryOperation::IBinaryOperation(INodePtr leftNode, INodePtr rightNode)
	: m_leftNode(std::move(leftNode))
	, m_rightNode(std::move(rightNode))
{}

Val::Val(int64_t value)
	: m_value(value)
{}

Brackets::Brackets(INodePtr otherNode)
	: m_node(std::move(otherNode))
{}

Sum::Sum(INodePtr leftNode, INodePtr rightNode)
	: IBinaryOperation(std::move(leftNode), std::move(rightNode))
{}

Dif::Dif(INodePtr leftNode, INodePtr rightNode)
	: IBinaryOperation(std::move(leftNode), std::move(rightNode))
{}

Mul::Mul(INodePtr leftNode, INodePtr rightNode)
	: IBinaryOperation(std::move(leftNode), std::move(rightNode))
{}

Div::Div(INodePtr leftNode, INodePtr rightNode)
	: IBinaryOperation(std::move(leftNode), std::move(rightNode))
{}
// Node ctors end //


// Getters start
INodePtr IBinaryOperation::getLeftNode()  { return m_leftNode; }
INodePtr IBinaryOperation::getRightNode() { return m_rightNode; }
int64_t Val::getValue() { return m_value; }
INodePtr Brackets::getNode() { return m_node; }
// Getters end


// Node accept start //
int64_t Val::accept (IVisitorPtr visitor) { return visitor->visit(*this); }
int64_t Sum::accept (IVisitorPtr visitor) { return visitor->visit(*this); }
int64_t Dif::accept (IVisitorPtr visitor) { return visitor->visit(*this); }
int64_t Mul::accept (IVisitorPtr visitor) { return visitor->visit(*this); }
int64_t Div::accept (IVisitorPtr visitor) { return visitor->visit(*this); }
int64_t Brackets::accept (IVisitorPtr visitor) { return visitor->visit(*this); }
// Node accept end //


// Node getType start //
NodeType Val::getType() const { return NodeType::Val; }
NodeType Sum::getType() const { return NodeType::Sum; }
NodeType Dif::getType() const { return NodeType::Dif; }
NodeType Mul::getType() const { return NodeType::Mul; }
NodeType Div::getType() const { return NodeType::Div; }
NodeType Brackets::getType() const { return NodeType::Brackets; }
// Node getType end //


