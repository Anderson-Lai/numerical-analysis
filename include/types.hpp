#pragma once

class Number
{
private:
    double m_value;
public:
    Number(double value);
    double GetValue() const;
};

class Variable
{
private:
    char m_name;
public:
    Variable(char name);
    char GetName() const;
};