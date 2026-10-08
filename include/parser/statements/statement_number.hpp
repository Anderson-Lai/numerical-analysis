#pragma once

#include "lexer/types.hpp"

#include "parser/statements/statement.hpp"

#ifdef DEBUG_BUILD
#include <iostream>
#endif

class StatementNumber final : public Statement
{
private:
    double m_value;
public:
    StatementNumber(const Number& value);
    StatementNumber(const double value);
    ~StatementNumber() override = default;
public:
    double GetValue() const;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters) const override;
public:
    StatementNumber operator+(const StatementNumber& other) const;
    StatementNumber operator-(const StatementNumber& other) const;
    StatementNumber operator*(const StatementNumber& other) const;
    StatementNumber operator/(const StatementNumber& other) const;
    StatementNumber operator^(const StatementNumber& other) const;
#ifdef DEBUG_BUILD
    void LogConcreteType() const override
    {
        std::cout << "StatementNumber";
    }
#endif
};