#include <iostream>
#include "lexer.hpp"
#include <optional>

Lexer::Lexer() : m_integrator(Integrator()), m_differentiator(Differentiator())
{

}

char Lexer::AssignToken(char character)
{
    std::string token;
    switch (character)
    {
        case '+':
            m_tokens.push_back(TokenType::ADDITION);
            return getchar();
        case '-':
            m_tokens.push_back(TokenType::SUBTRACTION);
            return getchar();
        case '/':
            m_tokens.push_back(TokenType::DIVISION);
            return getchar();
        case '*':
            m_tokens.push_back(TokenType::MULTIPLICATION);
            return getchar();
        case '^':
            m_tokens.push_back(TokenType::EXPONENTIATION);
            return getchar();
        case '_':
            m_tokens.push_back(TokenType::SUBSCRIPT);
            return getchar();
        case '(':
            m_tokens.push_back(TokenType::BRACKET_OPEN);
            return getchar();
        case ')':
            m_tokens.push_back(TokenType::BRACKET_CLOSE);
            return getchar();
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            do
            {
                token += static_cast<char>(character);
                character = getchar();
            } while (isdigit(character) || character == '.');
            m_tokens.emplace_back(Number(std::stod(token)));

            return character;
        case 's':
            token += static_cast<char>(character);
            for (int i = 0; i < 2; ++i)
            {
                token += static_cast<char>(getchar());
            }

            if (token == "sin")
            {
                m_tokens.push_back(TokenType::SINE);
            }
            else if (token == "sec")
            {
                m_tokens.push_back(TokenType::SECANT);
            }
            else
            {
                for (const auto& character : token)
                {
                    m_tokens.emplace_back(Variable(character));
                }
            }

            return getchar();
        case 'c':
            token += static_cast<char>(character);
            for (int i = 0; i < 2; ++i)
            {
                token += static_cast<char>(getchar());
            }

            if (token == "cos")
            {
                m_tokens.push_back(TokenType::COSINE);
            }
            else if (token == "csc")
            {
                m_tokens.push_back(TokenType::COSECANT);
            }
            else if (token == "cot")
            {
                m_tokens.push_back(TokenType::COTANGENT);
            }
            else
            {
                for (const auto& character : token)
                {
                    m_tokens.emplace_back(Variable(character));
                }
            }

            return getchar();
        case 't':
            token += static_cast<char>(character);
            for (int i = 0; i < 2; ++i)
            {
                token += static_cast<char>(getchar());
            }

            if (token == "tan")
            {
                m_tokens.push_back(TokenType::TANGENT);
            }
            else
            {
                for (const auto& character : token)
                {
                    m_tokens.emplace_back(Variable(character));
                }
            }

            return getchar();
        case 'a':
            token += static_cast<char>(character);
            for (int i = 0; i < 5; ++i)
            {
                token += static_cast<char>(getchar());
            }

            if (token == "arcsin")
            {
                m_tokens.push_back(TokenType::ASINE);
            }
            else if (token == "arccos")
            {
                m_tokens.push_back(TokenType::ACOSINE);
            }
            else if (token == "arctan")
            {
                m_tokens.push_back(TokenType::ATANGENT);
            }
            else if (token == "arccot")
            {
                m_tokens.push_back(TokenType::ACOTANGENT);
            }
            else if (token == "arcsec")
            {
                m_tokens.push_back(TokenType::ASECANT);
            }
            else if (token == "arccsc")
            {
                m_tokens.push_back(TokenType::ACOSECANT);
            }
            else
            {
                for (const auto& character : token)
                {
                    m_tokens.emplace_back(Variable(character));
                }
            }
        case ' ':
            while (true)
            {
                character = getchar();
                if (character != ' ')
                {
                    return character;
                }
            }
        case 'l':
            token += static_cast<char>(character);
            token += static_cast<char>(getchar());
            if (token == "ln")
            {
                m_tokens.push_back(TokenType::NATURAL_LOGARITHM);
                return getchar();
            }
            token += static_cast<char>(getchar());
            if (token == "log")
            {
                m_tokens.push_back(TokenType::LOGARITHM);
                return getchar();
            }
            for (const auto& character : token)
            {
                m_tokens.emplace_back(Variable(character));
            }
            return getchar();
        case 'e':
            m_tokens.push_back(TokenType::EXPONENTIAL);
            return getchar();
        default:
            m_tokens.emplace_back(Variable(character));
            return getchar();
    }
}

void Lexer::ReadTokens()
{
    int character = getchar();
    std::string token;

    while (character != '\n')
    {
        character = AssignToken(character);
    }
}

double Lexer::Differentiation()
{
    ReadTokens();
#ifdef DEBUG_BUILD
    PrintTokens();
#endif
    return this->m_differentiator.Differentiate();
}

double Lexer::Integration()
{
    ReadTokens();
#ifdef DEBUG_BUILD
    PrintTokens();
#endif
    return this->m_integrator.Integrate();
}

void Lexer::Cleanup()
{
    m_tokens.clear();
}