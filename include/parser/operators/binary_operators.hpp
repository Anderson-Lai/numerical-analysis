#pragma once

#include "operator_types.hpp"

class Addition final : public BinaryOperator
{
public:
    Addition() = default;
    ~Addition() = default;
    Number Evaluate() const override;
};

class Subtraction final : public BinaryOperator
{
public:
    Subtraction() = default;
    ~Subtraction() = default;
    Number Evaluate() const override;
};

class Multiplication final : public BinaryOperator
{
public:
    Multiplication() = default;
    ~Multiplication() = default;
    Number Evaluate() const override;
};

class Division final : public BinaryOperator
{
public:
    Division() = default;
    ~Division() = default;
    Number Evaluate() const override;
};

class Exponentiation final : public BinaryOperator
{
public:
    Exponentiation() = default;
    ~Exponentiation() = default;
    Number Evaluate() const override;
};