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
    bool CheckStability(const std::vector<StatementNumber>& sideValues) const;
    bool IsDifferenceWithinThreshold(const std::vector<StatementNumber>& values) const;
private:
    static constexpr double DISCRETIZATION_SIZE = 1e-12;
    static constexpr int STEPS = 1000;
    // note that threshold is set to 1e-6, which is 3 order of magnitudes greater than maximum discretization size
    // from the approaching value
    static constexpr double STABILITY_THRESHOLD = 1e-6;
#ifdef DEBUG_BUILD
public:
    virtual void LogConcreteType() const override
    {
        std::cout << "Limit";
    }
#endif
};