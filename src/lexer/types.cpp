#include "lexer/types.hpp"

Number::Number(double value) : m_value(value)
{

}

double Number::GetValue() const
{
    return m_value;
}

Number Number::Concatenate(const Number& other) const
{
    return Number(m_value * 10 + other.m_value);
}

Number Number::InsertDecimalPlace(const Number& other, const int decimalPlace) const
{
    return Number(m_value + other.m_value / std::pow(10, decimalPlace));
}

Variable::Variable(const std::string& name) : m_name(name) 
{

}

const std::string& Variable::GetName() const
{
    return m_name;
}