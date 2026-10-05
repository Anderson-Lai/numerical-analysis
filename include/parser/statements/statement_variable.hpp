#pragma once

#include "statement.hpp"
#include "lexer/types.hpp"
#include <string>

class StatementVariable final : public Statement
{
private:
    std::string m_name;
public:
    StatementVariable(const Variable& variable);
    StatementVariable(const std::string& name);
    ~StatementVariable() override = default;
    StatementNumber Evaluate() const override;
};