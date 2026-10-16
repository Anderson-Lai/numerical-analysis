#include "analysis/root.hpp"

#include "parser/statements/statement_number.hpp"

StatementNumber Root::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    if (rawArguments.size() != 2)
    {
        throw std::invalid_argument("Root requires exactly 2 parameters");
    }

    throw std::runtime_error("Root evaluation not implemented yet");
}

std::unique_ptr<Statement> Root::DeepCopy() const
{
    return std::make_unique<Root>(*this);
}