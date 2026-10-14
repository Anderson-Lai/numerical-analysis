#pragma once

#include "parser/statements/statement.hpp"

class Series final : public Statement
{
public:
    Series() = default;
    ~Series() override = default;
    virtual StatementNumber Evaluate(const std::vector<StatementNumber>& parameters) const override;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "Series";
    }
#endif
};