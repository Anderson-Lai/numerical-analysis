#pragma once

#include "statement.hpp"

class Operator
{
public:
    Operator() = default;
    virtual ~Operator() = default;
    virtual std::unique_ptr<Statement> Evaluate() const = 0;
};