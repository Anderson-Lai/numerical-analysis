#include <iostream>
#include "lexer/lexer.hpp"
#include <array>
#include <ranges>

Lexer::Lexer() : m_integrator(Integrator()), m_differentiator(Differentiator())
{

}

std::variant<Token, char> Lexer::ReadConsecutiveCharacter() const
{
    const char character = getchar();

    if (std::ranges::find(NON_LETTER, character))
    {
        switch (character)
        {
            case '+':
                return TokenType::ADDITION;
            case '-':
                return TokenType::SUBTRACTION;
            case '/':
                return TokenType::DIVISION;
            case '*':
                return TokenType::MULTIPLICATION;
            case '^':
                return TokenType::EXPONENTIATION;
            case '_':
                return TokenType::SUBSCRIPT;
            case '(':
                return TokenType::PARANTHESES_OPEN;
            case ')':
                return TokenType::PARANTHESES_CLOSE;
            case ' ':
                return TokenType::SPACE;
            case '\n':
                return TokenType::LINE_BREAK;
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
                return Number(std::stod(std::string{character}));
        }
    }

    return character;
}

std::vector<Token> Lexer::DeterminePossibleToken(const std::string& token) const
{
    switch (token.size())
    {
        // e
        case 1:
            if (token == "e")
            {
                return std::vector<Token>{TokenType::EXPONENTIAL};
            }

            return std::vector<Token>{Variable(token)};
        // ln
        case 2:
            if (token == "ln")
            {
                return std::vector<Token>{TokenType::NATURAL_LOGARITHM};
            }

            return std::vector<Token>{Variable(token)};
        // trig / log / int(egral):
        case 3:
            if (token == "log")
            {
                return std::vector<Token>{TokenType::LOGARITHM};
            }
            else if (token == "int")
            {
                return std::vector<Token>{TokenType::INTEGRATION};
            }
            else if (token == "sin")
            {
                return std::vector<Token>{TokenType::SINE};
            }
            else if (token == "cos")
            {
                return std::vector<Token>{TokenType::COSINE};
            }
            else if (token == "tan")
            {
                return std::vector<Token>{TokenType::TANGENT};
            }
            else if (token == "csc")
            {
                return std::vector<Token>{TokenType::COSECANT};
            }
            else if (token == "sec")
            {
                return std::vector<Token>{TokenType::SECANT};
            }
            else if (token == "cot")
            {
                return std::vector<Token>{TokenType::COTANGENT};
            }

            return std::vector<Token>{Variable(token)};
        // removed here since can not parse through the '/' symbol
        // // derivative
        // case 4:
        //     if (std::string_view(token.c_str(), 3) == "d/d")
        //     {
        //         return std::vector<Token>{TokenType::DIFFERENTIATION, Variable(std::string{token.back()})};
        //     }

        //     return std::vector<Token>{Variable(token)};
        // inverse trig
        case 6:
            if (token == "arcsin")
            {
                return std::vector<Token>{TokenType::ASINE};
            }
            else if (token == "arccos")
            {
                return std::vector<Token>{TokenType::ACOSINE};
            }
            else if (token == "arctan")
            {
                return std::vector<Token>{TokenType::ATANGENT};
            }
            else if (token == "arccsc")
            {
                return std::vector<Token>{TokenType::ACOSECANT};
            }
            else if (token == "arcsec")
            {
                return std::vector<Token>{TokenType::ASECANT};
            }
            else if (token == "arccot")
            {
                return std::vector<Token>{TokenType::ACOTANGENT};
            }

            return std::vector<Token>{Variable(token)};
        default:
            return std::vector<Token>{Variable(token)};
    }
}

