#pragma once

#include "statement.hpp"
#include "functions/function.hpp"

class StatementFunction final : public Statement
{
private:
    std::shared_ptr<Function> m_function;
public:
    StatementFunction() = default;
    ~StatementFunction() override = default;
    StatementNumber Evaluate() const override;
#ifdef DEBUG_BUILD
    void LogConcreteType() const override
    {
        std::cout << "StatementFunction";
    }
#endif
};