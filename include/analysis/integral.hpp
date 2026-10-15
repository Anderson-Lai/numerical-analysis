#pragma once

#include "parser/statements/statement.hpp"

class Integral final : public Statement
{
public:
    Integral() = default;
    ~Integral() override = default;
    virtual StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "Integral";
    }
#endif
};