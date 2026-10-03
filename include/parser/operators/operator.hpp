#pragma once

#include "lexer/types.hpp"
#include "parser/statements/statement_number.hpp"

class Operator
{
public:
    Operator() = default;
    virtual ~Operator() = default;
    virtual StatementNumber Evaluate() const = 0;
};