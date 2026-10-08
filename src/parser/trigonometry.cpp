#include "parser/statements/functions/trigonometry.hpp"
#include "parser/statements/statement_number.hpp"
#include <cmath>

StatementNumber Sine::Evaluate(const std::vector<StatementNumber>& parameters) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Sine function requires exactly one parameter.");
    }
    const StatementNumber argumentValue = parameters.front();
    return StatementNumber(std::sin(argumentValue.GetValue()));
}

StatementNumber Cosine::Evaluate(const std::vector<StatementNumber>& parameters) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Cosine function requires exactly one parameter.");
    }
    const StatementNumber argumentValue = parameters.front();
    return StatementNumber(std::cos(argumentValue.GetValue()));
}

StatementNumber Tangent::Evaluate(const std::vector<StatementNumber>& parameters) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Tangent function requires exactly one parameter.");
    }
    const StatementNumber argumentValue = parameters.front();
    return StatementNumber(std::tan(argumentValue.GetValue()));
}

StatementNumber Cosecant::Evaluate(const std::vector<StatementNumber>& parameters) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Cosecant function requires exactly one parameter.");
    }
    const StatementNumber argumentValue = parameters.front();
    return StatementNumber(1.0 / std::sin(argumentValue.GetValue()));
}

StatementNumber Secant::Evaluate(const std::vector<StatementNumber>& parameters) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Secant function requires exactly one parameter.");
    }
    const StatementNumber argumentValue = parameters.front();
    return StatementNumber(1.0 / std::cos(argumentValue.GetValue()));
}

StatementNumber Cotangent::Evaluate(const std::vector<StatementNumber>& parameters) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Cotangent function requires exactly one parameter.");
    }
    const StatementNumber argumentValue = parameters.front();
    return StatementNumber(1.0 / std::tan(argumentValue.GetValue()));
}

StatementNumber Arcsine::Evaluate(const std::vector<StatementNumber>& parameters) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Arcsine function requires exactly one parameter.");
    }
    const StatementNumber argumentValue = parameters.front();
    return StatementNumber(std::asin(argumentValue.GetValue()));
}

StatementNumber Arccosine::Evaluate(const std::vector<StatementNumber>& parameters) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Arccosine function requires exactly one parameter.");
    }
    const StatementNumber argumentValue = parameters.front();
    return StatementNumber(std::acos(argumentValue.GetValue()));
}

StatementNumber Arctangent::Evaluate(const std::vector<StatementNumber>& parameters) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Arctangent function requires exactly one parameter.");
    }
    const StatementNumber argumentValue = parameters.front();
    return StatementNumber(std::atan(argumentValue.GetValue()));
}

StatementNumber Arccosecant::Evaluate(const std::vector<StatementNumber>& parameters) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Arccosecant function requires exactly one parameter.");
    }
    const StatementNumber argumentValue = parameters.front();
    return StatementNumber(std::asin(1.0 / argumentValue.GetValue()));
}

StatementNumber Arcsecant::Evaluate(const std::vector<StatementNumber>& parameters) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Arcsecant function requires exactly one parameter.");
    }
    const StatementNumber argumentValue = parameters.front();
    return StatementNumber(std::acos(1.0 / argumentValue.GetValue()));
}

StatementNumber Arccotangent::Evaluate(const std::vector<StatementNumber>& parameters) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Arccotangent function requires exactly one parameter.");
    }
    const StatementNumber argumentValue = parameters.front();
    return StatementNumber(std::atan(1.0 / argumentValue.GetValue()));
}