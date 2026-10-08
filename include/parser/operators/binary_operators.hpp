#pragma once

#include "operator_types.hpp"
#include <vector>
#include "parser/statements/statement_number.hpp"

class AdditionOperator final : public BinaryOperator
{
public:
    AdditionOperator() = default;
    ~AdditionOperator() = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters) const override;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "AdditionOperator";
    }
#endif
};

class SubtractionOperator final : public BinaryOperator
{
public:
    SubtractionOperator() = default;
    ~SubtractionOperator() = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters) const override;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "SubtractionOperator";
    }
#endif
};

class MultiplicationOperator final : public BinaryOperator
{
public:
    MultiplicationOperator() = default;
    ~MultiplicationOperator() = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters) const override;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "MultiplicationOperator";
    }
#endif
};

class DivisionOperator final : public BinaryOperator
{
public:
    DivisionOperator() = default;
    ~DivisionOperator() = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters) const override;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "DivisionOperator";
    }
#endif
};

class ExponentiationOperator final : public BinaryOperator
{
public:
    ExponentiationOperator() = default;
    ~ExponentiationOperator() = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters) const override;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "ExponentiationOperator";
    }
#endif
};