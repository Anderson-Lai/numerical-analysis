#pragma once

#include "lexer/types.hpp"

#ifdef DEBUG_BUILD
#include <iostream>
#endif

// forward declaration over '#include "..."' to avoid circular dependency
class StatementNumber;

class Statement
{
public:
    Statement() = default;
    virtual ~Statement() = default;
    virtual StatementNumber Evaluate() const = 0;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const
    {
        std::cout << "Generic Statement";
    }
#endif
};