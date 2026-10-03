#pragma once

#include "lexer/types.hpp"

class Statement
{
public:
    Statement() = default;
    virtual ~Statement() = default;
    virtual Number Evaluate() const = 0;
};