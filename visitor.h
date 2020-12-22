#pragma once

#include "node.h"


class Calculation : public IVisitor {
    int visit(Val& node) override;
    int visit(Sum& node) override;
    int visit(Div& node) override;
    int visit(Mul& node) override;
    int visit(Dif& node) override;
    std::shared_ptr<IVisitor> getptr() override;
};
