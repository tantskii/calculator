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
using IVisitorPtr = std::shared_ptr<IVisitor>;
using INodePtr    = std::unique_ptr<INode>;


enum class NodeType {
    Val,
    Sum,
    Dif,
    Mul,
    Div,
};


static const std::map<NodeType, size_t> nodePriority = {
    {NodeType::Val,  0},
    {NodeType::Sum, 10},
    {NodeType::Dif, 10},
    {NodeType::Mul, 20},
    {NodeType::Div, 20},
};


class IVisitor : std::enable_shared_from_this<IVisitor> {
public:
    virtual ~IVisitor() = default;
    virtual int visit(Val& node) = 0;
    virtual int visit(Sum& node) = 0;
    virtual int visit(Div& node) = 0;
    virtual int visit(Mul& node) = 0;
    virtual int visit(Dif& node) = 0;
    virtual IVisitorPtr getptr() = 0;
};


class INode {
public:
    virtual ~INode() = default;
    virtual int accept(IVisitorPtr visitor) = 0;
    virtual NodeType getType() const = 0;
};


class Val : public INode {
public:
    Val(int value);
    int accept(IVisitorPtr visitor) override;
    int getValue();
    NodeType getType() const override;
private:
    int m_value;
    NodeType m_type = NodeType::Val;
};


class IBinaryOperation : public INode {
public:
    IBinaryOperation() = default;
    IBinaryOperation(INodePtr&& leftNode, INodePtr&& rightNode);
    virtual ~IBinaryOperation() = default;
    virtual int accept(IVisitorPtr visitor) = 0;
    INodePtr getLeftNode();
    INodePtr getRightNode();
    void setLeftNode(INodePtr node);
    void setRightNode(INodePtr node);
private:
    INodePtr m_leftNode  = nullptr;
    INodePtr m_rightNode = nullptr;
};
using IBinaryOperationPtr = std::unique_ptr<IBinaryOperation>;


class Sum : public IBinaryOperation {
public:
    Sum() = default;
    Sum(INodePtr&& leftNode, INodePtr&& rightNode);
    int accept(IVisitorPtr visitor) override;
    NodeType getType() const override;
};


class Dif : public IBinaryOperation {
public:
    Dif() = default;
    Dif(INodePtr&& leftNode, INodePtr&& rightNode);
    int accept(IVisitorPtr visitor) override;
    NodeType getType() const override;
};


class Mul : public IBinaryOperation {
public:
    Mul() = default;
    Mul(INodePtr&& leftNode, INodePtr&& rightNode);
    int accept(IVisitorPtr visitor) override;
    NodeType getType() const override;
};


class Div : public IBinaryOperation {
public:
    Div() = default;
    Div(INodePtr&& leftNode, INodePtr&& rightNode);
    int accept(IVisitorPtr visitor) override;
    NodeType getType() const override;
};


template <typename T, typename... Args>
INodePtr makeNode(Args... args) {
    return std::make_unique<T>(std::move(args)...);
}

template <typename T>
IVisitorPtr makeVisitor() {
    return std::make_shared<T>();
}




