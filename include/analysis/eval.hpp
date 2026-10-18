#pragma once

#include "parser/statements/statement.hpp"

class Eval final : public Statement
{
public:
    Eval() = default;
    ~Eval() override = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override;
    std::unique_ptr<Statement> DeepCopy() const override;
#ifdef DEBUG_BUILD
public:
    virtual void LogConcreteType() const override
    {
        std::cout << "Eval";
    }
#endif
};