#pragma once

#include "parser/statements/functions/function.hpp"

class AbsoluteValue final : public Function
{
public:
    AbsoluteValue() = default;
    ~AbsoluteValue() override = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override;
    std::unique_ptr<Statement> DeepCopy() const override;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "AbsoluteValue";
    }
#endif
};