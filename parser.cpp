#include "parser.h"

Parser::Parser()
    : m_handler(std::make_unique<ValueHandler>())
{}


void Parser::setHandler(ICommandHandlerPtr handler) {
    m_handler = std::move(handler);
}


void Parser::parse(std::string_view& view) {
    while (not view.empty()) {
        m_handler->parse(this, view);
    }
}


void Parser::addNode(INodePtr node) {
    m_nodes.push_back(std::move(node));
}


void Parser::addNode(IBinaryOperationPtr node) {
    NodeType type = node->getType();
    m_nodes.push_back(std::move(node));
    m_queue.push({type, std::prev(m_nodes.end())});
}


INodePtr Parser::build() {
    while (m_nodes.size() > 1) {
        BinaryOperationPosition position = m_queue.top();
       
        INodePtr prev_val_node = std::move(*std::prev(position.iter));
        INodePtr next_val_node = std::move(*std::next(position.iter));
        INodePtr old_node = std::move(*position.iter);
        INodePtr new_node;
        
        switch (old_node->getType()) {
            case NodeType::Sum:
                new_node = makeNode<Sum>(std::move(prev_val_node), std::move(next_val_node));
                break;
            case NodeType::Mul:
                new_node = makeNode<Mul>(std::move(prev_val_node), std::move(next_val_node));
                break;
            case NodeType::Div:
                new_node = makeNode<Div>(std::move(prev_val_node), std::move(next_val_node));
                break;
            case NodeType::Dif:
                new_node = makeNode<Dif>(std::move(prev_val_node), std::move(next_val_node));
                break;
            default:
                throw std::runtime_error("Incorrect Node type");
                break;
        }
        
        auto insert_iter = std::next(std::next(position.iter));
        m_nodes.erase(std::prev(position.iter), insert_iter);
        m_nodes.insert(insert_iter, std::move(new_node));
        m_queue.pop();
    }
    INodePtr root_node = std::move(*m_nodes.begin());
    return root_node;
}


void ICommandHandler::remove_spaces(std::string_view& view) {
    size_t pos = view.find_first_not_of(' ');
    pos = pos > view.size() ? view.size() : pos;
    view.remove_prefix(pos);
}


void ValueHandler::parse(Parser * parser, std::string_view& view) {
    int value;
    size_t start_pos = view[0] == '-' ? 1 : 0;
    size_t pos = view.find_first_not_of("0123456789", start_pos);
    pos = pos > view.size() ? view.size() : pos;
    
    std::string str_value = std::string(view.substr(0, pos));
    try {
        value = std::stoi(str_value);
    } catch (std::invalid_argument& ex) {
        throw std::runtime_error("Expected integer number but got '" + str_value + "'");
    }
    

    view.remove_prefix(pos);
    remove_spaces(view);
    
    INodePtr node = makeNode<Val>(value);
    parser->addNode(std::move(node));
    parser->setHandler(std::make_unique<BinaryOperationHandler>());
}


void BinaryOperationHandler::parse(Parser * parser, std::string_view& view) {
    char ch = view[0];
    
    IBinaryOperationPtr node = nullptr;
    switch (ch) {
        case '+':
            node = std::make_unique<Sum>();
            break;
        case '-':
            node = std::make_unique<Dif>();
            break;
        case '*':
            node = std::make_unique<Mul>();
            break;
        case '/':
            node = std::make_unique<Div>();
            break;
        default:
            throw std::runtime_error("Expected one of [+, -, *, /], but got integer value");
            break;
    }
    
    view.remove_prefix(1);
    remove_spaces(view);
    parser->addNode(std::move(node));
    parser->setHandler(std::make_unique<ValueHandler>());
}



