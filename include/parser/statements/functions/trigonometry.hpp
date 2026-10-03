#pragma once

#include "function.hpp"

class Trigonometry : public Function
{
public:
    // argument.size() must be 1
    Trigonometry(const std::vector<std::shared_ptr<Statement>>& argument);
    virtual ~Trigonometry() = default;
    virtual StatementNumber Evaluate() const override = 0;
};

class Sine final : public Trigonometry
{
public:
    Sine(const std::vector<std::shared_ptr<Statement>>& argument);
    ~Sine() override = default;
    StatementNumber Evaluate() const override;
};

class Cosine final : public Trigonometry
{

};

class Tangent final : public Trigonometry
{

};

class Cosecant final : public Trigonometry
{

};

class Secant final : public Trigonometry
{

};

class Cotangent final : public Trigonometry
{

};

class Arcsine final : public Trigonometry
{

};

class Arccosine final : public Trigonometry
{

};

class Arctangent final : public Trigonometry
{

};

class Arccosecant final : public Trigonometry
{

};

class Arcsecant final : public Trigonometry
{

};

class Arccotangent final : public Trigonometry
{

};