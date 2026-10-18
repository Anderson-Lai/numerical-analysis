#include "analysis/derivative.hpp"
#include "analysis/limit.hpp"

#include "parser/operators/binary_operators.hpp"
#include "parser/statements/statement_number.hpp"
#include "parser/statements/statement_variable.hpp"
#include "parser/tree.hpp"

StatementNumber Derivative::Evaluate(const std::vector<StatementNumber>&,
    const std::vector<std::shared_ptr<TreeNode>>& rawArguments) const
{
    if (rawArguments.size() != 2)
    {
        throw std::invalid_argument("Derivative requires exactly 2 parameters");
    }

    const StatementNumber& point = rawArguments.front() ? 
        rawArguments.front()->EvaluateNode(0.0) : StatementNumber(0.0);
    const std::shared_ptr<TreeNode>& inputFunction = rawArguments.back();

    // we first use the definition of the derivative to verify the existence of the derivative
    // then we use central differences to approximate the derivative since it
    // gains more digits of accuracy faster
    try
    {
        const StatementNumber existenceCheck = VerifyExistence(point, inputFunction);
        const StatementNumber derivativeApproximation = ApproximateDerivative(point, inputFunction);

        // quick sanity check that everything has gone right
        if (std::abs(existenceCheck.GetValue() - derivativeApproximation.GetValue()) > 1e-6)
        {
            throw std::runtime_error("Derivative does not exist");
        }

        return derivativeApproximation;
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error("Derivative does not exist");
    }

    throw std::runtime_error("Derivative does not exist");
}

std::unique_ptr<Statement> Derivative::DeepCopy() const
{
    return std::make_unique<Derivative>(*this);
}

/*
       we need to construct the arguments for the limits, so:
           f(variable) -> f(point + variable)
           f(variable) -> f(point)

       so then we have f(point + variable) - f(point) / variable and take variable -> 0, 
       which is the definition of the derivative
*/
StatementNumber Derivative::VerifyExistence(const StatementNumber& point,
    const std::shared_ptr<TreeNode>& inputFunction) const
{
    const std::shared_ptr<TreeNode> firstCopy = CopyAST(inputFunction);
    const std::shared_ptr<TreeNode> secondCopy = CopyAST(inputFunction);

    const std::shared_ptr<TreeNode> firstReplacement = std::make_shared<TreeNode>(
        std::make_shared<AdditionOperator>(),
        std::vector<std::shared_ptr<TreeNode>>{
            std::make_shared<TreeNode>(std::make_shared<StatementNumber>(point)),
            std::make_shared<TreeNode>(std::make_shared<StatementVariable>("x"))
        }
    );

    ReplaceVariableWith(firstCopy, firstReplacement);
    ReplaceVariableWith(secondCopy, std::make_shared<TreeNode>(std::make_shared<StatementNumber>(point)));

    const std::shared_ptr<TreeNode> numerator = std::make_shared<TreeNode>(
        std::make_shared<SubtractionOperator>(), 
        std::vector<std::shared_ptr<TreeNode>>{firstCopy, secondCopy}
    );

    const std::shared_ptr<TreeNode> limitArgument = std::make_shared<TreeNode>(
        std::make_shared<DivisionOperator>(), 
        std::vector<std::shared_ptr<TreeNode>>{
            numerator, 
            std::make_shared<TreeNode>(std::make_shared<StatementVariable>("x"))
        }
    );

    const std::shared_ptr<TreeNode> limitNode = std::make_shared<TreeNode>(
        std::make_shared<Limit>(), 
        std::vector<std::shared_ptr<TreeNode>>{
            std::make_shared<TreeNode>(std::make_shared<StatementNumber>(0.0)), 
            limitArgument
        }
    );

    return limitNode->GetValue()->Evaluate(std::vector<StatementNumber>{}, limitNode->GetChildren());
}

