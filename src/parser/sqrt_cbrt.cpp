#include "parser/statements/functions/sqrt_cbrt.hpp"
#include "parser/statements/statement_number.hpp"

StatementNumber SquareRoot::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Square root function requires exactly one parameter.");
    }

    const double value = parameters.front().GetValue();

    if (value < 0.0)
    {
        throw std::domain_error("Square root is not defined for negative values.");
    }

    return StatementNumber(std::sqrt(value));
}

StatementNumber CubeRoot::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Cube root function requires exactly one parameter.");
    }

    const double value = parameters.front().GetValue();
    return StatementNumber(std::cbrt(value));
}