#include <iostream>
#include "lexer.hpp"
#include <optional>

Lexer::Lexer() : m_integrator(Integrator()), m_differentiator(Differentiator())
{

}

std::variant<TokenType, char> Lexer::ReadUsefulCharacter() const
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
            return std::vector<Token>(1, TokenType::ADDITION);
        case '-':
            return std::vector<Token>(1, TokenType::SUBTRACTION);
        case '/':
            return std::vector<Token>(1, TokenType::DIVISION);
        case '*':
            return std::vector<Token>(1, TokenType::MULTIPLICATION);
        case '^':
            return std::vector<Token>(1, TokenType::EXPONENTIATION);
        case '_':
            return std::vector<Token>(1, TokenType::SUBSCRIPT);
        case '(':
            return std::vector<Token>(1, TokenType::PARANTHESES_OPEN);
        case ')':
            return std::vector<Token>(1, TokenType::PARANTHESES_CLOSE);
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
            return std::vector<Token>(1, Number( std::stod(std::string(1, character)) ));
        case 's':
            token += static_cast<char>(character);

            // check if it is sin/sec, if not, treat it as a variable
            for (int i = 0; i < 2; i++)
            {
                const auto nextCharacter = ReadUsefulCharacter();
                if (std::holds_alternative<Token>(nextCharacter))
                {
                    return std::vector<Token>{token, std::get<Token>(nextCharacter)};
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
                const auto nextCharacter = ReadUsefulCharacter();
                if (std::holds_alternative<Token>(nextCharacter))
                {
                    return std::vector<Token>{token, std::get<Token>(nextCharacter)};
                }

                token += std::get<char>(nextCharacter);
            }

            if (token == "cos")
            {
                return std::vector<Token>(1, TokenType::COSINE);
            }
            else if (token == "csc")
            {
                return std::vector<Token>(1, TokenType::COSECANT);
            }
            else if (token == "cot")
            {
                return std::vector<Token>(1, TokenType::COTANGENT);
            }

            return std::vector<Token>(1, (Variable(token)));
        case 't':
            token += static_cast<char>(character);

            for (int i = 0; i < 2; i++)
            {
                const auto nextCharacter = ReadUsefulCharacter();
                if (std::holds_alternative<Token>(nextCharacter))
                {
                    return std::vector<Token>{token, std::get<Token>(nextCharacter)};
                }

                token += std::get<char>(nextCharacter);
            }

            if (token == "tan")
            {
                return std::vector<Token>(1, TokenType::TANGENT);
            }
            
            return std::vector<Token>(1, (Variable(token)));
        case 'a':
            token += static_cast<char>(character);

            // check if it really is an 'arc' function, if not, treat it as a variable
            for (int i = 0; i < 5; i++)
            {
                const auto nextCharacter = ReadUsefulCharacter();
                if (std::holds_alternative<Token>(nextCharacter))
                {
                    return std::vector<Token>{token, std::get<Token>(nextCharacter)};
                }

                token += std::get<char>(nextCharacter);
            }

            if (token == "arcsin")
            {
                return std::vector<Token>(1, TokenType::ASINE);
            }
            else if (token == "arccos")
            {
                return std::vector<Token>(1, TokenType::ACOSINE);
            }
            else if (token == "arctan")
            {
                return std::vector<Token>(1, TokenType::ATANGENT);
            }
            else if (token == "arccot")
            {
                return std::vector<Token>(1, TokenType::ACOTANGENT);
            }
            else if (token == "arcsec")
            {
                return std::vector<Token>(1, TokenType::ASECANT);
            }
            else if (token == "arccsc")
            {
                return std::vector<Token>(1, TokenType::ACOSECANT);
            }

            return std::vector<Token>(1, (Variable(token)));
        case ' ':
            return std::vector<Token>(1, TokenType::SPACE);
        case '\n':
            return std::vector<Token>(1, TokenType::LINE_BREAK);
        case 'l':
            token += static_cast<char>(character);

            {
                const auto nextCharacter = ReadUsefulCharacter();
                if (std::holds_alternative<Token>(nextCharacter))
                {
                    return std::vector<Token>{token, std::get<Token>(nextCharacter)};
                }

                token += std::get<char>(nextCharacter);
            }

            if (token == "ln")
            {
                return std::vector<Token>(1, TokenType::NATURAL_LOGARITHM);
            }

            {
                const auto nextCharacter = ReadUsefulCharacter();
                if (std::holds_alternative<Token>(nextCharacter))
                {
                    return std::vector<Token>{token, std::get<Token>(nextCharacter)};
                }

                token += std::get<char>(nextCharacter);
            }

            if (token == "log")
            {
                return std::vector<Token>(1, TokenType::LOGARITHM);
            }

            return std::vector<Token>(1, Variable(token));
        case 'e':
            return std::vector<Token>(1, TokenType::EXPONENTIAL);
        default:
            return std::vector<Token>(1, Variable(std::string(1, character)));
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

        if (stored == TokenType::LINE_BREAK)
        {
            return true;
        }
    }
    return false;
}