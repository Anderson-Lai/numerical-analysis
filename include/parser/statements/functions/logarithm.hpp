#pragma once

#include "function.hpp"

class Logarithm final : public Function
{
private:
    double m_base;
public:
    Logarithm(const std::vector<std::shared_ptr<Statement>>& arguments);
    ~Logarithm() override = default;
    StatementNumber Evaluate() const override;
};