#pragma once

#include "parser/statements/statement.hpp"

class Limit final : public Statement
{
public:
    Limit() = default;
    ~Limit() override = default;
    virtual StatementNumber Evaluate(const std::vector<StatementNumber>& parameters) const override;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "Limit";
    }
#endif
};