#pragma once

#include <string>

class Number
{
private:
    double m_value;
public:
    Number(const double value);
    double GetValue() const;
};

class Variable
{
private:
    std::string m_name;
public:
    Variable(const std::string& name);
    const std::string& GetName() const;
};