#pragma once

#include <vector>

#include "parser/statements/statement.hpp"

class Function : public Statement
{
public:
    Function() = default;
    virtual ~Function() = default;
    virtual StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override = 0;
    virtual std::unique_ptr<Statement> DeepCopy() const override = 0;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "Function";
    }
#endif
};