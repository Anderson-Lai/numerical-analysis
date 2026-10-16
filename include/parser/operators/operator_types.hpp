#pragma once

#include <memory>

#include "parser/operators/operator.hpp"
#include "parser/statements/statement.hpp"

class BinaryOperator : public Operator
{
public:
    BinaryOperator() = default;
    ~BinaryOperator() = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override = 0;
    std::unique_ptr<Statement> DeepCopy() const override = 0;
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
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override = 0;
    std::unique_ptr<Statement> DeepCopy() const override = 0;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "UnaryOperator";
    }
#endif
};