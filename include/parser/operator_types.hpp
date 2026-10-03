#pragma once

#include "operator.hpp"
#include "statement.hpp"
#include <memory>

class BinaryOperator : Operator
{
public:
    std::unique_ptr<Statement> m_leftOperand;
    std::unique_ptr<Statement> m_rightOperand;
public:
    BinaryOperator() = default;
    ~BinaryOperator() = default;
    Number Evaluate() const override = 0;
};

class UnaryOperator : Operator
{
private:
    std::unique_ptr<Statement> m_operand;
public:
    UnaryOperator() = default;
    ~UnaryOperator() = default;
    Number Evaluate() const override = 0;
};