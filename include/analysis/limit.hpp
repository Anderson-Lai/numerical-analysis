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
    std::unique_ptr<Statement> DeepCopy() const override;
private:
    std::vector<StatementNumber> LeftLimit(const StatementNumber& approachingValue,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const;
    std::vector<StatementNumber> RightLimit(const StatementNumber& approachingValue,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const;
private:
    bool CheckExistence(const std::vector<StatementNumber>& leftValues,
        const std::vector<StatementNumber>& rightValues) const;
// helper functions
private:
    bool IsDecreasingWithinThreshold(const std::vector<double>& values) const;
    // bool CheckStability(const std::vector<StatementNumber>& sideValues) const;
    // bool IsDifferenceWithinThreshold(const std::vector<StatementNumber>& values) const;
private:
    // square root of machine epsilon for approximate best discretization size
    static constexpr double DISCRETIZATION_SIZE = 1e-8;
    static constexpr int STEPS = 1e2;
    // note that threshold is set to 1e-3, which is 6 order of magnitudes greater than maximum discretization size
    // from the approaching value
    static constexpr double STABILITY_THRESHOLD = 1e-3;
#ifdef DEBUG_BUILD
public:
    virtual void LogConcreteType() const override
    {
        std::cout << "Limit";
    }
#endif
};