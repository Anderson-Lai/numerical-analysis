#include "parser/parser.hpp"
#include "parser/tree.hpp"
#include "parser/statements/statement_variable.hpp"
#include "parser/statements/statement_number.hpp"
#include "parser/operators/binary_operators.hpp"

void Parser::Parse(const std::vector<Token>& tokens)
{
    m_root = std::make_shared<TreeNode>(nullptr, nullptr, nullptr, nullptr);
}

std::shared_ptr<TreeNode> Parser::ReadExpression(const std::vector<Token>& tokens, size_t& index, const int minBindingPower)
{
    auto left = std::make_shared<TreeNode>(nullptr, nullptr, nullptr, nullptr);
    auto node = std::make_shared<TreeNode>(left, nullptr, nullptr, nullptr);

    const Token& currentToken = tokens[index];
    int currentBindingPower = GetOperatorBindingPower(currentToken);

    while (index < tokens.size() && minBindingPower < currentBindingPower)
    {
        // implement implicit multiplication later
        if (std::holds_alternative<Number>(currentToken))
        {
            left->SetValue(std::make_shared<StatementNumber>(std::get<Number>(currentToken)));
            index++;
        }
        else if (std::holds_alternative<Variable>(currentToken))
        {
            left->SetValue(std::make_shared<StatementVariable>(std::get<Variable>(currentToken)));
            index++;
        }

        // recursive part of pratt parsing
        else if (std::holds_alternative<TokenType>(currentToken))
        {
            const TokenType& currentTokenType = std::get<TokenType>(currentToken);
            // since exponentiation is right associative
            int associativity = (currentTokenType == TokenType::EXPONENTIATION) ? 1 : 0;

            switch (currentTokenType)
            {
                case TokenType::ADDITION:
                    node->SetValue(std::make_shared<AdditionOperator>());
                    node->SetLeft(left);
                    node->SetRight(ReadExpression(tokens, ++index, currentBindingPower));
                    break;
                case TokenType::SUBTRACTION:
                    node->SetValue(std::make_shared<SubtractionOperator>());
                    node->SetLeft(left);
                    node->SetRight(ReadExpression(tokens, ++index, currentBindingPower));
                    break;
                case TokenType::MULTIPLICATION:
                    node->SetValue(std::make_shared<MultiplicationOperator>());
                    node->SetLeft(left);
                    node->SetRight(ReadExpression(tokens, ++index, currentBindingPower));
                    break;
                case TokenType::DIVISION:
                    node->SetValue(std::make_shared<DivisionOperator>());
                    node->SetLeft(left);
                    node->SetRight(ReadExpression(tokens, ++index, currentBindingPower));
                    break;
                case TokenType::EXPONENTIATION:
                    node->SetValue(std::make_shared<ExponentiationOperator>());
                    node->SetLeft(left);
                    node->SetRight(ReadExpression(tokens, ++index, currentBindingPower + associativity));
                    break;
                case TokenType::PARANTHESES_OPEN:
                    node->SetValue(ReadExpression(tokens, ++index, 0)->GetValue());
                    break;
                default:
                    throw std::runtime_error("Unexpected token");
            }
        }
        else
        {
            throw std::runtime_error("Unexpected token");
        }
    }

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