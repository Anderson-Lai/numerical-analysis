#pragma once

#include <vector>

#include "parser/statements/statement.hpp"

class Limit final : public Statement
{
public:
    Limit() = default;
    ~Limit() override = default;
    virtual StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override;
private:
    std::vector<StatementNumber> LeftLimit(const StatementNumber& approachingValue,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const;
    std::vector<StatementNumber> RightLimit(const StatementNumber& approachingValue,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const;
private:
    bool CheckExistence(const std::vector<StatementNumber> &leftValues,
        const std::vector<StatementNumber> &rightValues) const;
// helper functions
private:
    bool CheckStability(const std::vector<StatementNumber> &sideValues) const;
    bool IsDecreasing(const std::vector<StatementNumber> &values) const;
private:
    static constexpr double DISCRETIZATION_SIZE = 1e-12;
    static constexpr int STEPS = 1000;
#ifdef DEBUG_BUILD
public:
    virtual void LogConcreteType() const override
    {
        std::cout << "Limit";
    }
#endif
};