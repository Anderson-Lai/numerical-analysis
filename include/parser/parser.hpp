#pragma once

#include "tree.hpp"
#include "lexer/lexer.hpp"
#include <unordered_map>

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
        {TokenType::EXPONENTIATION, 30}
    };
public:
    Parser() = default;
    ~Parser() = default;
    void Parse(const std::vector<Token>& tokens);
private:
    int GetOperatorBindingPower(const Token& tokenType) const;
    std::shared_ptr<TreeNode> ReadExpression(const std::vector<Token>& tokens, size_t& index, const int minBindingPower);
};