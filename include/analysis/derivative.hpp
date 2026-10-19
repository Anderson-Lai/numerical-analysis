#pragma once

#include "parser/statements/statement.hpp"

class Derivative final : public Statement
{
public:
    Derivative() = default;
    ~Derivative() override = default;
    virtual StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override;
    std::unique_ptr<Statement> DeepCopy() const override;
private:
    StatementNumber VerifyExistence(const StatementNumber& point, 
        const std::shared_ptr<TreeNode>& inputFunction) const;
    StatementNumber ApproximateDerivative(const StatementNumber& point, 
        const std::shared_ptr<TreeNode>& inputFunction) const;
private:
    void ReplaceVariableWith(const std::shared_ptr<TreeNode>& node, 
        const std::shared_ptr<TreeNode>& replacement) const;
    std::shared_ptr<TreeNode> CopyAST(const std::shared_ptr<TreeNode>& node) const;
private:
    static constexpr double ACCEPTABLE_APPROACH_OFFSET = 1e-2;
#ifdef DEBUG_BUILD
public:
    virtual void LogConcreteType() const override
    {
        std::cout << "Derivative";
    }
#endif
};