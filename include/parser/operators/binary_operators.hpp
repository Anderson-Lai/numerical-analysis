#pragma once

#include "operator_types.hpp"

class AdditionOperator final : public BinaryOperator
{
public:
    AdditionOperator() = default;
    ~AdditionOperator() = default;
    StatementNumber Evaluate() const override;
};

class SubtractionOperator final : public BinaryOperator
{
public:
    SubtractionOperator() = default;
    ~SubtractionOperator() = default;
    StatementNumber Evaluate() const override;
};

class MultiplicationOperator final : public BinaryOperator
{
public:
    MultiplicationOperator() = default;
    ~MultiplicationOperator() = default;
    StatementNumber Evaluate() const override;
};

class DivisionOperator final : public BinaryOperator
{
public:
    DivisionOperator() = default;
    ~DivisionOperator() = default;
    StatementNumber Evaluate() const override;
};

class ExponentiationOperator final : public BinaryOperator
{
public:
    ExponentiationOperator() = default;
    ~ExponentiationOperator() = default;
    StatementNumber Evaluate() const override;
};