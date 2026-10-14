#include "analysis/derivative.hpp"

#include "parser/statements/statement_number.hpp"

StatementNumber Derivative::Evaluate(const std::vector<StatementNumber>& parameters) const
{
    if (parameters.size() != 2)
    {
        throw std::invalid_argument("Derivative requires exactly 2 parameters");
    }

    throw std::runtime_error("Derivative evaluation not implemented yet");
}