#pragma once

#include <memory>
#include <map>

class IVisitor;
class INode;
class Val;
class Sum;
class Div;
class Mul;
class Dif;
class Brackets;
using IVisitorPtr = std::shared_ptr<IVisitor>;
using INodePtr    = std::shared_ptr<INode>;


enum class NodeType {
	Val,
	Sum,
	Dif,
	Mul,
	Div,
	Brackets
};


const std::map<NodeType, uint8_t> nodePriority = {
	{NodeType::Val,  0},
	{NodeType::Brackets, 0},
	{NodeType::Sum, 10},
	{NodeType::Dif, 10},
	{NodeType::Mul, 20},
	{NodeType::Div, 20},
};


class IVisitor : std::enable_shared_from_this<IVisitor> {
public:
	virtual ~IVisitor() = default;
	virtual int64_t visit(Val& node) = 0;
	virtual int64_t visit(Sum& node) = 0;
	virtual int64_t visit(Div& node) = 0;
	virtual int64_t visit(Mul& node) = 0;
	virtual int64_t visit(Dif& node) = 0;
	virtual int64_t visit(Brackets& node) = 0;
	virtual IVisitorPtr getptr() = 0;
};


class INode {
public:
	virtual ~INode() = default;
	virtual int64_t accept(IVisitorPtr visitor) = 0;
	virtual NodeType getType() const = 0;
};


class Val : public INode {
public:
	Val(int64_t value);
	int64_t accept(IVisitorPtr visitor) override;
	int64_t getValue();
	NodeType getType() const override;
private:
	int64_t m_value;
};


class Brackets : public INode {
public:
	Brackets(INodePtr node);
	int64_t accept(IVisitorPtr visitor) override;
	NodeType getType() const override;
	INodePtr getNode();
private:
    INodePtr m_node;
};


class IBinaryOperation : public INode {
public:
	IBinaryOperation() = default;
	IBinaryOperation(INodePtr leftNode, INodePtr rightNode);
	INodePtr getLeftNode();
	INodePtr getRightNode();
private:
	INodePtr m_leftNode  = nullptr;
	INodePtr m_rightNode = nullptr;
};
using IBinaryOperationPtr = std::shared_ptr<IBinaryOperation>;


class Sum : public IBinaryOperation {
public:
	Sum() = default;
	Sum(INodePtr leftNode, INodePtr rightNode);
	int64_t accept(IVisitorPtr visitor) override;
	NodeType getType() const override;
};


class Dif : public IBinaryOperation {
public:
	Dif() = default;
	Dif(INodePtr leftNode, INodePtr rightNode);
	int64_t accept(IVisitorPtr visitor) override;
	NodeType getType() const override;
};


class Mul : public IBinaryOperation {
public:
	Mul() = default;
	Mul(INodePtr leftNode, INodePtr rightNode);
	int64_t accept(IVisitorPtr visitor) override;
	NodeType getType() const override;
};


class Div : public IBinaryOperation {
public:
	Div() = default;
	Div(INodePtr leftNode, INodePtr rightNode);
	int64_t accept(IVisitorPtr visitor) override;
	NodeType getType() const override;
};


template <typename T, typename... Args>
INodePtr makeNode(Args... args) {
	return std::make_shared<T>(std::move(args)...);
}

template <typename T>
IVisitorPtr makeVisitor() {
	return std::make_shared<T>();
}




