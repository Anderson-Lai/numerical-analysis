#pragma once

#include "operator_types.hpp"

class Addition : BinaryOperator
{
public:
    Addition() = default;
    ~Addition() = default;
    Number Evaluate() const override;
};

class Subtraction : BinaryOperator
{
public:
    Subtraction() = default;
    ~Subtraction() = default;
    Number Evaluate() const override;
};

class Multiplication : BinaryOperator
{
public:
    Multiplication() = default;
    ~Multiplication() = default;
    Number Evaluate() const override;
};

class Division : BinaryOperator
{
public:
    Division() = default;
    ~Division() = default;
    Number Evaluate() const override;
};

class Exponentiation : BinaryOperator
{
public:
    Exponentiation() = default;
    ~Exponentiation() = default;
    Number Evaluate() const override;
};