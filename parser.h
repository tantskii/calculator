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
	static std::shared_ptr<ICommandHandler> getNextNodeHandler(std::string_view);
protected:
    void remove_spaces(std::string_view&);
};
using ICommandHandlerPtr = std::shared_ptr<ICommandHandler>;


class Parser {
public:
    Parser() = default;
    Parser(Parser& other);
    void setHandler(ICommandHandlerPtr handler);
    void addNode(IBinaryOperationPtr);
    void addNode(INodePtr);

    void define(const std::string& alias, std::string_view meaning);
    void undefine(const std::string& alias);
    std::optional<INodePtr> findAlias(const std::string& alias);

    INodePtr build(std::string_view&);

    const std::string& getSpecSymbols() const;
private:
	void parse(std::string_view&);

    ICommandHandlerPtr m_handler;
    std::priority_queue<BinaryOperationPosition> m_queue;
    std::list<INodePtr> m_nodes;
    std::map<std::string, INodePtr> m_aliases;
    const std::string m_spec_symbols = "0123456789+-*/()";
};


class ValueHandler : public ICommandHandler {
public:
    void parse(Parser * parser, std::string_view&) override;
};


class BinaryOperationHandler : public ICommandHandler {
public:
    void parse(Parser * parser, std::string_view&) override;
};


class BracketsHandler : public ICommandHandler {
public:
    void parse(Parser * parser, std::string_view&) override;
};


class AliasHandler : public ICommandHandler {
public:
	void parse(Parser * parser, std::string_view&) override;
};


