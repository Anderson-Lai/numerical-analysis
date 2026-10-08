#pragma once

#include "operator.hpp"
#include "parser/statements/statement.hpp"
#include <memory>

class BinaryOperator : public Operator
{
protected:
    std::shared_ptr<Statement> m_leftOperand;
    std::shared_ptr<Statement> m_rightOperand;
public:
    BinaryOperator() = default;
    ~BinaryOperator() = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters) const override = 0;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "BinaryOperator";
    }
#endif
};

// currently unused
class UnaryOperator : public Operator
{
protected:
    std::shared_ptr<Statement> m_operand;
public:
    UnaryOperator() = default;
    ~UnaryOperator() = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters) const override = 0;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "UnaryOperator";
    }
#endif
};