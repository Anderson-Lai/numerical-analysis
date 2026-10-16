#include "parser/statements/functions/logarithm.hpp"
#include "parser/statements/statement_number.hpp"

StatementNumber Logarithm::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    if (parameters.size() != 2)
    {
        throw std::invalid_argument("Logarithm function requires exactly two parameters: the value and the base.");
    }

    const double base = parameters.front().GetValue();
    const double value = parameters.back().GetValue();

    if (base <= 0.0 || base == 1.0)
    {
        throw std::domain_error("Logarithm base must be positive and not equal to 1.");
    }
    if (value <= 0.0)
    {
        throw std::domain_error("Logarithm value must be positive.");
    }

    double result = std::log(value) / std::log(base);
    return StatementNumber(result);
}

std::unique_ptr<Statement> Logarithm::DeepCopy() const
{
    return std::make_unique<Logarithm>(*this);
}