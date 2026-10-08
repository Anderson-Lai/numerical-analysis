#include "parser/operators/binary_operators.hpp"

StatementNumber AdditionOperator::Evaluate(const std::vector<StatementNumber>& parameters) const
{
    if (parameters.size() != 2)
    {
        throw std::invalid_argument("Addition operator requires exactly two parameters.");
    }

    return parameters.front() + parameters.back();
}

StatementNumber SubtractionOperator::Evaluate(const std::vector<StatementNumber>& parameters) const
{
    if (parameters.size() != 2)
    {
        throw std::invalid_argument("Subtraction operator requires exactly two parameters.");
    }

    return parameters.front() - parameters.back();
}

StatementNumber MultiplicationOperator::Evaluate(const std::vector<StatementNumber>& parameters) const
{
    if (parameters.size() != 2)
    {
        throw std::invalid_argument("Multiplication operator requires exactly two parameters.");
    }

    return parameters.front() * parameters.back();
}

StatementNumber DivisionOperator::Evaluate(const std::vector<StatementNumber>& parameters) const
{
    if (parameters.size() != 2)
    {
        throw std::invalid_argument("Division operator requires exactly two parameters.");
    }

    return parameters.front() / parameters.back();
}

StatementNumber ExponentiationOperator::Evaluate(const std::vector<StatementNumber>& parameters) const
{
    if (parameters.size() != 2)
    {
        throw std::invalid_argument("Exponentiation operator requires exactly two parameters.");
    }

    return std::pow(parameters.front().GetValue(), parameters.back().GetValue());
}