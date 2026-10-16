#pragma once

#include <memory>
#include <vector>

#include "lexer/types.hpp"

#ifdef DEBUG_BUILD
#include <iostream>
#endif

// forward declaration over '#include "..."' to avoid circular dependency
class StatementNumber;
class TreeNode;

class Statement
{
public:
    Statement() = default;
    virtual ~Statement() = default;
    // avoid the use of 'rawArguments' where possible (only intended use is derivatives, integrals, limits, 
    // series, etc., where the need of the raw argument (input function) is needed for evaluation / approximation)
    virtual StatementNumber Evaluate(const std::vector<StatementNumber>& computedArguments,
        const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const = 0;
    virtual std::unique_ptr<Statement> DeepCopy() const = 0;
#ifdef DEBUG_BUILD
    virtual void LogConcreteType() const
    {
        std::cout << "Generic Statement";
    }
#endif
};