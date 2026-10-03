#pragma once

#include "statement.hpp"
#include "lexer/types.hpp"

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
    StatementNumber Evaluate() const override;
public:
    StatementNumber operator+(const StatementNumber& other) const;
    StatementNumber operator-(const StatementNumber& other) const;
    StatementNumber operator*(const StatementNumber& other) const;
    StatementNumber operator/(const StatementNumber& other) const;
    StatementNumber operator^(const StatementNumber& other) const;

#ifdef DEBUG_BUILD
    void PrintValue() const {
        std::cout << "StatementNumber: " << m_value << std::endl;
    }
#endif
};