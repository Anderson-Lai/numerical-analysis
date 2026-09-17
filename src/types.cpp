#include "types.hpp"

Number::Number(double value) : m_value(value)
{

}

double Number::GetValue() const
{
    return m_value;
}

Variable::Variable(const std::string& name) : m_name(name) 
{

}

const std::string& Variable::GetName() const
{
    return m_name;
}