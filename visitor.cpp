#include "visitor.h"
#include <iostream>


int64_t Calculation::visit(Val& node) {
	return node.getValue();
}


int64_t Calculation::visit(Sum& node) {
	return node.getLeftNode()->accept(getptr()) \
		 + node.getRightNode()->accept(getptr());
}


int64_t Calculation::visit(Dif& node) {
	return node.getLeftNode()->accept(getptr()) \
		 - node.getRightNode()->accept(getptr());
}


int64_t Calculation::visit(Mul& node) {
	return node.getLeftNode()->accept(getptr()) \
		 * node.getRightNode()->accept(getptr());
}


int64_t Calculation::visit(Div& node) {
	int64_t right_result = node.getRightNode()->accept(getptr());
	if (right_result == 0) {
		throw std::runtime_error("Zero division error");
	}
	return node.getLeftNode()->accept(getptr()) \
		 / right_result;
}


IVisitorPtr Calculation::getptr() {
	return std::make_shared<Calculation>();
}


int64_t Calculation::visit(Brackets &node) {
	return node.getNode()->accept(getptr());
}


int64_t Print::visit(Val& node) {
	std::cout << node.getValue() << std::endl;
	return 1;
}


int64_t Print::visit(Sum& node) {
	node.getLeftNode()->accept(getptr());
	std::cout << "+" << std::endl;
	node.getRightNode()->accept(getptr());
	return 1;
}


int64_t Print::visit(Dif& node) {
	node.getLeftNode()->accept(getptr());
	std::cout << "-" << std::endl;
	node.getRightNode()->accept(getptr());
	return 1;
}


int64_t Print::visit(Mul& node) {
	node.getLeftNode()->accept(getptr());
	std::cout << "*" << std::endl;
	node.getRightNode()->accept(getptr());
	return 1;
}


int64_t Print::visit(Div& node) {
	node.getLeftNode()->accept(getptr());
	std::cout << "/" << std::endl;
	node.getRightNode()->accept(getptr());
	return 1;
}


int64_t Print::visit(Brackets &node) {
	std::cout << "(" << std::endl;
	node.getNode()->accept(getptr());
	std::cout << ")" << std::endl;
	return 1;
}


IVisitorPtr Print::getptr() {
	return std::make_shared<Print>();
}


