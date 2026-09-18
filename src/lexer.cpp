#include <iostream>
#include "lexer.hpp"
#include <optional>

Lexer::Lexer() : m_integrator(Integrator()), m_differentiator(Differentiator())
{

}

CharacterOrWhitespace Lexer::ReadUsefulCharacter() const
{
    const CharacterOrWhitespace character = ReadCharacter();
    if (IsLinebreak(character))
    {
        return TokenType::LINE_BREAK;
    }
    else if (IsSpace(character))
    {
        return TokenType::SPACE;
    }

    if (std::holds_alternative<char>(character))
    {
        return std::get<char>(character);
    }

    throw std::runtime_error("Something other than a character, space, or linebreak was parsed. Exiting...");
};

std::vector<Token> Lexer::Tokenize(const char character) const
{
    std::string token;
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
        case 's':
            token += static_cast<char>(character);

            // check if it is sin/sec, if not, treat it as a variable
            for (int i = 0; i < 2; i++)
            {
                const CharacterOrWhitespace nextCharacter = ReadUsefulCharacter();
                if (std::holds_alternative<TokenType>(nextCharacter))
                {
                    return std::vector<Token>{Variable(token), std::get<TokenType>(nextCharacter)};
                }

                token += std::get<char>(nextCharacter);
            }

            if (token == "sin")
            {
                return std::vector<Token>{TokenType::SINE};
            }
            else if (token == "sec")
            {
                return std::vector<Token>{TokenType::SECANT};
            }

            return std::vector<Token>{Variable(token)};
        case 'c':
            token += static_cast<char>(character);

            for (int i = 0; i < 2; i++)
            {
                const CharacterOrWhitespace nextCharacter = ReadUsefulCharacter();
                if (std::holds_alternative<TokenType>(nextCharacter))
                {
                    return std::vector<Token>{Variable(token), std::get<TokenType>(nextCharacter)};
                }

                token += std::get<char>(nextCharacter);
            }

            if (token == "cos")
            {
                return std::vector<Token>{TokenType::COSINE};
            }
            else if (token == "csc")
            {
                return std::vector<Token>{TokenType::COSECANT};
            }
            else if (token == "cot")
            {
                return std::vector<Token>{TokenType::COTANGENT};
            }

            return std::vector<Token>{(Variable(token))};
        case 't':
            token += static_cast<char>(character);

            for (int i = 0; i < 2; i++)
            {
                const CharacterOrWhitespace nextCharacter = ReadUsefulCharacter();
                if (std::holds_alternative<TokenType>(nextCharacter))
                {
                    return std::vector<Token>{Variable(token), std::get<TokenType>(nextCharacter)};
                }

                token += std::get<char>(nextCharacter);
            }

            if (token == "tan")
            {
                return std::vector<Token>{TokenType::TANGENT};
            }
            
            return std::vector<Token>{(Variable(token))};
        case 'a':
            token += static_cast<char>(character);

            // check if it really is an 'arc' function, if not, treat it as a variable
            for (int i = 0; i < 5; i++)
            {
                const CharacterOrWhitespace nextCharacter = ReadUsefulCharacter();
                if (std::holds_alternative<TokenType>(nextCharacter))
                {
                    return std::vector<Token>{Variable(token), std::get<TokenType>(nextCharacter)};
                }

                token += std::get<char>(nextCharacter);
            }

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
            else if (token == "arccot")
            {
                return std::vector<Token>{TokenType::ACOTANGENT};
            }
            else if (token == "arcsec")
            {
                return std::vector<Token>{TokenType::ASECANT};
            }
            else if (token == "arccsc")
            {
                return std::vector<Token>{TokenType::ACOSECANT};
            }

            return std::vector<Token>{(Variable(token))};
        case ' ':
            return std::vector<Token>{TokenType::SPACE};
        case '\n':
            return std::vector<Token>{TokenType::LINE_BREAK};
        case 'l':
            token += static_cast<char>(character);

            {
                const CharacterOrWhitespace nextCharacter = ReadUsefulCharacter();
                if (std::holds_alternative<TokenType>(nextCharacter))
                {
                    return std::vector<Token>{Variable(token), std::get<TokenType>(nextCharacter)};
                }

                token += std::get<char>(nextCharacter);
            }

            if (token == "ln")
            {
                return std::vector<Token>{TokenType::NATURAL_LOGARITHM};
            }

            {
                const CharacterOrWhitespace nextCharacter = ReadUsefulCharacter();
                if (std::holds_alternative<TokenType>(nextCharacter))
                {
                    return std::vector<Token>{Variable(token), std::get<TokenType>(nextCharacter)};
                }

                token += std::get<char>(nextCharacter);
            }

            if (token == "log")
            {
                return std::vector<Token>{TokenType::LOGARITHM};
            }

            return std::vector<Token>{Variable(token)};
        case 'e':
            return std::vector<Token>{TokenType::EXPONENTIAL};
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

CharacterOrWhitespace Lexer::ReadCharacter() const
{
    char character = getchar();
    if (character == ' ')
    {
        return TokenType::SPACE;
    }
    else if (character == '\n')
    {
        return TokenType::LINE_BREAK;
    }

    return character;
}

bool Lexer::IsLinebreak(const CharacterOrWhitespace& character) const
{
    if (std::holds_alternative<TokenType>(character))
    {
        const TokenType& stored = std::get<TokenType>(character);

        if (stored == TokenType::LINE_BREAK)
        {
            return true;
        }
    }
    return false;
}

bool Lexer::IsSpace(const CharacterOrWhitespace& character) const
{
    if (std::holds_alternative<TokenType>(character))
    {
        const TokenType& stored = std::get<TokenType>(character);

        if (stored == TokenType::SPACE)
        {
            return true;
        }
    }
    return false;
}