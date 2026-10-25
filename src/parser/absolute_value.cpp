#include <cmath>

#include "parser/statements/functions/absolute_value.hpp"
#include "parser/statements/statement_number.hpp"

StatementNumber AbsoluteValue::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>&) const
{
    if (parameters.size() != 1)
    {
        throw std::runtime_error("AbsoluteValue::Evaluate() - expected 1 argument");
    }

    return StatementNumber(std::abs(parameters.front().GetValue()));
}

std::unique_ptr<Statement> AbsoluteValue::DeepCopy() const
{
    return std::make_unique<AbsoluteValue>(*this);
}