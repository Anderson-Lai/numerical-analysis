#pragma once

#include "parser/statements/functions/function.hpp"

#ifdef DEBUG_BUILD
#include <iostream>
#endif

class SquareRoot final : public Function
{
public:
    SquareRoot() = default;
    ~SquareRoot() override = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override;
#ifdef DEBUG_BUILD
    void LogConcreteType() const override
    {
        std::cout << "SquareRoot";
    }
#endif
};

class CubeRoot final : public Function
{
public:
    CubeRoot() = default;
    ~CubeRoot() override = default;
    StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override;
#ifdef DEBUG_BUILD
    void LogConcreteType() const override
    {
        std::cout << "CubeRoot";
    }
#endif
};