#include <cmath>

#include "analysis/limit.hpp"

#include "parser/statements/statement_number.hpp"
#include "parser/tree.hpp"

StatementNumber Limit::Evaluate(const std::vector<StatementNumber>& parameters,
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

    // return average of the 'closest' left and right values to the approaching value
    return StatementNumber((leftValues.back().GetValue() + rightValues.back().GetValue()) / 2.0);
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
    if (!CheckStability(leftValues) || !CheckStability(rightValues))
    {
        return false;
    }

    if (leftValues.size() != rightValues.size())
    {
#ifdef DEBUG_BUILD
        throw std::runtime_error("Left and right limit values must have the same size");
#endif
        return false;
    }

    std::vector<StatementNumber> differences;
    differences.reserve(leftValues.size());

    for (size_t i = 0; i < leftValues.size(); i++)
    {
        differences.emplace_back(std::abs(leftValues[i].GetValue() - rightValues[i].GetValue()));
    }

    return IsDecreasing(differences);
}

bool Limit::CheckStability(const std::vector<StatementNumber>& sideValues) const
{
    const StatementNumber& targetValue = sideValues.back();

    std::vector<StatementNumber> differences;
    differences.reserve(sideValues.size() - 1);

    for (size_t i = 0; i < sideValues.size() - 1; i++)
    {
        differences.emplace_back(std::abs(sideValues[i].GetValue() - targetValue.GetValue()));
    }

    return IsDecreasing(differences);
}

bool Limit::IsDecreasing(const std::vector<StatementNumber> &values) const
{
    StatementNumber pastValue = values.front();

    for (size_t i = 1; i < values.size(); i++)
    {
        const StatementNumber& currentValue = values[i];

        if (currentValue.GetValue() > pastValue.GetValue())
        {
            return false;
        }

        pastValue = currentValue;
    }

    return true;
}