#pragma once

#include "lexer/types.hpp"
#include "parser/statements/statement_number.hpp"

class Operator : public Statement
{
public:
    Operator() = default;
    virtual ~Operator() = default;
    virtual StatementNumber Evaluate() const override = 0;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "Operator";
    }
#endif
};