#include <vector>

#include "parser/statements/statement_number.hpp"
#include "parser/statements/statement_variable.hpp"

StatementVariable::StatementVariable(const Variable& variable) : m_name(variable.GetName())
{

}

StatementVariable::StatementVariable(const std::string& name) : m_name(name)
{

}

StatementNumber StatementVariable::Evaluate(const std::vector<StatementNumber>& parameters) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Variable evaluation requires exactly one parameter: the value to assign.");
    }

    return parameters.front();
}