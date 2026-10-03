#include "parser/statements/functions/logarithm.hpp"
#include "statements/statement_number.hpp"

Logarithm::Logarithm(const std::vector<std::shared_ptr<Statement>>& arguments) : Function(std::vector{arguments.back()})
{
    if (arguments.size() != 2)
    {
        throw std::invalid_argument("Logarithm function requires exactly two arguments: the value and the base.");
    }

    const StatementNumber baseValue = m_arguments.front()->Evaluate();
    m_base = baseValue.GetValue();

    if (m_base <= 0.0 || m_base == 1.0)
    {
        throw std::invalid_argument("Logarithm base must be positive and not equal to 1.");
    }
}