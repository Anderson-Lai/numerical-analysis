#include "parser/statements/functions/function_argument.hpp"
#include "parser/statements/statement_number.hpp"

StatementNumber FunctionArgument::Evaluate(const std::vector<StatementNumber>& parameters) const
{
    throw std::runtime_error("FunctionArgument::Evaluate() should never be called directly");
}