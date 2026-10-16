#include "analysis/integral.hpp"

#include "parser/statements/statement_number.hpp"

StatementNumber Integral::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    if (rawArguments.size() != 3)
    {
        throw std::invalid_argument("Integral requires exactly 3 parameters");
    }

    throw std::runtime_error("Integral evaluation not implemented yet");
}

std::unique_ptr<Statement> Integral::DeepCopy() const
{
    return std::make_unique<Integral>(*this);
}