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
    const StatementNumber argumentValue = m_arguments.front()->Evaluate();
    return StatementNumber(std::sin(argumentValue.GetValue()));
}

Cosine::Cosine(const std::vector<std::shared_ptr<Statement>>& argument) : Trigonometry(argument)
{

}

StatementNumber Cosine::Evaluate() const
{
    const StatementNumber argumentValue = m_arguments.front()->Evaluate();
    return StatementNumber(std::cos(argumentValue.GetValue()));
}

Tangent::Tangent(const std::vector<std::shared_ptr<Statement>>& argument) : Trigonometry(argument)
{

}

StatementNumber Tangent::Evaluate() const
{
    const StatementNumber argumentValue = m_arguments.front()->Evaluate();
    return StatementNumber(std::tan(argumentValue.GetValue()));
}

Cosecant::Cosecant(const std::vector<std::shared_ptr<Statement>>& argument) : Trigonometry(argument)
{

}

StatementNumber Cosecant::Evaluate() const
{
    const StatementNumber argumentValue = m_arguments.front()->Evaluate();
    return StatementNumber(1.0 / std::sin(argumentValue.GetValue()));
}

Secant::Secant(const std::vector<std::shared_ptr<Statement>>& argument) : Trigonometry(argument)
{

}

StatementNumber Secant::Evaluate() const
{
    const StatementNumber argumentValue = m_arguments.front()->Evaluate();
    return StatementNumber(1.0 / std::cos(argumentValue.GetValue()));
}

Cotangent::Cotangent(const std::vector<std::shared_ptr<Statement>>& argument) : Trigonometry(argument)
{

}

StatementNumber Cotangent::Evaluate() const
{
    const StatementNumber argumentValue = m_arguments.front()->Evaluate();
    return StatementNumber(1.0 / std::tan(argumentValue.GetValue()));
}

Arcsine::Arcsine(const std::vector<std::shared_ptr<Statement>>& argument) : Trigonometry(argument)
{

}

StatementNumber Arcsine::Evaluate() const
{
    const StatementNumber argumentValue = m_arguments.front()->Evaluate();
    return StatementNumber(std::asin(argumentValue.GetValue()));
}

Arccosine::Arccosine(const std::vector<std::shared_ptr<Statement>>& argument) : Trigonometry(argument)
{

}

StatementNumber Arccosine::Evaluate() const
{
    const StatementNumber argumentValue = m_arguments.front()->Evaluate();
    return StatementNumber(std::acos(argumentValue.GetValue()));
}

Arctangent::Arctangent(const std::vector<std::shared_ptr<Statement>>& argument) : Trigonometry(argument)
{

}

StatementNumber Arctangent::Evaluate() const
{
    const StatementNumber argumentValue = m_arguments.front()->Evaluate();
    return StatementNumber(std::atan(argumentValue.GetValue()));
}

Arccosecant::Arccosecant(const std::vector<std::shared_ptr<Statement>>& argument) : Trigonometry(argument)
{

}

StatementNumber Arccosecant::Evaluate() const
{
    const StatementNumber argumentValue = m_arguments.front()->Evaluate();
    return StatementNumber(std::asin(1.0 / argumentValue.GetValue()));
}

Arcsecant::Arcsecant(const std::vector<std::shared_ptr<Statement>>& argument) : Trigonometry(argument)
{

}

StatementNumber Arcsecant::Evaluate() const
{
    const StatementNumber argumentValue = m_arguments.front()->Evaluate();
    return StatementNumber(std::acos(1.0 / argumentValue.GetValue()));
}

Arccotangent::Arccotangent(const std::vector<std::shared_ptr<Statement>>& argument) : Trigonometry(argument)
{

}

StatementNumber Arccotangent::Evaluate() const
{
    const StatementNumber argumentValue = m_arguments.front()->Evaluate();
    return StatementNumber(std::atan(1.0 / argumentValue.GetValue()));
}