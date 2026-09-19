#pragma once

#include <memory>

class Statement
{
public:
    Statement() = default;
    virtual ~Statement() = default;
    virtual std::unique_ptr<Statement> Evaluate() const = 0;
};