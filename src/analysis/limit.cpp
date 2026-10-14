#include "analysis/limit.hpp"

#include "parser/statements/statement_number.hpp"

StatementNumber Limit::Evaluate(const std::vector<StatementNumber>& parameters) const
{
    if (parameters.size() != 2)
    {
        throw std::invalid_argument("Limit requires exactly 2 parameters");
    }

    throw std::runtime_error("Limit evaluation not implemented yet");
}