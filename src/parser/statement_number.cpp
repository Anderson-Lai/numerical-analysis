#include "parser/statements/statement_number.hpp"
#include "vector"
#include <cmath>

StatementNumber::StatementNumber(const Number& value) : StatementNumber(value.GetValue())
{

}

StatementNumber::StatementNumber(const double value) : m_value(value)
{

}

double StatementNumber::GetValue() const
{
    return m_value;
}

StatementNumber StatementNumber::Evaluate(const std::vector<StatementNumber>& parameters) const
{
    return StatementNumber(m_value);
}

StatementNumber StatementNumber::operator+(const StatementNumber& other) const
{
    return StatementNumber(m_value + other.m_value);
}

StatementNumber StatementNumber::operator-(const StatementNumber& other) const
{
    return StatementNumber(m_value - other.m_value);
}

StatementNumber StatementNumber::operator*(const StatementNumber& other) const
{
    return StatementNumber(m_value * other.m_value);
}

StatementNumber StatementNumber::operator/(const StatementNumber& other) const
{
    if (other.m_value == 0.0)
    {
        throw std::runtime_error("Division by zero.");
    }
    return StatementNumber(m_value / other.m_value);
}

StatementNumber StatementNumber::operator^(const StatementNumber& other) const
{
    return StatementNumber(std::pow(m_value, other.m_value));
}