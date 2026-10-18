#include <cmath>

#include "analysis/series.hpp"

#include "parser/statements/statement_number.hpp"
#include "parser/tree.hpp"

bool Series::IsNaturalNumber(const StatementNumber& number)
{
    return number.GetValue() >= 0.0 && std::floor(number.GetValue()) == number.GetValue();
}

StatementNumber Sum::Evaluate(const std::vector<StatementNumber>&,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    if (rawArguments.size() != 3)
    {
        throw std::invalid_argument("Sum must contain exactly 3 elements.");
    }

    if (!rawArguments.back())
    {
        throw std::invalid_argument("Sum must contain a valid function to sum over.");
    }

    const StatementNumber& lowerBound = rawArguments.front() ?
        rawArguments.front()->EvaluateNode(StatementNumber(0.0)) : StatementNumber(0.0);
    const StatementNumber& upperBound = rawArguments[1] ?
        rawArguments[1]->EvaluateNode(StatementNumber(0.0)) : StatementNumber(0.0);
    
    if (!Series::IsNaturalNumber(lowerBound) || !Series::IsNaturalNumber(upperBound))
    {
        throw std::invalid_argument("Sum bounds must be natural numbers.");
    }

    const int lowerBoundValue = static_cast<int>(lowerBound.GetValue());
    const int upperBoundValue = static_cast<int>(upperBound.GetValue());
    StatementNumber result(0.0);
    for (int i = lowerBoundValue; i <= upperBoundValue; i++)
    {
        result += rawArguments.back()->EvaluateNode(StatementNumber(static_cast<double>(i)));
    }

    return result;
}

std::unique_ptr<Statement> Sum::DeepCopy() const
{
    return std::make_unique<Sum>();
}

StatementNumber Product::Evaluate(const std::vector<StatementNumber>&,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    if (rawArguments.size() != 3)
    {
        throw std::invalid_argument("Product must contain exactly 3 elements.");
    }

    if (!rawArguments.back())
    {
        throw std::invalid_argument("Product must contain a valid function to multiply over.");
    }

    const StatementNumber& lowerBound = rawArguments.front() ?
        rawArguments.front()->EvaluateNode(StatementNumber(0.0)) : StatementNumber(0.0);
    const StatementNumber& upperBound = rawArguments[1] ?
        rawArguments[1]->EvaluateNode(StatementNumber(0.0)) : StatementNumber(0.0);

    if (!Series::IsNaturalNumber(lowerBound) || !Series::IsNaturalNumber(upperBound))
    {
        throw std::invalid_argument("Product bounds must be natural numbers.");
    }

    const int lowerBoundValue = static_cast<int>(lowerBound.GetValue());
    const int upperBoundValue = static_cast<int>(upperBound.GetValue());
    StatementNumber result(1.0);
    for (int i = lowerBoundValue; i <= upperBoundValue; i++)
    {
        result *= rawArguments.back()->EvaluateNode(StatementNumber(static_cast<double>(i)));
    }

    return result;
}

std::unique_ptr<Statement> Product::DeepCopy() const
{
    return std::make_unique<Product>();
}