#include <cmath>

#include "parser/statements/functions/trigonometry.hpp"
#include "parser/statements/statement_number.hpp"

StatementNumber Sine::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Sine function requires exactly one parameter.");
    }
    const StatementNumber argumentValue = parameters.front();
    return StatementNumber(std::sin(argumentValue.GetValue()));
}

std::unique_ptr<Statement> Sine::DeepCopy() const
{
    return std::make_unique<Sine>(*this);
}

StatementNumber Cosine::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Cosine function requires exactly one parameter.");
    }
    const StatementNumber argumentValue = parameters.front();
    return StatementNumber(std::cos(argumentValue.GetValue()));
}

std::unique_ptr<Statement> Cosine::DeepCopy() const
{
    return std::make_unique<Cosine>(*this);
}

StatementNumber Tangent::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Tangent function requires exactly one parameter.");
    }
    const StatementNumber argumentValue = parameters.front();
    return StatementNumber(std::tan(argumentValue.GetValue()));
}

std::unique_ptr<Statement> Tangent::DeepCopy() const
{
    return std::make_unique<Tangent>(*this);
}

StatementNumber Cosecant::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Cosecant function requires exactly one parameter.");
    }
    const StatementNumber argumentValue = parameters.front();
    return StatementNumber(1.0 / std::sin(argumentValue.GetValue()));
}

std::unique_ptr<Statement> Cosecant::DeepCopy() const
{
    return std::make_unique<Cosecant>(*this);
}

StatementNumber Secant::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Secant function requires exactly one parameter.");
    }
    const StatementNumber argumentValue = parameters.front();
    return StatementNumber(1.0 / std::cos(argumentValue.GetValue()));
}

std::unique_ptr<Statement> Secant::DeepCopy() const
{
    return std::make_unique<Secant>(*this);
}

StatementNumber Cotangent::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Cotangent function requires exactly one parameter.");
    }
    const StatementNumber argumentValue = parameters.front();
    return StatementNumber(1.0 / std::tan(argumentValue.GetValue()));
}

std::unique_ptr<Statement> Cotangent::DeepCopy() const
{
    return std::make_unique<Cotangent>(*this);
}

StatementNumber Arcsine::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Arcsine function requires exactly one parameter.");
    }
    const StatementNumber argumentValue = parameters.front();
    return StatementNumber(std::asin(argumentValue.GetValue()));
}

std::unique_ptr<Statement> Arcsine::DeepCopy() const
{
    return std::make_unique<Arcsine>(*this);
}

StatementNumber Arccosine::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Arccosine function requires exactly one parameter.");
    }
    const StatementNumber argumentValue = parameters.front();
    return StatementNumber(std::acos(argumentValue.GetValue()));
}

std::unique_ptr<Statement> Arccosine::DeepCopy() const
{
    return std::make_unique<Arccosine>(*this);
}

StatementNumber Arctangent::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Arctangent function requires exactly one parameter.");
    }
    const StatementNumber argumentValue = parameters.front();
    return StatementNumber(std::atan(argumentValue.GetValue()));
}

std::unique_ptr<Statement> Arctangent::DeepCopy() const
{
    return std::make_unique<Arctangent>(*this);
}

StatementNumber Arccosecant::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Arccosecant function requires exactly one parameter.");
    }
    const StatementNumber argumentValue = parameters.front();
    return StatementNumber(std::asin(1.0 / argumentValue.GetValue()));
}

std::unique_ptr<Statement> Arccosecant::DeepCopy() const
{
    return std::make_unique<Arccosecant>(*this);
}

StatementNumber Arcsecant::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Arcsecant function requires exactly one parameter.");
    }
    const StatementNumber argumentValue = parameters.front();
    return StatementNumber(std::acos(1.0 / argumentValue.GetValue()));
}

std::unique_ptr<Statement> Arcsecant::DeepCopy() const
{
    return std::make_unique<Arcsecant>(*this);
}

StatementNumber Arccotangent::Evaluate(const std::vector<StatementNumber>& parameters,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    if (parameters.size() != 1)
    {
        throw std::invalid_argument("Arccotangent function requires exactly one parameter.");
    }
    const StatementNumber argumentValue = parameters.front();
    return StatementNumber(std::atan(1.0 / argumentValue.GetValue()));
}

std::unique_ptr<Statement> Arccotangent::DeepCopy() const
{
    return std::make_unique<Arccotangent>(*this);
}