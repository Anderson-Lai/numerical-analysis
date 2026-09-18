#pragma once

#include <vector>
#include <variant>
#include "differentiator.hpp"
#include "integrator.hpp"
#include <iostream>
#include "types.hpp"
#include <utility>

enum class TokenType
{
    ADDITION,
    SUBTRACTION,
    DIVISION,
    MULTIPLICATION,

    SUBSCRIPT,
    EXPONENTIATION,

    NUMBER,

    PARANTHESES_OPEN,
    PARANTHESES_CLOSE,

    VARIABLE,

    SINE,
    COSINE,
    TANGENT,
    COTANGENT,
    SECANT,
    COSECANT,

    ASINE,
    ACOSINE,
    ATANGENT,
    ACOTANGENT,
    ASECANT,
    ACOSECANT,

    LOGARITHM,
    NATURAL_LOGARITHM,
    EXPONENTIAL,

    DIFFERENTIATION,
    INTEGRATION,
    DIFFERENTIAL,

    SPACE,
    LINE_BREAK,
    
    INVALID
};

typedef std::variant<TokenType, Number, Variable> Token;
typedef std::variant<TokenType, char> CharacterOrWhitespace;

class Lexer
{
private:
    std::vector<Token> m_tokens;
    Integrator m_integrator;
    Differentiator m_differentiator;
private:
    void ReadTokens();
    std::vector<Token> Tokenize(const char character) const;
private:
    // replaces getchar()
    std::variant<Token, char> ReadConsecutiveLetter() const;
    std::vector<Token> DeterminePossibleToken(const std::string& token) const;
public:
    Lexer();
    double Differentiation();
    double Integration();
    void Cleanup();

#ifdef DEBUG_BUILD
private:
    void PrintTokens()
    {
        for (const auto &token : m_tokens)
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
                case TokenType::NUMBER:
                    tokenTypeStr = "NUMBER";
                    break;
                case TokenType::PARANTHESES_OPEN:
                    tokenTypeStr = "PARANTHESES_OPEN";
                    break;
                case TokenType::PARANTHESES_CLOSE:
                    tokenTypeStr = "PARANTHESES_CLOSE";
                    break;
                case TokenType::VARIABLE:
                    tokenTypeStr = "VARIABLE";
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
                case TokenType::DIFFERENTIATION:
                    tokenTypeStr = "DIFFERENTIATION";
                    break;
                case TokenType::INTEGRATION:
                    tokenTypeStr = "INTEGRATION";
                    break;
                case TokenType::DIFFERENTIAL:
                    tokenTypeStr = "DIFFERENTIAL";
                    break;
                case TokenType::NATURAL_LOGARITHM:
                    tokenTypeStr = "NATURAL_LOGARITHM";
                    break;
                case TokenType::LOGARITHM:
                    tokenTypeStr = "LOGARITHM";
                    break;
                case TokenType::EXPONENTIAL:
                    tokenTypeStr = "EXPONENTIAL";
                    break;
                case TokenType::INVALID:
                    tokenTypeStr = "INVALID";
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