#include "parser/operators/binary_operators.hpp"

StatementNumber AdditionOperator::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>&) const
{
    if (parameters.size() != 2)
    {
        throw std::invalid_argument("Addition operator requires exactly two parameters.");
    }

    return parameters.front() + parameters.back();
}

std::unique_ptr<Statement> AdditionOperator::DeepCopy() const
{
    return std::make_unique<AdditionOperator>(*this);
}

StatementNumber SubtractionOperator::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>&) const
{
    if (parameters.size() != 2)
    {
        throw std::invalid_argument("Subtraction operator requires exactly two parameters.");
    }

    return parameters.front() - parameters.back();
}

std::unique_ptr<Statement> SubtractionOperator::DeepCopy() const
{
    return std::make_unique<SubtractionOperator>(*this);
}

StatementNumber MultiplicationOperator::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>&) const
{
    if (parameters.size() != 2)
    {
        throw std::invalid_argument("Multiplication operator requires exactly two parameters.");
    }

    return parameters.front() * parameters.back();
}

std::unique_ptr<Statement> MultiplicationOperator::DeepCopy() const
{
    return std::make_unique<MultiplicationOperator>(*this);
}

StatementNumber DivisionOperator::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>&) const
{
    if (parameters.size() != 2)
    {
        throw std::invalid_argument("Division operator requires exactly two parameters.");
    }

    return parameters.front() / parameters.back();
}

std::unique_ptr<Statement> DivisionOperator::DeepCopy() const
{
    return std::make_unique<DivisionOperator>(*this);
}

StatementNumber ExponentiationOperator::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>&) const
{
    if (parameters.size() != 2)
    {
        throw std::invalid_argument("Exponentiation operator requires exactly two parameters.");
    }

    return std::pow(parameters.front().GetValue(), parameters.back().GetValue());
}

std::unique_ptr<Statement> ExponentiationOperator::DeepCopy() const
{
    return std::make_unique<ExponentiationOperator>(*this);
}