#pragma once

#include "parser/statements/statement.hpp"

class Derivative final : public Statement
{
public:
    Derivative() = default;
    ~Derivative() override = default;
    virtual StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "Derivative";
    }
#endif
};