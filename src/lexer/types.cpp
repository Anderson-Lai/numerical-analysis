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

Variable::Variable(const std::string& name) : m_name(name) 
{

}

const std::string& Variable::GetName() const
{
    return m_name;
}