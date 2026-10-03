#include "parser/statements/functions/trigonometry.hpp"
#include "parser/statements/statement_number.hpp"
#include <cmath>

Trigonometry::Trigonometry(const std::vector<std::shared_ptr<Statement>>&argument) : Function(argument)
{
    if (argument.size() != 1)
    {
        throw std::invalid_argument("Trigonometric functions require exactly one argument.");
    }
}

Sine::Sine(const std::vector<std::shared_ptr<Statement>>& argument) : Trigonometry(argument)
{

}

StatementNumber Sine::Evaluate() const
{
    StatementNumber argumentValue = m_arguments.front()->Evaluate();
    return StatementNumber(std::sin(argumentValue.GetValue()));
}