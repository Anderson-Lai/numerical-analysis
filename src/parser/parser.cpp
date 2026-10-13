#include <cmath>

#include "parser/operators/binary_operators.hpp"
#include "parser/statements/functions/function_argument.hpp"
#include "parser/statements/functions/logarithm.hpp"
#include "parser/statements/functions/sqrt_cbrt.hpp"
#include "parser/statements/functions/trigonometry.hpp"
#include "parser/statements/statement_number.hpp"
#include "parser/statements/statement_variable.hpp"
#include "parser/parser.hpp"
#include "parser/tree.hpp"

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

        result->AttachAtBottomLeft(m_root);
        m_root = result;
    }
}

StatementNumber Parser::EvaluateAST(const std::shared_ptr<TreeNode> currentNode, 
    const StatementNumber& value) const
{
    if (!currentNode)
    {
        throw std::invalid_argument("AST node is nullptr");
    }

    // needed for unitary operators (addition / subtraction (negation)) since their left child's value
    // (m_value) will be nullptr while the left child itself is NOT a nullptr; thus,
    // the BinaryOperator only 'has' one child, when it needs two children to properly evaluate the expression
    if (!currentNode->GetValue())
    {
        return StatementNumber(0.0);
    }

    // should be a 'variable' or 'number'
    if (currentNode->GetChildren().empty())
    {
        return currentNode->GetValue()->Evaluate(std::vector<StatementNumber>{value});
    }

    std::vector<StatementNumber> parameters;
    for (const auto& child : currentNode->GetChildren())
    {
        if (child)
        {
            parameters.push_back(EvaluateAST(child, value));
        }
    }

    return currentNode->GetValue()->Evaluate(parameters);
}

std::shared_ptr<TreeNode> Parser::GetRoot() const
{
    return m_root;
}

