#include "parser/parser.hpp"
#include "parser/tree.hpp"
#include "parser/statements/statement_variable.hpp"
#include "parser/statements/statement_number.hpp"

void Parser::Parse(const std::vector<Token>& tokens)
{
    m_root = std::make_shared<TreeNode>(nullptr, nullptr, nullptr);
}

std::shared_ptr<TreeNode> Parser::ReadExpression(const std::vector<Token>& tokens, size_t& index, const int minBindingPower)
{
    auto node = std::make_shared<TreeNode>(nullptr, nullptr, nullptr);

    return node;
}

int Parser::GetOperatorBindingPower(const Token& tokenType) const
{
    if (!std::holds_alternative<TokenType>(tokenType))
    {
        return -1;
    }

    if (OPERATOR_BINDING_POWER.find(std::get<TokenType>(tokenType)) != OPERATOR_BINDING_POWER.end())
    {
        return OPERATOR_BINDING_POWER.at(std::get<TokenType>(tokenType));
    }
    return -1;
}