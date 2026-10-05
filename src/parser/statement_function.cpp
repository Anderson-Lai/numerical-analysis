#include "parser/statements/statement_function.hpp"
#include "parser/statements/statement_number.hpp"

StatementNumber StatementFunction::Evaluate() const
{
    return m_function->Evaluate();
}