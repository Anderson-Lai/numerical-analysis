#include "types.hpp"

Number::Number(double value) : m_value(value)
{

}

double Number::GetValue() const
{
    return m_value;
}

Variable::Variable(char name) : m_name(name) 
{

}

char Variable::GetName() const
{
    return m_name;
}