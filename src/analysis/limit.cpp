#include <cmath>
#include <stdint.h>

#include "analysis/limit.hpp"

#include "parser/statements/statement_number.hpp"
#include "parser/tree.hpp"

StatementNumber Limit::Evaluate(const std::vector<StatementNumber>&,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    if (rawArguments.size() != 2)
    {
        throw std::invalid_argument("Limit requires exactly 2 parameters");
    }

    const StatementNumber& approachingValue = rawArguments.front() ? 
        rawArguments.front()->EvaluateNode(0.0) : StatementNumber(0.0);
    auto leftValues = LeftLimit(approachingValue, rawArguments);
    auto rightValues = RightLimit(approachingValue, rawArguments);

    if (!CheckExistence(leftValues, rightValues))
    {
        throw std::runtime_error("Limit does not exist");
    }

    size_t minIndex = 0;
    double minError = INT32_MAX;
    for (size_t i = 0; i < leftValues.size(); i++)
    {
        const double error = std::abs(leftValues[i].GetValue() - rightValues[i].GetValue());
        if (error < minError)
        {
            minError = error;
            minIndex = i;
        }
    }

    return StatementNumber((leftValues[minIndex].GetValue() + rightValues[minIndex].GetValue()) / 2.0);
}

std::unique_ptr<Statement> Limit::DeepCopy() const
{
    return std::make_unique<Limit>(*this);
}

std::vector<StatementNumber> Limit::LeftLimit(const StatementNumber& approachingValue,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    const std::shared_ptr<TreeNode>& inputFunction = rawArguments.back();
    std::vector<StatementNumber> leftValues;
    leftValues.reserve(STEPS);

    for (int i = STEPS; i > 0; i--)
    {
        leftValues.emplace_back(
            inputFunction->EvaluateNode(approachingValue.GetValue() - (i * DISCRETIZATION_SIZE))
        );
    }

    return leftValues;
}

std::vector<StatementNumber> Limit::RightLimit(const StatementNumber& approachingValue,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    const std::shared_ptr<TreeNode>& inputFunction = rawArguments.back();
    std::vector<StatementNumber> rightValues;
    rightValues.reserve(STEPS);

    for (int i = STEPS; i > 0; i--)
    {
        rightValues.emplace_back(
            inputFunction->EvaluateNode(approachingValue.GetValue() + (i * DISCRETIZATION_SIZE))
        );
    }

    return rightValues;
}

bool Limit::CheckExistence(const std::vector<StatementNumber>& leftValues,
    const std::vector<StatementNumber>& rightValues) const
{
    std::vector<double> errors;
    if (leftValues.size() != rightValues.size())
    {
#ifdef DEBUG_BUILD
        throw std::runtime_error("Left and right limit values must have the same size");
#endif
        return false;
    }

    for (size_t i = 0; i < leftValues.size(); i++)
    {
        errors.emplace_back(std::abs(leftValues[i].GetValue() - rightValues[i].GetValue()));
    }

    // as discretization approaches 0, we expect error to be decreasing (minus some floating point error)
    return IsDecreasingWithinThreshold(errors);
}

bool Limit::IsDecreasingWithinThreshold(const std::vector<double>& values) const
{
    double pastValue = values.front();

    for (size_t i = 1; i < values.size(); i++)
    {
        const double& currentValue = values[i];

        // ideally, currentValue - pastValue < 0, but we allow for some floating point error
        if (currentValue - pastValue > STABILITY_THRESHOLD)
        {
            return false;
        }

        pastValue = currentValue;
    }

    return true;
}