#pragma once

#include "lexer/types.hpp"

class Operator
{
public:
    Operator() = default;
    virtual ~Operator() = default;
    virtual Number Evaluate() const = 0;
};