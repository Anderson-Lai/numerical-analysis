#pragma once

#include "parser/statements/statement.hpp"

class Integral final : public Statement
{
public:
    Integral() = default;
    ~Integral() override = default;
    virtual StatementNumber Evaluate(const std::vector<StatementNumber>& parameters,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const override;
    std::unique_ptr<Statement> DeepCopy() const override;
private:
    StatementNumber SimpsonsRule(const int subintervals,const StatementNumber& lowerBound,
        const StatementNumber& upperBound, const std::shared_ptr<TreeNode>& inputFunction) const;
    
    StatementNumber IthX(const int subintervals, const StatementNumber& lowerBound,
        const StatementNumber& upperBound, const int i) const;
    
    StatementNumber StepSize(const int subintervals, const StatementNumber& lowerBound,
        const StatementNumber& upperBound) const;
private:
    // temporary value
    static constexpr int SUBINTERVALS = 1e7;
#ifdef DEBUG_BUILD
public:
    virtual void LogConcreteType() const override
    {
        std::cout << "Integral";
    }
#endif
};