#pragma once

#include <vector>
#include <unordered_map>

#include "lexer/token.hpp"

#include "parser/statements/statement_number.hpp"
#include "parser/tree.hpp"

class Parser
{
private:
    std::shared_ptr<TreeNode> m_root;
private:
    inline static const std::unordered_map<TokenType, int> OPERATOR_BINDING_POWER =
    {
        {TokenType::ADDITION, 10},
        {TokenType::SUBTRACTION, 10},
        {TokenType::DIVISION, 20},
        {TokenType::MULTIPLICATION, 20},
        {TokenType::SUBSCRIPT, 30},
        {TokenType::EXPONENTIATION, 40}
    };
public:
    Parser() = default;
    ~Parser() = default;
    void Parse(const std::vector<Token>& tokens);
    StatementNumber EvaluateAST() const;
#ifdef DEBUG_EXPRESSIONS
    StatementNumber EvaluateAST(const StatementNumber& value) const;
#endif
public:
    std::shared_ptr<TreeNode> GetRoot() const;
private:
    std::shared_ptr<TreeNode> ReadExpression(const std::vector<Token>& tokens,
        size_t& index, const int minBindingPower, const bool fromFunctionCall = false) const;

    std::shared_ptr<TreeNode> ReadFullExpression(const std::vector<Token>& tokens, size_t& index, 
        const int minBindingPower) const;
// helper functions for building AST
private:
    std::shared_ptr<TreeNode> GetArguments(const std::vector<Token>& tokens, size_t& index,
        const bool fromFunctionCall = false) const;
    int GetOperatorBindingPower(const Token& tokenType) const;
    bool IsFunctionIdentifier(const Token& token) const;
#ifdef DEBUG_BUILD
public:
    static void PrintAST(const std::shared_ptr<TreeNode>& root)
    {
        std::vector<std::vector<std::shared_ptr<TreeNode>>> res;
        PrintASTHelper(root, 0, res);
        for (int i = 0; i < res.size(); i++)
        {
            std::cout << "Depth: " << i << std::endl;
            for (int j = 0; j < res[i].size(); j++)
            {
                if (res[i][j]->GetValue())
                {
                    res[i][j]->GetValue()->LogConcreteType();
                }
                else
                {
                    std::cout << "nullptr";
                }
                std::cout << "\t";
            }
            std::cout << std::endl << std::endl;
        }
    }
private:
    static void PrintASTHelper(const std::shared_ptr<TreeNode>& curr, const int level, 
        std::vector<std::vector<std::shared_ptr<TreeNode>>>& res)
    {
        if (!curr)
            return;
        if (level >= res.size())
        {
            res.push_back(std::vector<std::shared_ptr<TreeNode>>());
        }
        res[level].push_back(curr);

        if (!curr->GetChildren().empty())
        {
            for (const auto& child : curr->GetChildren())
            {
                PrintASTHelper(child, level + 1, res);
            }
        }
    }
#endif
};