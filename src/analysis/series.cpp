#include "analysis/series.hpp"

#include "parser/statements/statement_number.hpp"

StatementNumber Series::Evaluate(const std::vector<StatementNumber>& parameters) const
{
    if (parameters.size() != 3)
    {
        throw std::invalid_argument("Series requires exactly 3 parameters");
    }

    throw std::runtime_error("Series evaluation not implemented yet");
}