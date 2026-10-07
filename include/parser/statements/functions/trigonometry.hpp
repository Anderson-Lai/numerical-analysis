#pragma once

#include "function.hpp"

class Trigonometry : public Function
{
public:
    Trigonometry() = default;
    // argument.size() must be 1
    Trigonometry(const std::vector<std::shared_ptr<Statement>>& argument);
    virtual ~Trigonometry() = default;
    virtual StatementNumber Evaluate() const override = 0;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "Trigonometry";
    }
#endif
};

class Sine final : public Trigonometry
{
public:
    Sine() = default;
    Sine(const std::vector<std::shared_ptr<Statement>>& argument);
    ~Sine() override = default;
    StatementNumber Evaluate() const override;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "Sine";
    }
#endif
};

class Cosine final : public Trigonometry
{
public:
    Cosine() = default;
    Cosine(const std::vector<std::shared_ptr<Statement>>& argument);
    ~Cosine() override = default;
    StatementNumber Evaluate() const override;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "Cosine";
    }
#endif
};

class Tangent final : public Trigonometry
{
public:
    Tangent() = default;
    Tangent(const std::vector<std::shared_ptr<Statement>>& argument);
    ~Tangent() override = default;
    StatementNumber Evaluate() const override;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "Tangent";
    }
#endif
};

class Cosecant final : public Trigonometry
{
public:
    Cosecant() = default;
    Cosecant(const std::vector<std::shared_ptr<Statement>>& argument);
    ~Cosecant() override = default;
    StatementNumber Evaluate() const override;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "Cosecant";
    }
#endif
};

class Secant final : public Trigonometry
{
public:
    Secant() = default;
    Secant(const std::vector<std::shared_ptr<Statement>>& argument);
    ~Secant() override = default;
    StatementNumber Evaluate() const override;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "Secant";
    }
#endif
};

class Cotangent final : public Trigonometry
{
public:
    Cotangent() = default;
    Cotangent(const std::vector<std::shared_ptr<Statement>>& argument);
    ~Cotangent() override = default;
    StatementNumber Evaluate() const override;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "Cotangent";
    }
#endif
};

class Arcsine final : public Trigonometry
{
public:
    Arcsine() = default;
    Arcsine(const std::vector<std::shared_ptr<Statement>>& argument);
    ~Arcsine() override = default;
    StatementNumber Evaluate() const override;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "Arcsine";
    }
#endif
};

class Arccosine final : public Trigonometry
{
public:
    Arccosine() = default;
    Arccosine(const std::vector<std::shared_ptr<Statement>>& argument);
    ~Arccosine() override = default;
    StatementNumber Evaluate() const override;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "Arccosine";
    }
#endif
};

class Arctangent final : public Trigonometry
{
public:
    Arctangent() = default;
    Arctangent(const std::vector<std::shared_ptr<Statement>>& argument);
    ~Arctangent() override = default;
    StatementNumber Evaluate() const override;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "Arctangent";
    }
#endif
};

class Arccosecant final : public Trigonometry
{
public:
    Arccosecant() = default;
    Arccosecant(const std::vector<std::shared_ptr<Statement>>& argument);
    ~Arccosecant() override = default;
    StatementNumber Evaluate() const override;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "Arccosecant";
    }
#endif
};

class Arcsecant final : public Trigonometry
{
public:
    Arcsecant() = default;
    Arcsecant(const std::vector<std::shared_ptr<Statement>>& argument);
    ~Arcsecant() override = default;
    StatementNumber Evaluate() const override;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "Arcsecant";
    }
#endif
};

class Arccotangent final : public Trigonometry
{
public:
    Arccotangent() = default;
    Arccotangent(const std::vector<std::shared_ptr<Statement>>& argument);
    ~Arccotangent() override = default;
    StatementNumber Evaluate() const override;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const override
    {
        std::cout << "Arccotangent";
    }
#endif
};