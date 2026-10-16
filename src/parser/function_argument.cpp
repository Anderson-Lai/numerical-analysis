#include "parser/statements/functions/function_argument.hpp"
#include "parser/statements/statement_number.hpp"

StatementNumber FunctionArgument::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    throw std::runtime_error("FunctionArgument::Evaluate() should never be called directly");
}

std::unique_ptr<Statement> FunctionArgument::DeepCopy() const
{
    return std::make_unique<FunctionArgument>(*this);
}