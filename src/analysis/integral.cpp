#include "analysis/integral.hpp"

#include "parser/statements/statement_number.hpp"
#include "parser/tree.hpp"

StatementNumber Integral::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    if (rawArguments.size() != 3)
    {
        throw std::invalid_argument("Integral requires exactly 3 parameters");
    }

    const StatementNumber& lowerBound = rawArguments.front() ? 
        rawArguments.front()->EvaluateNode(0.0) : StatementNumber(0.0);
    const StatementNumber& upperBound = rawArguments[1] ?
        rawArguments[1]->EvaluateNode(0.0) : StatementNumber(0.0);
    const std::shared_ptr<TreeNode>& inputFunction = rawArguments.back();

    return SimpsonsRule(SUBINTERVALS, lowerBound, upperBound, inputFunction);
}

std::unique_ptr<Statement> Integral::DeepCopy() const
{
    return std::make_unique<Integral>(*this);
}

StatementNumber Integral::SimpsonsRule(const int subintervals, const StatementNumber& lowerBound,
    const StatementNumber& upperBound, const std::shared_ptr<TreeNode>& inputFunction) const
{
    if (subintervals <= 0 || subintervals % 2 != 0)
    {
        throw std::invalid_argument("Subintervals must be a positive even integer");
    }

    StatementNumber sum = inputFunction->EvaluateNode(lowerBound.GetValue()) +
        inputFunction->EvaluateNode(upperBound.GetValue());

    for (int i = 1; i < subintervals; i++)
    {
        const StatementNumber x = IthX(subintervals, lowerBound, upperBound, i);
        if (i % 2 == 0)
        {
            sum = sum + inputFunction->EvaluateNode(x.GetValue()) * StatementNumber(2.0);
        }
        else
        {
            sum = sum + inputFunction->EvaluateNode(x.GetValue()) * StatementNumber(4.0);
        }
    }

    return sum * StepSize(subintervals, lowerBound, upperBound) / StatementNumber(3.0);
}

StatementNumber Integral::IthX(const int subintervals, const StatementNumber& lowerBound,
    const StatementNumber& upperBound, const int i) const
{
    if (subintervals <= 0)
    {
        throw std::invalid_argument("Subintervals must be a positive integer");
    }
    if (i < 0 || i >= subintervals)
    {
        throw std::out_of_range("Index i must be in the range [0, subintervals - 1]");
    }

    return lowerBound + StepSize(subintervals, lowerBound, upperBound) * StatementNumber(i);
}

StatementNumber Integral::StepSize(const int subintervals, const StatementNumber& lowerBound,
    const StatementNumber& upperBound) const
{
    if (subintervals <= 0)
    {
        throw std::invalid_argument("Subintervals must be a positive integer");
    }

    return (upperBound - lowerBound) / StatementNumber(subintervals);
}