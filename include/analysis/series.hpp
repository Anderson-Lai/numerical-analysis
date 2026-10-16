#pragma once

#include "parser/statements/statement.hpp"

class Series final : public Statement
{
public:
    Series() = default;
    ~Series() override = default;
    virtual StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override;
    std::unique_ptr<Statement> DeepCopy() const override;
#ifdef DEBUG_BUILD
public:
    virtual void LogConcreteType() const override
    {
        std::cout << "Series";
    }
#endif
};