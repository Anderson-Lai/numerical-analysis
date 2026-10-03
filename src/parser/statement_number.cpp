#include "parser/statements/statement_number.hpp"

StatementNumber::StatementNumber(const Number& value) : m_value(value.GetValue())
{

}

StatementNumber::StatementNumber(const double value) : m_value(value)
{

}

double StatementNumber::GetValue() const
{
    return m_value;
}

StatementNumber StatementNumber::Evaluate() const
{
    return StatementNumber(m_value);
}

StatementNumber StatementNumber::operator+(const StatementNumber& other) const
{
    return StatementNumber(m_value + other.m_value);
}