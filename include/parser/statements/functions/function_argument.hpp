#pragma once

#include "function.hpp"

class FunctionArgument final : public Function
{
public:
    FunctionArgument() = default;
    virtual ~FunctionArgument() = default;
    virtual StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "FunctionArgument";
    }
#endif
};