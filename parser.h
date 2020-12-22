#pragma once

#include "node.h"
#include <utility>
#include <memory>
#include <string_view>
#include <string>
#include <list>
#include <queue>


class Parser;

struct BinaryOperationPosition {
    NodeType type;
    std::list<INodePtr>::iterator iter;
};

inline bool operator<(const BinaryOperationPosition& lhs,
                      const BinaryOperationPosition& rhs) {
    return nodePriority.at(lhs.type) < nodePriority.at(rhs.type);
}


class ICommandHandler {
public:
    virtual ~ICommandHandler() = default;
    virtual void parse(Parser * parser, std::string_view&) = 0;
protected:
    void remove_spaces(std::string_view&);
};
using ICommandHandlerPtr = std::unique_ptr<ICommandHandler>;


class Parser {
public:
    Parser();
    void setHandler(ICommandHandlerPtr handler);
    void parse(std::string_view&);
    void addNode(IBinaryOperationPtr);
    void addNode(INodePtr);
    INodePtr build();
private:
    ICommandHandlerPtr m_handler;
    std::priority_queue<BinaryOperationPosition> m_queue;
    std::list<INodePtr> m_nodes;
};


class ValueHandler : public ICommandHandler {
public:
    void parse(Parser * parser, std::string_view&) override;
};


class BinaryOperationHandler : public ICommandHandler {
public:
    void parse(Parser * parser, std::string_view&) override;
};


