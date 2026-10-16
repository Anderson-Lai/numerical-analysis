#pragma once

#include "parser/statements/functions/function.hpp"

class Trigonometry : public Function
{
public:
    Trigonometry() = default;
    virtual ~Trigonometry() = default;
    virtual StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override = 0;
    virtual std::unique_ptr<Statement> DeepCopy() const override = 0;
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
    ~Sine() override = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override;
    std::unique_ptr<Statement> DeepCopy() const override;
#ifdef DEBUG_BUILD
    void LogConcreteType() const override
    {
        std::cout << "Sine";
    }
#endif
};

class Cosine final : public Trigonometry
{
public:
    Cosine() = default;
    ~Cosine() override = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override;
    std::unique_ptr<Statement> DeepCopy() const override;
#ifdef DEBUG_BUILD
    void LogConcreteType() const override
    {
        std::cout << "Cosine";
    }
#endif
};

class Tangent final : public Trigonometry
{
public:
    Tangent() = default;
    ~Tangent() override = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override;
    std::unique_ptr<Statement> DeepCopy() const override;
#ifdef DEBUG_BUILD
    void LogConcreteType() const override
    {
        std::cout << "Tangent";
    }
#endif
};

class Cosecant final : public Trigonometry
{
public:
    Cosecant() = default;
    ~Cosecant() override = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override;
    std::unique_ptr<Statement> DeepCopy() const override;
#ifdef DEBUG_BUILD
    void LogConcreteType() const override
    {
        std::cout << "Cosecant";
    }
#endif
};

class Secant final : public Trigonometry
{
public:
    Secant() = default;
    ~Secant() override = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override;
    std::unique_ptr<Statement> DeepCopy() const override;
#ifdef DEBUG_BUILD
    void LogConcreteType() const override
    {
        std::cout << "Secant";
    }
#endif
};

class Cotangent final : public Trigonometry
{
public:
    Cotangent() = default;
    ~Cotangent() override = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override;
    std::unique_ptr<Statement> DeepCopy() const override;
#ifdef DEBUG_BUILD
    void LogConcreteType() const override
    {
        std::cout << "Cotangent";
    }
#endif
};

class Arcsine final : public Trigonometry
{
public:
    Arcsine() = default;
    ~Arcsine() override = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override;
    std::unique_ptr<Statement> DeepCopy() const override;
#ifdef DEBUG_BUILD
    void LogConcreteType() const override
    {
        std::cout << "Arcsine";
    }
#endif
};

class Arccosine final : public Trigonometry
{
public:
    Arccosine() = default;
    ~Arccosine() override = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override;
    std::unique_ptr<Statement> DeepCopy() const override;
#ifdef DEBUG_BUILD
    void LogConcreteType() const override
    {
        std::cout << "Arccosine";
    }
#endif
};

class Arctangent final : public Trigonometry
{
public:
    Arctangent() = default;
    ~Arctangent() override = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override;
    std::unique_ptr<Statement> DeepCopy() const override;
#ifdef DEBUG_BUILD
    void LogConcreteType() const override
    {
        std::cout << "Arctangent";
    }
#endif
};

class Arccosecant final : public Trigonometry
{
public:
    Arccosecant() = default;
    ~Arccosecant() override = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override;
    std::unique_ptr<Statement> DeepCopy() const override;
#ifdef DEBUG_BUILD
    void LogConcreteType() const override
    {
        std::cout << "Arccosecant";
    }
#endif
};

class Arcsecant final : public Trigonometry
{
public:
    Arcsecant() = default;
    ~Arcsecant() override = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override;
    std::unique_ptr<Statement> DeepCopy() const override;
#ifdef DEBUG_BUILD
    void LogConcreteType() const override
    {
        std::cout << "Arcsecant";
    }
#endif
};

class Arccotangent final : public Trigonometry
{
public:
    Arccotangent() = default;
    ~Arccotangent() override = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override;
    std::unique_ptr<Statement> DeepCopy() const override;
#ifdef DEBUG_BUILD
    void LogConcreteType() const override
    {
        std::cout << "Arccotangent";
    }
#endif
};