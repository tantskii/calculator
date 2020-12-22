#include "node.h"

IBinaryOperation::IBinaryOperation(INodePtr&& leftNode, INodePtr&& rightNode)
    : m_leftNode(std::move(leftNode))
    , m_rightNode(std::move(rightNode))
{}

INodePtr IBinaryOperation::getLeftNode()  { return std::move(m_leftNode); }
INodePtr IBinaryOperation::getRightNode() { return std::move(m_rightNode); }
void IBinaryOperation::setLeftNode (INodePtr node) { m_leftNode  = std::move(node); }
void IBinaryOperation::setRightNode(INodePtr node) { m_rightNode = std::move(node); }
int Val::getValue() { return m_value; }


// Node ctors start //
Val::Val(int value) : m_value(value) {}
Sum::Sum(INodePtr&& leftNode, INodePtr&& rightNode)
    : IBinaryOperation(std::move(leftNode), std::move(rightNode)) {}
Dif::Dif(INodePtr&& leftNode, INodePtr&& rightNode)
    : IBinaryOperation(std::move(leftNode), std::move(rightNode)) {}
Mul::Mul(INodePtr&& leftNode, INodePtr&& rightNode)
    : IBinaryOperation(std::move(leftNode), std::move(rightNode)) {}
Div::Div(INodePtr&& leftNode, INodePtr&& rightNode)
    : IBinaryOperation(std::move(leftNode), std::move(rightNode)) {}
// Node ctors end //


// Node accept start //
int Val::accept (IVisitorPtr visitor) { return visitor->visit(*this); }
int Sum::accept (IVisitorPtr visitor) { return visitor->visit(*this); }
int Dif::accept (IVisitorPtr visitor) { return visitor->visit(*this); }
int Mul::accept (IVisitorPtr visitor) { return visitor->visit(*this); }
int Div::accept (IVisitorPtr visitor) { return visitor->visit(*this); }
// Node accept end //


// Node getType start //
NodeType Val::getType() const { return NodeType::Val; }
NodeType Sum::getType() const { return NodeType::Sum; }
NodeType Dif::getType() const { return NodeType::Dif; }
NodeType Mul::getType() const { return NodeType::Mul; }
NodeType Div::getType() const { return NodeType::Div; }
// Node getType end //


