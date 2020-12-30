#pragma once

#include "node.h"


class Calculation : public IVisitor {
	int64_t visit(Val& node) override;
	int64_t visit(Sum& node) override;
	int64_t visit(Div& node) override;
	int64_t visit(Mul& node) override;
	int64_t visit(Dif& node) override;
	int64_t visit(Brackets& node) override;
	std::shared_ptr<IVisitor> getptr() override;
};

class Print : public IVisitor {
	int64_t visit(Val& node) override;
	int64_t visit(Sum& node) override;
	int64_t visit(Div& node) override;
	int64_t visit(Mul& node) override;
	int64_t visit(Dif& node) override;
	int64_t visit(Brackets& node) override;
	std::shared_ptr<IVisitor> getptr() override;
};
