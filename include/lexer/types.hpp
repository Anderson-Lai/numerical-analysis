#pragma once

#include <string>

class Number
{
private:
    double m_value;
public:
    Number(const double value);
    double GetValue() const;
    Number operator+(const Number& other) const;
    Number Concatenate(const Number& other) const;
};

class Variable
{
private:
    std::string m_name;
public:
    Variable(const std::string& name);
    const std::string& GetName() const;
};