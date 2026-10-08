#pragma once

#include <vector>

#include "parser/statements/statement.hpp"

class Function : public Statement
{
protected:
    std::vector<std::shared_ptr<Statement>> m_arguments;
public:
    Function() = default;
    virtual ~Function() = default;
    virtual StatementNumber Evaluate(const std::vector<StatementNumber>& parameters) const override = 0;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "Function";
    }
#endif
};