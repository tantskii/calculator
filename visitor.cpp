#include "visitor.h"
#include <iostream>


int Calculation::visit(Val& node) {
    return node.getValue();
}


int Calculation::visit(Sum& node) {
    return node.getLeftNode()->accept(getptr()) \
         + node.getRightNode()->accept(getptr());
}


int Calculation::visit(Dif& node) {
    return node.getLeftNode()->accept(getptr()) \
         - node.getRightNode()->accept(getptr());
}


int Calculation::visit(Mul& node) {
    return node.getLeftNode()->accept(getptr()) \
         * node.getRightNode()->accept(getptr());
}


int Calculation::visit(Div& node) {
    int right_result = node.getRightNode()->accept(getptr());
    if (right_result == 0) {
        throw std::runtime_error("Zero division error");
    }
    return node.getLeftNode()->accept(getptr()) \
         / right_result;
}


IVisitorPtr Calculation::getptr() {
    return std::make_shared<Calculation>();
}


int Calculation::visit(Brackets &node) {
    return node.getNode()->accept(getptr());
}


int Print::visit(Val& node) {
    std::cout << node.getValue() << std::endl;
    return 1;
}


int Print::visit(Sum& node) {
   node.getLeftNode()->accept(getptr());
   std::cout << "+" << std::endl;
   node.getRightNode()->accept(getptr());
    return 1;
}


int Print::visit(Dif& node) {
    node.getLeftNode()->accept(getptr());
    std::cout << "-" << std::endl;
    node.getRightNode()->accept(getptr());
    return 1;
}


int Print::visit(Mul& node) {
    node.getLeftNode()->accept(getptr());
    std::cout << "*" << std::endl;
    node.getRightNode()->accept(getptr());
    return 1;
}


int Print::visit(Div& node) {
    node.getLeftNode()->accept(getptr());
    std::cout << "/" << std::endl;
    node.getRightNode()->accept(getptr());
    return 1;
}


int Print::visit(Brackets &node) {
    std::cout << "(" << std::endl;
    node.getNode()->accept(getptr());
    std::cout << ")" << std::endl;
    return 1;
}


IVisitorPtr Print::getptr() {
    return std::make_shared<Print>();
}


