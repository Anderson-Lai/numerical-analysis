#include "parser/parser.hpp"
#include "parser/tree.hpp"
#include "parser/statements/statement_variable.hpp"
#include "parser/statements/statement_number.hpp"
#include "parser/operators/binary_operators.hpp"
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

    // no need for 'index++' since it would have happend in 'ReadExpression' before the function returned
    while (index < tokens.size())
    {
        auto result = ReadExpression(tokens, index, 0);
        if (!result)
        {
            throw std::runtime_error("Invalid expression detected");
        }

        // get to the leftmost node of the new subtree and attach the old root as its left child
        // to avoid accidentally erasing any tokens/information
        auto temp = result;
        while (temp->GetLeft() && temp->GetLeft()->GetValue())
        {
            temp = temp->GetLeft();
        }
        temp->SetLeft(std::make_shared<TreeNode>(*m_root));

        m_root = result;
        index++;
    }
}

std::shared_ptr<TreeNode> Parser::ReadExpression(const std::vector<Token>& tokens, 
    size_t& index, const int minBindingPower)
{

    if (index >= tokens.size())
    {
        return nullptr;
    }

    Token currentToken = tokens[index];
    int currentBindingPower = GetOperatorBindingPower(currentToken);
    auto node = std::make_shared<TreeNode>(nullptr, nullptr, nullptr, nullptr);

    while (index < tokens.size() && (minBindingPower < currentBindingPower || currentBindingPower == -1))
    {
        // implement implicit multiplication later
        if (std::holds_alternative<Number>(currentToken))
        {
            node->SetValue(std::make_shared<StatementNumber>(std::get<Number>(currentToken)));
            index++;
        }
        else if (std::holds_alternative<Variable>(currentToken))
        {
            node->SetValue(std::make_shared<StatementVariable>(std::get<Variable>(currentToken)));
            index++;
        }

        // recursive part of pratt parsing
        else if (std::holds_alternative<TokenType>(currentToken))
        {
            const TokenType& currentTokenType = std::get<TokenType>(currentToken);
            // since exponentiation is right associative
            int associativity = (currentTokenType == TokenType::EXPONENTIATION) ? -1 : 0;

            switch (currentTokenType)
            {
                case TokenType::ADDITION:
                    node->SetLeft(std::make_shared<TreeNode>(*node));
                    node->SetValue(std::make_shared<AdditionOperator>());
                    node->SetRight(ReadExpression(tokens, ++index, currentBindingPower));
                    break;
                case TokenType::SUBTRACTION:
                    node->SetLeft(std::make_shared<TreeNode>(*node));
                    node->SetValue(std::make_shared<SubtractionOperator>());
                    node->SetRight(ReadExpression(tokens, ++index, currentBindingPower));
                    break;
                case TokenType::MULTIPLICATION:
                    node->SetLeft(std::make_shared<TreeNode>(*node));
                    node->SetValue(std::make_shared<MultiplicationOperator>());
                    node->SetRight(ReadExpression(tokens, ++index, currentBindingPower));
                    break;
                case TokenType::DIVISION:
                    node->SetLeft(std::make_shared<TreeNode>(*node));
                    node->SetValue(std::make_shared<DivisionOperator>());
                    node->SetRight(ReadExpression(tokens, ++index, currentBindingPower));
                    break;
                // to implement later; subscript is a UNARY operator
                case TokenType::SUBSCRIPT:
                    node = ReadExpression(tokens, ++index, 0);

                    if (!node->GetValue())
                    {
                        return nullptr;
                    }
                    return node;
                case TokenType::EXPONENTIATION:
                    node->SetLeft(std::make_shared<TreeNode>(*node));
                    node->SetValue(std::make_shared<ExponentiationOperator>());
                    node->SetRight(ReadExpression(tokens, ++index, currentBindingPower + associativity));
                    break;
                case TokenType::PARANTHESES_OPEN:
                    // possible issues when adding implicit multiplication
                    // since 'node->m_value' is ignored here
                    node = ReadExpression(tokens, ++index, 0);
                    if (index >= tokens.size() || !std::holds_alternative<TokenType>(tokens[index])
                        || std::get<TokenType>(tokens[index]) != TokenType::PARANTHESES_CLOSE)
                    {
                        throw std::runtime_error("Missing closing paranthesis");
                    }
                    // since we are at a ')' right now
                    index++;

                    // since an "expression" has ended
                    if (!node->GetValue())
                    {
                        return nullptr;
                    }
                    return node;
                case TokenType::PARANTHESES_CLOSE:
                    if (!node->GetValue())
                    {
                        return nullptr;
                    }
                    return node;
                
                // CONVENTION: arguments go on right, subscripts go on left
                // m_left is usually nullptr except for logarithms with a base
                case TokenType::SINE:
                    node->SetValue(std::make_shared<Sine>());
                    node->SetRight(ReadExpression(tokens, ++index, 0));
                    break;
                case TokenType::COSINE:
                    node->SetValue(std::make_shared<Cosine>());
                    node->SetRight(ReadExpression(tokens, ++index, 0));
                    break;
                case TokenType::TANGENT:
                    node->SetValue(std::make_shared<Tangent>());
                    node->SetRight(ReadExpression(tokens, ++index, 0));
                    break;
                case TokenType::SECANT:
                    node->SetValue(std::make_shared<Secant>());
                    node->SetRight(ReadExpression(tokens, ++index, 0));
                    break;
                case TokenType::COSECANT:
                    node->SetValue(std::make_shared<Cosecant>());
                    node->SetRight(ReadExpression(tokens, ++index, 0));
                    break;
                case TokenType::COTANGENT:
                    node->SetValue(std::make_shared<Cotangent>());
                    node->SetRight(ReadExpression(tokens, ++index, 0));
                    break;
                case TokenType::ASINE:
                    node->SetValue(std::make_shared<Arcsine>());
                    node->SetRight(ReadExpression(tokens, ++index, 0));
                    break;
                case TokenType::ACOSINE:
                    node->SetValue(std::make_shared<Arccosine>());
                    node->SetRight(ReadExpression(tokens, ++index, 0));
                    break;
                case TokenType::ATANGENT:
                    node->SetValue(std::make_shared<Arctangent>());
                    node->SetRight(ReadExpression(tokens, ++index, 0));
                    break;
                case TokenType::ASECANT:
                    node->SetValue(std::make_shared<Arcsecant>());
                    node->SetRight(ReadExpression(tokens, ++index, 0));
                    break;
                case TokenType::ACOSECANT:
                    node->SetValue(std::make_shared<Arccosecant>());
                    node->SetRight(ReadExpression(tokens, ++index, 0));
                    break;
                case TokenType::ACOTANGENT:
                    node->SetValue(std::make_shared<Arccotangent>());
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
                case TokenType::LOGARITHM:
                    node->SetValue(std::make_shared<Logarithm>());

                    if (index + 1 < tokens.size() && std::holds_alternative<TokenType>(tokens[index + 1]) 
                        && std::get<TokenType>(tokens[index + 1]) == TokenType::SUBSCRIPT)
                    {
                        node->SetLeft(ReadExpression(tokens, ++index, 0));

                        /*  
                        since we just read a base that ended with a parantheses, we are currently
                        past the parantheses since there is an 'index++' when returning
                        from the parantheses parsing

                        technically, this 'index--' should trigger regardless of whether the base
                        ended with a parantheses or not, but if the base did not end with a parantheses,
                        the parser would have just treated the whole expression (including the supposed arguments)
                        as an expression for the base
                        */
                        if (std::holds_alternative<TokenType>(tokens[index - 1])
                            && std::get<TokenType>(tokens[index - 1]) == TokenType::PARANTHESES_CLOSE)
                        {
                            index--;
                        }
                    }
                    // 'log' should default to base 10 if no base is specified
                    else
                    {
                        node->SetLeft(std::make_shared<TreeNode>(nullptr, nullptr, nullptr,
                            std::make_shared<StatementNumber>(10.0)
                        ));
                    }

                    // '++index' is needed in case no base is specified
                    node->SetRight(ReadExpression(tokens, ++index, 0));
                    break;
                case TokenType::NATURAL_LOGARITHM:
                    node->SetValue(std::make_shared<Logarithm>());
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

        if (index < tokens.size())
        {
            currentToken = tokens[index];
            currentBindingPower = GetOperatorBindingPower(currentToken);
        }
    }

    if (!node->GetValue())
    {
        return nullptr;
    }
    return node;
}

StatementNumber Parser::EvaluateAST(const std::shared_ptr<TreeNode> currentNode,
    const StatementNumber& value) const
{
    // needed for unitary operators (addition / subtraction (negation)) since their left child will be nullptr
    // and so the BinaryOperator only 'has' one child, when it needs two to properly evaluate
    if (!currentNode || !currentNode->GetValue())
    {
        return StatementNumber(0.0);
    }

    if (!currentNode->GetLeft() && !currentNode->GetRight())
    {
        return currentNode->GetValue()->Evaluate(std::vector<StatementNumber>{value});
    }

    std::vector<StatementNumber> parameters;
    if (currentNode->GetLeft())
    {
        parameters.push_back(EvaluateAST(currentNode->GetLeft(), value));
    }
    if (currentNode->GetRight())
    {
        parameters.push_back(EvaluateAST(currentNode->GetRight(), value));
    }

    return currentNode->GetValue()->Evaluate(parameters);
}

std::shared_ptr<TreeNode> Parser::GetRoot() const
{
    return m_root;
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