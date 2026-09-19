#pragma once

#include "operator.hpp"

class BinaryOperator : Operator
{
public:
    std::unique_ptr<Statement> m_leftOperand;
    std::unique_ptr<Statement> m_rightOperand;
public:
    BinaryOperator() = default;
    ~BinaryOperator() = default;
    std::unique_ptr<Statement> Evaluate() const override = 0;
};

class UnaryOperator : Operator
{
private:
    std::unique_ptr<Statement> m_operand;
public:
    UnaryOperator() = default;
    ~UnaryOperator() = default;
    std::unique_ptr<Statement> Evaluate() const override = 0;
};