std::vector<Token> Lexer::Tokenize(const char character) const
{
    std::string token;
    std::vector<Token> result;

    switch (character)
    {
        case '+':
            return std::vector<Token>{TokenType::ADDITION};
        case '-':
            return std::vector<Token>{TokenType::SUBTRACTION};
        case '/':
            return std::vector<Token>{TokenType::DIVISION};
        case '*':
            return std::vector<Token>{TokenType::MULTIPLICATION};
        case '^':
            return std::vector<Token>{TokenType::EXPONENTIATION};
        case '_':
            return std::vector<Token>{TokenType::SUBSCRIPT};
        case '(':
            return std::vector<Token>{TokenType::PARANTHESES_OPEN};
        case ')':
            return std::vector<Token>{TokenType::PARANTHESES_CLOSE};
        case ' ':
            return std::vector<Token>{TokenType::SPACE};
        case '\n':
            return std::vector<Token>{TokenType::LINE_BREAK};
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
            return std::vector<Token>{Number(std::stod(std::string{character}))};
        case 'a':
        case 's':
        case 'c':
        case 't':
        case 'l':
        case 'e':
        case 'd':
        case 'i':
            token += static_cast<char>(character);

            while (true)
            {

                const std::vector<Token> possibleToken = DeterminePossibleToken(token);
                if (std::holds_alternative<TokenType>(possibleToken.front()))
                {
                    for (const auto& tok : possibleToken)
                    {
                        result.push_back(tok);
                    }
                    token.clear();
                }

                const std::variant<Token, char> nextCharacter = ReadConsecutiveCharacter();

                // if typeof(nextCharacter) == Token, then an important character (e.g., ')', a number, etc.)
                // was read and the keyword has ended
                if (std::holds_alternative<Token>(nextCharacter))
                {
                    // ex: 'cos(' : after 'cos' is turned into a token, 'token' is now "", 
                    // so there is no point in determining if it is a possible token
                    if (token == "")
                    {
                        result.push_back(std::get<Token>(nextCharacter));
                        return result;
                    }

                    // certainToken.front() could be a Variable/Number as well,
                    // not just a TokenType
                    const std::vector<Token> certainToken = DeterminePossibleToken(token);
                    for (const auto& tok : certainToken)
                    {
                        result.push_back(tok);
                    }

                    result.push_back(std::get<Token>(nextCharacter));
                    return result;
                }

                token += std::get<char>(nextCharacter);
            }

            return std::vector<Token>{Variable(token)};
        default:
            return std::vector<Token>{Variable(std::string{character})};
    }
}

void Lexer::ReadTokens()
{
    bool running = true;
    while (running)
    {
        const std::vector<Token> returnedToken = Tokenize(getchar());

        for (const Token& token : returnedToken)
        {
            if (std::holds_alternative<TokenType>(token))
            {
                const TokenType& stored = std::get<TokenType>(token);

                if (stored == TokenType::LINE_BREAK)
                {
                    running = false;
                    break;
                }
                else if (stored == TokenType::SPACE)
                {
                    continue;
                }
                else if (stored == TokenType::INVALID)
                {
                    std::cout << "Invalid token encountered. Exiting...\n";
                    std::exit(EXIT_FAILURE);
                }
            }

            m_tokens.push_back(std::move(token));
        }
    };
}

void Lexer::CleanTokens()
{
    m_cleanedTokens.reserve(m_tokens.size());
    Number runningNumber(0.0);
    
    for (size_t i = 0; i < m_tokens.size(); i++)
    {
        if (std::holds_alternative<Number>(m_tokens[i]))
        {
            runningNumber = runningNumber.Concatenate(std::get<Number>(m_tokens[i]));
            i++;
            while (i < m_tokens.size() && std::holds_alternative<Number>(m_tokens[i]))
            {
                runningNumber = runningNumber.Concatenate(std::get<Number>(m_tokens[i]));
                i++;
            }
            m_cleanedTokens.push_back(runningNumber);
            runningNumber = Number(0.0);

            if (i < m_tokens.size())
            {
                m_cleanedTokens.push_back(m_tokens[i]);
            }
        }
        else
        {
            m_cleanedTokens.push_back(m_tokens[i]);
        }
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
    m_cleanedTokens.clear();
}