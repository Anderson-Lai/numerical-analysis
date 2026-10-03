#pragma once

#include "lexer/types.hpp"

// forward declaration over '#include "..."' to avoid circular dependency
class StatementNumber;

class Statement
{
public:
    Statement() = default;
    virtual ~Statement() = default;
    virtual StatementNumber Evaluate() const = 0;
};