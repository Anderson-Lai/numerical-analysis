#include "parser/statements/statement_variable.hpp"

StatementVariable::StatementVariable(const Variable& variable) : m_name(variable.GetName())
{

}

StatementVariable::StatementVariable(const std::string& name) : m_name(name)
{

}