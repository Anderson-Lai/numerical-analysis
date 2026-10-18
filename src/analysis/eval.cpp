#include "analysis/eval.hpp"

#include "parser/statements/statement_number.hpp"
#include "parser/tree.hpp"

StatementNumber Eval::Evaluate(const std::vector<StatementNumber>&,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    if (rawArguments.size() != 2)
    {
        throw std::invalid_argument("Eval requires exactly 2 parameters");
    }

    const StatementNumber& point = rawArguments.front() ? 
        rawArguments.front()->EvaluateNode(0.0) : StatementNumber(0.0);
    const std::shared_ptr<TreeNode>& inputFunction = rawArguments.back();

    return inputFunction->EvaluateNode(point.GetValue());
}

std::unique_ptr<Statement> Eval::DeepCopy() const
{
    return std::make_unique<Eval>();
}