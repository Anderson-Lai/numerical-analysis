#pragma once

#include "operators.hpp"

class Addition : BinaryOperator
{
public:
    Addition() = default;
    ~Addition() = default;
    std::unique_ptr<Statement> Evaluate() const override;
};

class Subtraction : BinaryOperator
{
public:
    Subtraction() = default;
    ~Subtraction() = default;
    std::unique_ptr<Statement> Evaluate() const override;
};

class Multiplication : BinaryOperator
{
public:
    Multiplication() = default;
    ~Multiplication() = default;
    std::unique_ptr<Statement> Evaluate() const override;
};

class Division : BinaryOperator
{
public:
    Division() = default;
    ~Division() = default;
    std::unique_ptr<Statement> Evaluate() const override;
};

class Exponentiation : BinaryOperator
{
public:
    Exponentiation() = default;
    ~Exponentiation() = default;
    std::unique_ptr<Statement> Evaluate() const override;
};