// will auto increment 'index' (i.e., there is no reason to call 'index++' after calling this function,
// say, in a loop)
std::shared_ptr<TreeNode> Parser::ReadExpression(const std::vector<Token>& tokens, 
    size_t& index, const int minBindingPower) const
{

    if (index >= tokens.size())
    {
        return nullptr;
    }

    Token currentToken = tokens[index];
    int currentBindingPower = GetOperatorBindingPower(currentToken);
    auto node = std::make_shared<TreeNode>(nullptr);

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
            switch (currentTokenType)
            {
                // --- BINARY OPERATORS ---
                case TokenType::ADDITION:
                {
                    // we can't just add 'node' as another child since it is a vector of children,
                    // not just a singular left/right child now. thus, if we had added 'node' as a child instead of
                    // replacing all the children with 'node', then there would be at least 2 arguments
                    // for the 'AdditionOperator' even before we called 'AddChild'
                    // for the right side of the expression.
                    node->SetChildren(std::vector<std::shared_ptr<TreeNode>>{
                        std::make_shared<TreeNode>(*node)});
                    node->SetValue(std::make_shared<AdditionOperator>());

                    auto child = ReadExpression(tokens, ++index, currentBindingPower);
                    node->AddChild(child);

                    break;
                }
                case TokenType::SUBTRACTION:
                {
                    node->SetChildren(std::vector<std::shared_ptr<TreeNode>>{
                        std::make_shared<TreeNode>(*node)});
                    node->SetValue(std::make_shared<SubtractionOperator>());

                    auto child = ReadExpression(tokens, ++index, currentBindingPower);
                    node->AddChild(child);

                    break;
                }
                case TokenType::MULTIPLICATION:
                {
                    node->SetChildren(std::vector<std::shared_ptr<TreeNode>>{
                        std::make_shared<TreeNode>(*node)});
                    node->SetValue(std::make_shared<MultiplicationOperator>());

                    auto child = ReadExpression(tokens, ++index, currentBindingPower);
                    node->AddChild(child);

                    break;
                }
                case TokenType::DIVISION:
                {
                    node->SetChildren(std::vector<std::shared_ptr<TreeNode>>{
                        std::make_shared<TreeNode>(*node)});
                    node->SetValue(std::make_shared<DivisionOperator>());

                    auto child = ReadExpression(tokens, ++index, currentBindingPower);
                    node->AddChild(child);

                    break;
                }
                case TokenType::EXPONENTIATION:
                {
                    node->SetChildren(std::vector<std::shared_ptr<TreeNode>>{
                        std::make_shared<TreeNode>(*node)});
                    node->SetValue(std::make_shared<ExponentiationOperator>());

                    // since exponentiation is right associative
                    auto child = ReadExpression(tokens, ++index, currentBindingPower - 1);

                    node->AddChild(child);
                    break;
                }
                case TokenType::SUBSCRIPT:
                    node = ReadExpression(tokens, ++index, 0);

                    if (!node->GetValue())
                    {
                        return nullptr;
                    }
                    return node;
                case TokenType::COMMA:
                    if (!node->GetValue())
                    {
                        return nullptr;
                    }
                    return node;

                // TO IMPLEMENT: 
                // a) need to change based on if previous token was a function identifier
                // b) potentially add parantheses checking
                case TokenType::PARANTHESES_OPEN:
                    // possible issues when adding implicit multiplication
                    // since 'node->m_value' is ignored here
                    if (index - 1 < tokens.size() && IsFunctionIdentifier(tokens[index - 1]))
                    {
                        // node = ReadFullExpression(tokens, index, 0, true);
                        node->SetValue(std::make_shared<FunctionArgument>());
                        do
                        {
                            auto child = ReadFullExpression(tokens, index, 0, true);
                            if (!child)
                            {
                                throw std::runtime_error("Invalid expression detected");
                            }
                            node->AddChild(child);
                        }
                        while (index < tokens.size() && std::holds_alternative<TokenType>(tokens[index]) 
                            && std::get<TokenType>(tokens[index]) == TokenType::COMMA);
                    }
                    else
                    {
                        node = ReadFullExpression(tokens, index, 0, false);
                    }

                    if (!node)
                    {
                        throw std::runtime_error("Invalid expression detected");
                    }

                    return node;
                case TokenType::PARANTHESES_CLOSE:
                    if (!node->GetValue())
                    {
                        return nullptr;
                    }
                    return node;
                // --- CONSTANTS ---
                case TokenType::PI:
                    // std::acos(-1.0f) = pi since cos(pi) = -1.0
                    node->SetValue(std::make_shared<StatementNumber>(std::acos(-1.0f)));
                    index++;
                    break;
                case TokenType::EXPONENTIAL:
                    node->SetValue(std::make_shared<StatementNumber>(std::exp(1.0f)));
                    index++;
                    break;
                // CONVENTION: subscripts (bases for logarithms) go before function arguments
                // --- TRIG FUNCTIONS ---
                case TokenType::SINE:
                {
                    node->SetValue(std::make_shared<Sine>());
                    auto arguments = GetArguments(tokens, ++index);

                    node->SetChildren(arguments->GetChildren());
                    break;
                }
                case TokenType::COSINE:
                {
                    node->SetValue(std::make_shared<Cosine>());
                    auto arguments = GetArguments(tokens, ++index);

                    node->SetChildren(arguments->GetChildren());
                    break;
                }
                case TokenType::TANGENT:
                {
                    node->SetValue(std::make_shared<Tangent>());
                    auto arguments = GetArguments(tokens, ++index);

                    node->SetChildren(arguments->GetChildren());
                    break;
                }
                case TokenType::SECANT:
                {
                    node->SetValue(std::make_shared<Secant>());
                    auto arguments = GetArguments(tokens, ++index);

                    node->SetChildren(arguments->GetChildren());
                    break;
                }
                case TokenType::COSECANT:
                {
                    node->SetValue(std::make_shared<Cosecant>());
                    auto arguments = GetArguments(tokens, ++index);

                    node->SetChildren(arguments->GetChildren());
                    break;
                }
                case TokenType::COTANGENT:
                {
                    node->SetValue(std::make_shared<Cotangent>());
                    auto arguments = GetArguments(tokens, ++index);

                    node->SetChildren(arguments->GetChildren());
                    break;
                }
                case TokenType::ASINE:
                {
                    node->SetValue(std::make_shared<Arcsine>());
                    auto arguments = GetArguments(tokens, ++index);

                    node->SetChildren(arguments->GetChildren());
                    break;
                }
                case TokenType::ACOSINE:
                {
                    node->SetValue(std::make_shared<Arccosine>());
                    auto arguments = GetArguments(tokens, ++index);

                    node->SetChildren(arguments->GetChildren());
                    break;
                }
                case TokenType::ATANGENT:
                {
                    node->SetValue(std::make_shared<Arctangent>());
                    auto arguments = GetArguments(tokens, ++index);

                    node->SetChildren(arguments->GetChildren());
                    break;
                }
                case TokenType::ASECANT:
                {
                    node->SetValue(std::make_shared<Arcsecant>());
                    auto arguments = GetArguments(tokens, ++index);

                    node->SetChildren(arguments->GetChildren());
                    break;
                }
                case TokenType::ACOSECANT:
                {
                    node->SetValue(std::make_shared<Arccosecant>());
                    auto arguments = GetArguments(tokens, ++index);

                    node->SetChildren(arguments->GetChildren());
                    break;
                }
                case TokenType::ACOTANGENT:
                {
                    node->SetValue(std::make_shared<Arccotangent>());
                    auto arguments = GetArguments(tokens, ++index);

                    node->SetChildren(arguments->GetChildren());
                    break;
                }

                // --- LOGARITHMS ---
                case TokenType::LOGARITHM:
                {
                    node->SetValue(std::make_shared<Logarithm>());

                    if (index + 1 < tokens.size() && std::holds_alternative<TokenType>(tokens[index + 1]) && std::get<TokenType>(tokens[index + 1]) == TokenType::SUBSCRIPT)
                    {
                        node->AddChild(ReadExpression(tokens, ++index, 0));

                        /*
                        since we just read a base that ended with a parantheses, we are currently
                        past the parantheses since there is an 'index++' when returning
                        from the parantheses parsing

                        technically, this 'index--' should trigger regardless of whether the base
                        ended with a parantheses or not, but if the base did not end with a parantheses,
                        the parser would have just treated the whole expression (including the supposed arguments)
                        as an expression for the base
                        */
                        if (std::holds_alternative<TokenType>(tokens[index - 1]) && std::get<TokenType>(tokens[index - 1]) == TokenType::PARANTHESES_CLOSE)
                        {
                            index--;
                        }
                    }
                    // 'log' should default to base 10 if no base is specified
                    else
                    {
                        node->AddChild(std::make_shared<TreeNode>(
                            std::make_shared<StatementNumber>(10.0f)));
                    }

                    // '++index' is needed in case no base is specified
                    node->AddChild(ReadExpression(tokens, ++index, 0));

                    auto arguments = GetArguments(tokens, index);
                    for (const auto& arg : arguments->GetChildren())
                    {
                        node->AddChild(arg);
                    }
                    break;
                }
                case TokenType::NATURAL_LOGARITHM:
                {
                    node->AddChild(std::make_shared<TreeNode>(
                        std::make_shared<StatementNumber>(std::exp(1.0f))));

                    node->SetValue(std::make_shared<Logarithm>());
                    auto arguments = GetArguments(tokens, ++index);

                    for (const auto& arg : arguments->GetChildren())
                    {
                        node->AddChild(arg);
                    }
                    break;
                }
                    
                // --- ROOTS ---
                case TokenType::SQUARE_ROOT:
                {
                    node->SetValue(std::make_shared<SquareRoot>());
                    auto arguments = GetArguments(tokens, ++index);

                    node->SetChildren(arguments->GetChildren());
                    break;
                }
                case TokenType::CUBE_ROOT:
                {
                    node->SetValue(std::make_shared<CubeRoot>());
                    auto arguments = GetArguments(tokens, ++index);

                    node->SetChildren(arguments->GetChildren());
                    break;
                }
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

std::shared_ptr<TreeNode> Parser::ReadFullExpression(const std::vector<Token>& tokens, size_t& index, 
    const int operatorBindingPower, const bool fromFunctionCall) const
{
    if (index >= tokens.size())
    {
        throw std::runtime_error("Invalid expression detected");
    }

    // check if the current token is an opening parenthesis
    bool ownsParanthesis = false;
    if (std::holds_alternative<TokenType>(tokens[index]) 
        && std::get<TokenType>(tokens[index]) == TokenType::PARANTHESES_OPEN)
    {
        ownsParanthesis = true;
        // we can skip the '(' token
        index++;
    }
    
    auto child = ReadExpression(tokens, index, operatorBindingPower);
    if (!child)
    {
        throw std::runtime_error("Invalid expression detected");
    }

    if (index >= tokens.size())
    {
        return child;
    }

    // return if:
    // we do not own the current (closing) paranthesis AND the current token is a closing paranthesis
    // OR current token is a comma (e.g., for function arguments)
    const bool isCurrentTokenClosingParanthesis = std::holds_alternative<TokenType>(tokens[index]) 
        && std::get<TokenType>(tokens[index]) == TokenType::PARANTHESES_CLOSE;
    const bool isCurrentTokenComma = std::holds_alternative<TokenType>(tokens[index]) 
        && std::get<TokenType>(tokens[index]) == TokenType::COMMA;

    if ((!ownsParanthesis && isCurrentTokenClosingParanthesis) || isCurrentTokenComma)
    {
        index++;
        return child;
    }

    // since we own the ')' token (if it is a ')' token)
    if (isCurrentTokenClosingParanthesis)
    {
        ownsParanthesis = false;
        index++;

        if (index >= tokens.size() || operatorBindingPower >= GetOperatorBindingPower(tokens[index]) 
            || fromFunctionCall)
        {
            return child;
        }
    }
    
    int currentBindingPower = GetOperatorBindingPower(tokens[index]);
    while (index < tokens.size() && operatorBindingPower < currentBindingPower)
    {
        auto result = ReadExpression(tokens, index, operatorBindingPower);
        result->AttachAtBottomLeft(child);
        child = result;

        if (index >= tokens.size() || 
            (std::holds_alternative<TokenType>(tokens[index]) 
            && std::get<TokenType>(tokens[index]) == TokenType::PARANTHESES_CLOSE))
        {
            return child;
        }

        if (index < tokens.size())
        {
            currentBindingPower = GetOperatorBindingPower(tokens[index]);
        }
    }

    return child;
}

std::shared_ptr<TreeNode> Parser::GetArguments(const std::vector<Token>& tokens, size_t& index) const
{
    auto arguments = ReadExpression(tokens, index, 0);
    if (!std::dynamic_pointer_cast<FunctionArgument>(arguments->GetValue()))
    {
        throw std::runtime_error("FunctionArgument expected for function call");
    }
    return arguments;
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

bool Parser::IsFunctionIdentifier(const Token& token) const
{
    if (!std::holds_alternative<TokenType>(token))
    {
        return false;
    }

    const TokenType& tokenType = std::get<TokenType>(token);
    return (tokenType == TokenType::SINE || tokenType == TokenType::COSINE || tokenType == TokenType::TANGENT
        || tokenType == TokenType::COTANGENT || tokenType == TokenType::SECANT || tokenType == TokenType::COSECANT
        || tokenType == TokenType::ASINE || tokenType == TokenType::ACOSINE || tokenType == TokenType::ATANGENT
        || tokenType == TokenType::ACOTANGENT || tokenType == TokenType::ASECANT || tokenType == TokenType::ACOSECANT
        || tokenType == TokenType::SQUARE_ROOT || tokenType == TokenType::CUBE_ROOT
        || tokenType == TokenType::LOGARITHM || tokenType == TokenType::NATURAL_LOGARITHM);
}