/*
    we use central differences, so:
    f(variable) -> f(point + variable)
    f(variable) -> f(point - variable)

    then we can take f(point + variable) - f(point - variable) / (2 * variable) and take variable -> 0,
    which is the central difference approximation of the derivative
*/
StatementNumber Derivative::ApproximateDerivative(const StatementNumber& point,
    const std::shared_ptr<TreeNode>& inputFunction) const
{
    const std::shared_ptr<TreeNode> firstCopy = CopyAST(inputFunction);
    const std::shared_ptr<TreeNode> secondCopy = CopyAST(inputFunction);

    const std::shared_ptr<TreeNode> firstReplacement = std::make_shared<TreeNode>(
        std::make_shared<AdditionOperator>(),
        std::vector<std::shared_ptr<TreeNode>>{
            std::make_shared<TreeNode>(std::make_shared<StatementNumber>(point)),
            std::make_shared<TreeNode>(std::make_shared<StatementVariable>("x"))
        }
    );

    const std::shared_ptr<TreeNode> secondReplacement = std::make_shared<TreeNode>(
        std::make_shared<SubtractionOperator>(),
        std::vector<std::shared_ptr<TreeNode>>{
            std::make_shared<TreeNode>(std::make_shared<StatementNumber>(point)),
            std::make_shared<TreeNode>(std::make_shared<StatementVariable>("x"))
        }
    );

    ReplaceVariableWith(firstCopy, firstReplacement);
    ReplaceVariableWith(secondCopy, secondReplacement);

    const std::shared_ptr<TreeNode> numerator = std::make_shared<TreeNode>(
        std::make_shared<SubtractionOperator>(), 
        std::vector<std::shared_ptr<TreeNode>>{
            firstCopy, 
            secondCopy
        }
    );

    const std::shared_ptr<TreeNode> denominator = std::make_shared<TreeNode>(
        std::make_shared<MultiplicationOperator>(), 
        std::vector<std::shared_ptr<TreeNode>>{
            std::make_shared<TreeNode>(std::make_shared<StatementNumber>(2.0)), 
            std::make_shared<TreeNode>(std::make_shared<StatementVariable>("x"))
        }
    );

    const std::shared_ptr<TreeNode> limitArgument = std::make_shared<TreeNode>(
        std::make_shared<DivisionOperator>(), 
        std::vector<std::shared_ptr<TreeNode>>{
            numerator, 
            denominator
        }
    );

    const std::shared_ptr<TreeNode> limitNode = std::make_shared<TreeNode>(
        std::make_shared<Limit>(), 
        std::vector<std::shared_ptr<TreeNode>>{
            std::make_shared<TreeNode>(std::make_shared<StatementNumber>(0.0)), 
            limitArgument
        }
    );

    return limitNode->GetValue()->Evaluate(std::vector<StatementNumber>{}, limitNode->GetChildren());
}

void Derivative::ReplaceVariableWith(const std::shared_ptr<TreeNode>& node, 
    const std::shared_ptr<TreeNode>& replacement) const
{
    if (!replacement)
    {
        throw std::invalid_argument("Replacement node is nullptr");
    }
    if (!node)
    {
        return;
    }

    if (node->GetValue() && std::dynamic_pointer_cast<StatementVariable>(node->GetValue()))
    {
        node->SetValue(replacement->GetValue());
        node->SetChildren(replacement->GetChildren());
    }
    else
    {
        for (const std::shared_ptr<TreeNode>& child : node->GetChildren())
        {
            ReplaceVariableWith(child, replacement);
        }
    }
}

std::shared_ptr<TreeNode> Derivative::CopyAST(const std::shared_ptr<TreeNode>& node) const
{
    if (!node)
    {
        return nullptr;
    }

    std::vector<std::shared_ptr<TreeNode>> copiedChildren;
    std::vector<std::shared_ptr<TreeNode>> children = node->GetChildren();
    copiedChildren.reserve(children.size());

    for (const std::shared_ptr<TreeNode>& child : children)
    {
        copiedChildren.emplace_back(CopyAST(child));
    }

    return std::make_shared<TreeNode>(node->GetValue() ? node->GetValue()->DeepCopy() : nullptr, copiedChildren);
}