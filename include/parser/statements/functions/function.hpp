#pragma once

#include <vector>
#include "statements/statement.hpp"

class Function : Statement
{
protected:
    std::vector<std::unique_ptr<Statement>> m_arguments;
public:
    Function() = default;
    virtual ~Function() = default;
    virtual Number Evaluate() const override = 0;
};