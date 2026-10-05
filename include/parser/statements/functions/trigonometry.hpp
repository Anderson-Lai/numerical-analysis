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
public:
    Cosine(const std::vector<std::shared_ptr<Statement>>& argument);
    ~Cosine() override = default;
    StatementNumber Evaluate() const override;
};

class Tangent final : public Trigonometry
{
public:
    Tangent(const std::vector<std::shared_ptr<Statement>>& argument);
    ~Tangent() override = default;
    StatementNumber Evaluate() const override;
};

class Cosecant final : public Trigonometry
{
public:
    Cosecant(const std::vector<std::shared_ptr<Statement>>& argument);
    ~Cosecant() override = default;
    StatementNumber Evaluate() const override;
};

class Secant final : public Trigonometry
{
public:
    Secant(const std::vector<std::shared_ptr<Statement>>& argument);
    ~Secant() override = default;
    StatementNumber Evaluate() const override;
};

class Cotangent final : public Trigonometry
{
public:
    Cotangent(const std::vector<std::shared_ptr<Statement>>& argument);
    ~Cotangent() override = default;
    StatementNumber Evaluate() const override;
};

class Arcsine final : public Trigonometry
{
public:
    Arcsine(const std::vector<std::shared_ptr<Statement>>& argument);
    ~Arcsine() override = default;
    StatementNumber Evaluate() const override;
};

class Arccosine final : public Trigonometry
{
public:
    Arccosine(const std::vector<std::shared_ptr<Statement>>& argument);
    ~Arccosine() override = default;
    StatementNumber Evaluate() const override;
};

class Arctangent final : public Trigonometry
{
public:
    Arctangent(const std::vector<std::shared_ptr<Statement>>& argument);
    ~Arctangent() override = default;
    StatementNumber Evaluate() const override;
};

class Arccosecant final : public Trigonometry
{
public:
    Arccosecant(const std::vector<std::shared_ptr<Statement>>& argument);
    ~Arccosecant() override = default;
    StatementNumber Evaluate() const override;
};

class Arcsecant final : public Trigonometry
{
public:
    Arcsecant(const std::vector<std::shared_ptr<Statement>>& argument);
    ~Arcsecant() override = default;
    StatementNumber Evaluate() const override;
};

class Arccotangent final : public Trigonometry
{
public:
    Arccotangent(const std::vector<std::shared_ptr<Statement>>& argument);
    ~Arccotangent() override = default;
    StatementNumber Evaluate() const override;
};