#include "visitor.h"

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

