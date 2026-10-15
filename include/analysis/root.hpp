#pragma once

#include "parser/statements/statement.hpp"

class Root final : public Statement
{
public:
    Root() = default;
    ~Root() override = default;
    virtual StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "Root";
    }
#endif
};