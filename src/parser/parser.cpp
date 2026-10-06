#include "parser/parser.hpp"
#include "parser/tree.hpp"
#include "parser/statements/statement_variable.hpp"
#include "parser/statements/statement_number.hpp"
#include "parser/operators/binary_operators.hpp"
#include "parser/statements/statement_function.hpp"
#include "parser/statements/functions/trigonometry.hpp"
#include "parser/statements/functions/logarithm.hpp"
#include <cmath>

void Parser::Parse(const std::vector<Token>& tokens)
{
    if (tokens.empty())
    {
        throw std::runtime_error("No tokens in expression");
    }

    size_t index = 0;
    m_root = ReadExpression(tokens, index, 0);
    // not sure if this is needed; further testing needs to be done
    index++;

    while (index < tokens.size())
    {
        auto result = ReadExpression(tokens, index, 0);
        index++;
        result->SetLeft(m_root);
        m_root = result;
    }
}

std::shared_ptr<TreeNode> Parser::ReadExpression(const std::vector<Token>& tokens, size_t& index, const int minBindingPower)
{
    auto node = std::make_shared<TreeNode>(nullptr, nullptr, nullptr, nullptr);
    auto data = std::make_shared<TreeNode>(nullptr, nullptr, nullptr, nullptr);

    Token currentToken = tokens[index];
    int currentBindingPower = GetOperatorBindingPower(currentToken);

    while (index < tokens.size() && (minBindingPower < currentBindingPower || currentBindingPower == -1))
    {
        currentToken = tokens[index];
        currentBindingPower = GetOperatorBindingPower(currentToken);

        // implement implicit multiplication later
        if (std::holds_alternative<Number>(currentToken))
        {
            data->SetValue(std::make_shared<StatementNumber>(std::get<Number>(currentToken)));
            index++;
        }
        else if (std::holds_alternative<Variable>(currentToken))
        {
            data->SetValue(std::make_shared<StatementVariable>(std::get<Variable>(currentToken)));
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
                    node->SetLeft(data);
                    node->SetValue(std::make_shared<AdditionOperator>());
                    node->SetRight(ReadExpression(tokens, ++index, currentBindingPower));
                    break;
                case TokenType::SUBTRACTION:
                    node->SetLeft(data);
                    node->SetValue(std::make_shared<SubtractionOperator>());
                    node->SetRight(ReadExpression(tokens, ++index, currentBindingPower));
                    break;
                case TokenType::MULTIPLICATION:
                    node->SetLeft(data);
                    node->SetValue(std::make_shared<MultiplicationOperator>());
                    node->SetRight(ReadExpression(tokens, ++index, currentBindingPower));
                    break;
                case TokenType::DIVISION:
                    node->SetLeft(data);
                    node->SetValue(std::make_shared<DivisionOperator>());
                    node->SetRight(ReadExpression(tokens, ++index, currentBindingPower));
                    break;
                // to implement later; subscript is a UNARY operator
                case TokenType::SUBSCRIPT:
                    break;
                case TokenType::EXPONENTIATION:
                    node->SetLeft(data);
                    node->SetValue(std::make_shared<ExponentiationOperator>());
                    node->SetRight(ReadExpression(tokens, ++index, currentBindingPower + associativity));
                    break;
                case TokenType::PARANTHESES_OPEN:
                    // possible issues when adding implicit multiplication
                    // since 'left' is ignored here
                    node = ReadExpression(tokens, ++index, 0);
                    if (index >= tokens.size() || !std::holds_alternative<TokenType>(tokens[index])
                        || std::get<TokenType>(tokens[index]) != TokenType::PARANTHESES_CLOSE)
                    {
                        throw std::runtime_error("Missing closing paranthesis");
                    }
                    // since we are at a ')' right now
                    index++;
                    break;
                case TokenType::PARANTHESES_CLOSE:
                    if (data->GetValue() && !node->GetValue())
                    {
                        return data;
                    }
                    return node;
                case TokenType::SINE:
                    node->SetLeft(std::make_shared<TreeNode>(nullptr, nullptr, node, 
                            std::make_shared<Sine>(
                                std::vector<std::shared_ptr<Statement>>{std::make_shared<StatementNumber>(0.0)}
                            )));
                    node->SetValue(std::make_shared<StatementFunction>());
                    node->SetRight(ReadExpression(tokens, ++index, 0));
                    break;
                case TokenType::COSINE:
                    node->SetLeft(std::make_shared<TreeNode>(nullptr, nullptr, node,
                        std::make_shared<Cosine>(
                            std::vector<std::shared_ptr<Statement>>{std::make_shared<StatementNumber>(0.0)}
                        )));
                    node->SetValue(std::make_shared<StatementFunction>());
                    node->SetRight(ReadExpression(tokens, ++index, 0));
                    break;
                case TokenType::TANGENT:
                    node->SetLeft(std::make_shared<TreeNode>(nullptr, nullptr, node,
                        std::make_shared<Tangent>(
                            std::vector<std::shared_ptr<Statement>>{std::make_shared<StatementNumber>(0.0)}
                        )));
                    node->SetValue(std::make_shared<StatementFunction>());
                    node->SetRight(ReadExpression(tokens, ++index, 0));
                    break;
                case TokenType::SECANT:
                    node->SetLeft(std::make_shared<TreeNode>(nullptr, nullptr, node,
                        std::make_shared<Secant>(
                            std::vector<std::shared_ptr<Statement>>{std::make_shared<StatementNumber>(0.0)}
                        )));
                    node->SetValue(std::make_shared<StatementFunction>());
                    node->SetRight(ReadExpression(tokens, ++index, 0));
                    break;
                case TokenType::COSECANT:
                    node->SetLeft(std::make_shared<TreeNode>(nullptr, nullptr, node,
                        std::make_shared<Cosecant>(
                            std::vector<std::shared_ptr<Statement>>{std::make_shared<StatementNumber>(0.0)}
                        )));
                    node->SetValue(std::make_shared<StatementFunction>());
                    node->SetRight(ReadExpression(tokens, ++index, 0));
                    break;
                case TokenType::COTANGENT:
                    node->SetLeft(std::make_shared<TreeNode>(nullptr, nullptr, node,
                        std::make_shared<Cotangent>(
                            std::vector<std::shared_ptr<Statement>>{std::make_shared<StatementNumber>(0.0)}
                        )));
                    node->SetValue(std::make_shared<StatementFunction>());
                    node->SetRight(ReadExpression(tokens, ++index, 0));
                    break;
                case TokenType::ASINE:
                    node->SetLeft(std::make_shared<TreeNode>(nullptr, nullptr, node,
                        std::make_shared<Arcsine>(
                            std::vector<std::shared_ptr<Statement>>{std::make_shared<StatementNumber>(0.0)}
                        )));
                    node->SetValue(std::make_shared<StatementFunction>());
                    node->SetRight(ReadExpression(tokens, ++index, 0));
                    break;
                case TokenType::ACOSINE:
                    node->SetLeft(std::make_shared<TreeNode>(nullptr, nullptr, node,
                        std::make_shared<Arccosine>(
                            std::vector<std::shared_ptr<Statement>>{std::make_shared<StatementNumber>(0.0)}
                        )));
                    node->SetValue(std::make_shared<StatementFunction>());
                    node->SetRight(ReadExpression(tokens, ++index, 0));
                    break;
                case TokenType::ATANGENT:
                    node->SetLeft(std::make_shared<TreeNode>(nullptr, nullptr, node,
                        std::make_shared<Arctangent>(
                            std::vector<std::shared_ptr<Statement>>{std::make_shared<StatementNumber>(0.0)}
                        )));
                    node->SetValue(std::make_shared<StatementFunction>());
                    node->SetRight(ReadExpression(tokens, ++index, 0));
                    break;
                case TokenType::ASECANT:
                    node->SetLeft(std::make_shared<TreeNode>(nullptr, nullptr, node,
                        std::make_shared<Arcsecant>(
                            std::vector<std::shared_ptr<Statement>>{std::make_shared<StatementNumber>(0.0)}
                        )));
                    node->SetValue(std::make_shared<StatementFunction>());
                    node->SetRight(ReadExpression(tokens, ++index, 0));
                    break;
                case TokenType::ACOSECANT:
                    node->SetLeft(std::make_shared<TreeNode>(nullptr, nullptr, node,
                        std::make_shared<Arccosecant>(
                            std::vector<std::shared_ptr<Statement>>{std::make_shared<StatementNumber>(0.0)}
                        )));
                    node->SetValue(std::make_shared<StatementFunction>());
                    node->SetRight(ReadExpression(tokens, ++index, 0));
                    break;
                case TokenType::ACOTANGENT:
                    node->SetLeft(std::make_shared<TreeNode>(nullptr, nullptr, node,
                        std::make_shared<Arccotangent>(
                            std::vector<std::shared_ptr<Statement>>{std::make_shared<StatementNumber>(0.0)}
                        )));
                    node->SetValue(std::make_shared<StatementFunction>());
                    node->SetRight(ReadExpression(tokens, ++index, 0));
                    break;
                case TokenType::PI:
                    // std::acos(-1.0f) = pi since cos(pi) = -1.0
                    node->SetValue(std::make_shared<StatementNumber>(std::acos(-1.0f)));
                    index++;
                    break;
                case TokenType::EXPONENTIAL:
                    node->SetValue(std::make_shared<StatementNumber>(std::exp(1.0f)));
                    index++;
                    break;
                // does not matter since these are placeholder initializations;
                // only the instantiation of a 'Logarithm' matters
                case TokenType::LOGARITHM:
                case TokenType::NATURAL_LOGARITHM:
                    node->SetLeft(std::make_shared<TreeNode>(nullptr, nullptr, node,
                        std::make_shared<Logarithm>(
                            std::vector<std::shared_ptr<Statement>>
                            {
                                std::make_shared<StatementNumber>(std::exp(1.0f)), 
                                std::make_shared<StatementNumber>(std::exp(1.0f))
                            }
                        )));
                    node->SetValue(std::make_shared<StatementFunction>());
                    node->SetRight(ReadExpression(tokens, ++index, 0));
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

    if (data->GetValue() && !node->GetValue())
    {
        return data;
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