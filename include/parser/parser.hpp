#pragma once

#include "tree.hpp"
#include <unordered_map>
#include "lexer/token.hpp"
#include <vector>

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
private:
    int GetOperatorBindingPower(const Token& tokenType) const;
    std::shared_ptr<TreeNode> ReadExpression(const std::vector<Token>& tokens, 
        size_t& index, const int minBindingPower);
#ifdef DEBUG_BUILD
public:
    void PrintAST() const
    {
        std::vector<std::vector<std::shared_ptr<TreeNode>>> res;
        auto curr = m_root;
        PrintASTHelper(curr, 0, res);
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
    void PrintASTHelper(std::shared_ptr<TreeNode> curr, int level, 
        std::vector<std::vector<std::shared_ptr<TreeNode>>>& res) const
    {
        if (!curr)
            return;
        if (level >= res.size())
        {
            res.push_back(std::vector<std::shared_ptr<TreeNode>>());
        }
        res[level].push_back(curr);
        if (curr->GetLeft())
        {
            PrintASTHelper(curr->GetLeft(), level + 1, res);
        }
        if (curr->GetRight())
        {
            PrintASTHelper(curr->GetRight(), level + 1, res);
        }
    }
#endif
};