#include "parser/statements/statement_variable.hpp"
#include "parser/statements/statement_number.hpp"

StatementVariable::StatementVariable(const Variable& variable) : m_name(variable.GetName())
{

}

StatementVariable::StatementVariable(const std::string& name) : m_name(name)
{

}

StatementNumber StatementVariable::Evaluate() const
{
    // placeholder value
    return StatementNumber(-1);
}