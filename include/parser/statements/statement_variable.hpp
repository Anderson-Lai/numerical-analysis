#pragma once

#include <string>

#include "lexer/types.hpp"

#include "parser/statements/statement.hpp"

class StatementVariable final : public Statement
{
private:
    std::string m_name;
public:
    StatementVariable(const Variable& variable);
    StatementVariable(const std::string& name);
    ~StatementVariable() override = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters) const override;
#ifdef DEBUG_BUILD
    void LogConcreteType() const override
    {
        std::cout << "StatementVariable";
    }
#endif
};