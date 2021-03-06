#include "parser.h"

#include <memory>

void Parser::setHandler(ICommandHandlerPtr handler) {
	m_handler = std::move(handler);
}


void Parser::parse(std::string_view& view) {
	m_handler = ICommandHandler::getNextNodeHandler(view);
	while (!view.empty()) {
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
		}

		auto insert_iter = std::next(std::next(position.iter));
		m_nodes.erase(std::prev(position.iter), insert_iter);
		m_nodes.insert(insert_iter, std::move(new_node));
		m_queue.pop();
	}
	INodePtr root_node = std::move(*m_nodes.begin());
	return root_node;
}

ICommandHandlerPtr ICommandHandler::getNextNodeHandler(std::string_view view) {
	ICommandHandlerPtr handler = nullptr;
	char next_symbol = view[0];
	switch (next_symbol) {
		case '(':
			handler = std::make_shared<BracketsHandler>();
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			handler = std::make_shared<ValueHandler>();
			break;
		case '+':
		case '-':
		case '*':
		case '/':
			handler = std::make_shared<BinaryOperationHandler>();
			break;
		default:
			std::string error_message_2("Unexpected symbol: ");
			error_message_2 += next_symbol;
			throw std::runtime_error(error_message_2);
	}
	return handler;
}


void ValueHandler::parse(Parser * parser, std::string_view& view) {
	int64_t value;
	size_t start_pos = view[0] == '-' ? 1 : 0;
	size_t pos = view.find_first_not_of("0123456789", start_pos);
	pos = pos > view.size() ? view.size() : pos;

	std::string str_value = std::string(view.substr(0, pos));
	try {
		value = std::stoi(str_value);
	} catch (std::invalid_argument& ex) {
		throw std::runtime_error("Expected integer number but got '" + str_value + "'");
	}

	help::removePrefix(view, pos);
	help::removeSpaces(view);

	INodePtr node = makeNode<Val>(value);
	parser->addNode(std::move(node));
	parser->setHandler(std::make_shared<BinaryOperationHandler>());
}


void BinaryOperationHandler::parse(Parser * parser, std::string_view& view) {
	char ch = view[0];

	IBinaryOperationPtr node = nullptr;
	switch (ch) {
		case '+':
			node = std::make_shared<Sum>();
			break;
		case '-':
			node = std::make_shared<Dif>();
			break;
		case '*':
			node = std::make_shared<Mul>();
			break;
		case '/':
			node = std::make_shared<Div>();
			break;
		default:
			std::string error_message("Expected one of [+, -, *, /], but got: ");
			error_message += ch;
			throw std::runtime_error(error_message);
	}

	help::removePrefix(view, 1);
	help::removeSpaces(view);
	parser->addNode(std::move(node));
	parser->setHandler(ICommandHandler::getNextNodeHandler(view));
}


void BracketsHandler::parse(Parser * parser, std::string_view& view) {
	size_t bracket_counter = 0;
	bool found_close_bracket = false;
	char ch;
	size_t i = 0;

	if (view[0] != '(') {
		throw std::runtime_error("BracketsHandler can not parse expression which does not start with (");
	}

	while (!found_close_bracket && i < view.size()) {
		ch = view[i];

		switch (ch) {
			case '(':
				++bracket_counter;
				break;
			case ')':
				--bracket_counter;
				break;
			default:
				break;
		}

		found_close_bracket = bracket_counter == 0;

		if (!found_close_bracket) {
			i++;
		}
	}

	if (!found_close_bracket) {
		throw std::runtime_error("Incorrect number of brackets");
	}

	if (i == 1) {
		throw std::runtime_error("Expression '()' is incorrect");
	}

	std::string_view between_brackets = view.substr(1, i - 1);
	help::removeSpaces(between_brackets);

	Parser local_parser;
	local_parser.parse(between_brackets);
	INodePtr node = makeNode<Brackets>(local_parser.build());
	parser->addNode(std::move(node));
	parser->setHandler(std::make_shared<BinaryOperationHandler>());

	help::removePrefix(view, i + 1);
	help::removeSpaces(view);
}
