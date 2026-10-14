#pragma once

#include <vector>
#include <variant>
#include <unordered_map>

#include "lexer/types.hpp"
#include "lexer/token.hpp"

#ifdef DEBUG_BUILD
#include <iostream>
#endif

class Lexer
{
private:
    std::vector<Token> m_tokens;
private:
    inline static const std::unordered_map<char, TokenType> NON_LETTER_TO_TOKEN_TYPE =
    {
        {'+', TokenType::ADDITION},
        {'-', TokenType::SUBTRACTION},
        {'/', TokenType::DIVISION},
        {'*', TokenType::MULTIPLICATION},
        {'^', TokenType::EXPONENTIATION},

        {'_', TokenType::SUBSCRIPT},
        {',', TokenType::COMMA},

        {'1', TokenType::NUMBER},
        {'2', TokenType::NUMBER},
        {'3', TokenType::NUMBER},
        {'4', TokenType::NUMBER},
        {'5', TokenType::NUMBER},
        {'6', TokenType::NUMBER},
        {'7', TokenType::NUMBER},
        {'8', TokenType::NUMBER},
        {'9', TokenType::NUMBER},
        {'0', TokenType::NUMBER},

        {'(', TokenType::PARANTHESES_OPEN},
        {')', TokenType::PARANTHESES_CLOSE},

        {' ', TokenType::SPACE},
        {'\n', TokenType::LINE_BREAK}
    };
public:
    Lexer() = default;
    void ReadTokens();
    std::vector<Token> GetTokens() const;
private:
    std::vector<Token> CleanTokens();
private:
    std::vector<Token> Tokenize(const char character) const;
// helper functions
private:
    Token DeterminePossibleKeyword(const std::string& token) const;
    // replaces getchar()
    std::variant<Token, char> ReadConsecutiveCharacter() const;
#ifdef DEBUG_BUILD
public:
    void PrintTokens()
    {
        for (const auto& token : m_tokens)
        {
            if (std::holds_alternative<TokenType>(token))
            {
                std::string tokenTypeStr;
                switch (std::get<TokenType>(token))
                {
                case TokenType::ADDITION:
                    tokenTypeStr = "ADDITION";
                    break;
                case TokenType::SUBTRACTION:
                    tokenTypeStr = "SUBTRACTION";
                    break;
                case TokenType::DIVISION:
                    tokenTypeStr = "DIVISION";
                    break;
                case TokenType::MULTIPLICATION:
                    tokenTypeStr = "MULTIPLICATION";
                    break;
                case TokenType::EXPONENTIATION:
                    tokenTypeStr = "EXPONENTIATION";
                    break;

                case TokenType::SUBSCRIPT:
                    tokenTypeStr = "SUBSCRIPT";
                    break;
                case TokenType::COMMA:
                    tokenTypeStr = "COMMA";
                    break;

                case TokenType::PARANTHESES_OPEN:
                    tokenTypeStr = "PARANTHESES_OPEN";
                    break;
                case TokenType::PARANTHESES_CLOSE:
                    tokenTypeStr = "PARANTHESES_CLOSE";
                    break;

                case TokenType::EXPONENTIAL:
                    tokenTypeStr = "EXPONENTIAL";
                    break;
                case TokenType::PI:
                    tokenTypeStr = "PI";
                    break;

                case TokenType::SINE:
                    tokenTypeStr = "SINE";
                    break;
                case TokenType::COSINE:
                    tokenTypeStr = "COSINE";
                    break;
                case TokenType::TANGENT:
                    tokenTypeStr = "TANGENT";
                    break;
                case TokenType::COTANGENT:
                    tokenTypeStr = "COTANGENT";
                    break;
                case TokenType::SECANT:
                    tokenTypeStr = "SECANT";
                    break;
                case TokenType::COSECANT:
                    tokenTypeStr = "COSECANT";
                    break;
                case TokenType::ASINE:
                    tokenTypeStr = "ASINE";
                    break;
                case TokenType::ACOSINE:
                    tokenTypeStr = "ACOSINE";
                    break;
                case TokenType::ATANGENT:
                    tokenTypeStr = "ATANGENT";
                    break;
                case TokenType::ACOTANGENT:
                    tokenTypeStr = "ACOTANGENT";
                    break;
                case TokenType::ASECANT:
                    tokenTypeStr = "ASECANT";
                    break;
                case TokenType::ACOSECANT:
                    tokenTypeStr = "ACOSECANT";
                    break;

                case TokenType::SQUARE_ROOT:
                    tokenTypeStr = "SQUARE_ROOT";
                    break;
                case TokenType::CUBE_ROOT:
                    tokenTypeStr = "CUBE_ROOT";
                    break;

                case TokenType::LOGARITHM:
                    tokenTypeStr = "LOGARITHM";
                    break;
                case TokenType::NATURAL_LOGARITHM:
                    tokenTypeStr = "NATURAL_LOGARITHM";
                    break;

                case TokenType::DERIVATIVE:
                    tokenTypeStr = "DERIVATIVE";
                    break;
                case TokenType::INTEGRAL:
                    tokenTypeStr = "INTEGRAL";
                    break;
                case TokenType::LIMIT:
                    tokenTypeStr = "LIMIT";
                    break;
                case TokenType::ROOT:
                    tokenTypeStr = "ROOT";
                    break;
                case TokenType::SERIES:
                    tokenTypeStr = "SERIES";
                    break;

                case TokenType::SPACE:
                    tokenTypeStr = "SPACE";
                    break;
                case TokenType::LINE_BREAK:
                    tokenTypeStr = "LINE_BREAK";
                    break;
                
                default:
                    tokenTypeStr = "UNKNOWN";
                }
                std::cout << "TokenType: " << tokenTypeStr << "\n";
            }
            else if (std::holds_alternative<Number>(token))
            {
                std::cout << "Number: " << std::get<Number>(token).GetValue() << "\n";
            }
            else if (std::holds_alternative<Variable>(token))
            {
                std::cout << "Variable: " << std::get<Variable>(token).GetName() << "\n";
            }
        }
    }
#endif
};