#include "lexer/lexer.hpp"

#include "parser/statements/statement_number.hpp"

#ifdef DEBUG_BUILD
#include <iostream>
#endif

void Lexer::ReadTokens()
{
    bool running = true;
    while (running)
    {
        const std::vector<Token> returnedToken = Tokenize(static_cast<char>(getchar()));

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
                else if (stored == TokenType::NUMBER)
                {
                    throw std::runtime_error("Lexer::ReadTokens() - unexpected TokenType::NUMBER");
                }
            }

            m_tokens.push_back(std::move(token));
        }
    };

    m_tokens = CleanTokens();
}

std::vector<Token> Lexer::GetTokens() const
{
    return m_tokens;
}

std::vector<Token> Lexer::CleanTokens()
{
    std::vector<Token> cleanedTokens;
    cleanedTokens.reserve(m_tokens.size());
    Number runningNumber(0.0);

    for (size_t i = 0; i < m_tokens.size(); i++)
    {
        const Token& currentToken = m_tokens[i];
        if (std::holds_alternative<Number>(currentToken) || (std::holds_alternative<TokenType>(currentToken) 
            && std::get<TokenType>(currentToken) == TokenType::DECIMAL_POINT))
        {
            bool inDecimalRegime = std::holds_alternative<TokenType>(currentToken) 
                && std::get<TokenType>(currentToken) == TokenType::DECIMAL_POINT;
            if (!inDecimalRegime)
            {
                runningNumber = std::get<Number>(currentToken);
            }
            else
            {
                runningNumber = Number(0.0);
            }

            i++;
            int decimalPlace = 1;
            while (i < m_tokens.size() && (std::holds_alternative<Number>(m_tokens[i]) 
                    || (std::holds_alternative<TokenType>(m_tokens[i]) 
                        && std::get<TokenType>(m_tokens[i]) == TokenType::DECIMAL_POINT)))
            {
                if (std::holds_alternative<TokenType>(m_tokens[i]) && std::get<TokenType>(m_tokens[i]) == TokenType::DECIMAL_POINT)
                {
                    if (inDecimalRegime)
                    {
                        throw std::runtime_error("Multiple decimal points in one number");
                    }
                    inDecimalRegime = true;
                    i++;
                    continue;
                }

                const Number& nextNumber = std::get<Number>(m_tokens[i]);
                if (inDecimalRegime)
                {
                    runningNumber = runningNumber.InsertDecimalPlace(nextNumber, decimalPlace);
                    decimalPlace++;
                }
                else
                {
                    runningNumber = runningNumber.Concatenate(nextNumber);
                }

                i++;
            }

            cleanedTokens.push_back(runningNumber);
            runningNumber = Number(0.0);
            if (i < m_tokens.size())
            {
                cleanedTokens.push_back(m_tokens[i]);
            }
        }
        else
        {
            cleanedTokens.emplace_back(std::move(currentToken));
        }
    }

    return cleanedTokens;
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
    case ',':
        return std::vector<Token>{TokenType::COMMA};
    case '(':
        return std::vector<Token>{TokenType::PARANTHESES_OPEN};
    case ')':
        return std::vector<Token>{TokenType::PARANTHESES_CLOSE};
    case '.':
        return std::vector<Token>{TokenType::DECIMAL_POINT};
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
    // inverse trig
    case 'a':
    // cosine, cosecant, cotangent, cbrt
    case 'c':
    // derivative
    case 'd':
    // e, eval
    case 'e':
    // integral
    case 'i':
    // log, ln, limit
    case 'l':
    // pi, product
    case 'p':
    // sine, secant, sqrt, sum
    case 's':
    // tangent
    case 't':
        token += static_cast<char>(character);

        while (true)
        {
            const std::variant<Token, char> nextCharacter = ReadConsecutiveCharacter();

            // if typeof(nextCharacter) == Token, then an important character (e.g., ')', a number, etc.)
            // was read and the (possible) keyword has ended
            if (std::holds_alternative<Token>(nextCharacter))
            {
                // certainToken.front() could be a 'Variable' as well,
                // not just a TokenType
                const Token certainToken = DeterminePossibleKeyword(token);
                result.push_back(certainToken);
                result.push_back(std::get<Token>(nextCharacter));

                return result;
            }

            token += std::get<char>(nextCharacter);
        }

        // should never be reached
        return std::vector<Token>{Variable(token)};
    default:
        return std::vector<Token>{Variable(std::string{character})};
    }
}

Token Lexer::DeterminePossibleKeyword(const std::string& token) const
{
    switch (token.size())
    {
    // e
    case 1:
        if (token == "e")
        {
            return TokenType::EXPONENTIAL;
        }

        return Variable(token);
    // ln / pi
    case 2:
        if (token == "ln")
        {
            return TokenType::NATURAL_LOGARITHM;
        }
        else if (token == "pi")
        {
            return TokenType::PI;
        }

        return Variable(token);
    // trig / log / sum
    case 3:
        if (token == "log")
        {
            return TokenType::LOGARITHM;
        }
        else if (token == "sum")
        {
            return TokenType::SUM;
        }
        else if (token == "sin")
        {
            return TokenType::SINE;
        }
        else if (token == "cos")
        {
            return TokenType::COSINE;
        }
        else if (token == "tan")
        {
            return TokenType::TANGENT;
        }
        else if (token == "csc")
        {
            return TokenType::COSECANT;
        }
        else if (token == "sec")
        {
            return TokenType::SECANT;
        }
        else if (token == "cot")
        {
            return TokenType::COTANGENT;
        }

        return Variable(token);
    // sqrt / cbrt, eval
    case 4:
        if (token == "sqrt")
        {
            return TokenType::SQUARE_ROOT;
        }
        else if (token == "cbrt")
        {
            return TokenType::CUBE_ROOT;
        }
        else if (token == "eval")
        {
            return TokenType::EVAL;
        }

        return Variable(token);
    // limit
    case 5:
        if (token == "limit")
        {
            return TokenType::LIMIT;
        }

        return Variable(token);
    // inverse trig
    case 6:
        if (token == "arcsin")
        {
            return TokenType::ASINE;
        }
        else if (token == "arccos")
        {
            return TokenType::ACOSINE;
        }
        else if (token == "arctan")
        {
            return TokenType::ATANGENT;
        }
        else if (token == "arccsc")
        {
            return TokenType::ACOSECANT;
        }
        else if (token == "arcsec")
        {
            return TokenType::ASECANT;
        }
        else if (token == "arccot")
        {
            return TokenType::ACOTANGENT;
        }

        return Variable(token);
    // product
    case 7:
        if (token == "product")
        {
            return TokenType::PRODUCT;
        }

        return Variable(token);
    // integral
    case 8:
        if (token == "integral")
        {
            return TokenType::INTEGRAL;
        }

        return Variable(token);
    // derivative
    case 10:
        if (token == "derivative")
        {
            return TokenType::DERIVATIVE;
        }

        return Variable(token);
    default:
        return Variable(token);
    }
}

std::variant<Token, char> Lexer::ReadConsecutiveCharacter() const
{
    const char character = static_cast<char>(getchar());

    if (NON_LETTER_TO_TOKEN_TYPE.find(character) != NON_LETTER_TO_TOKEN_TYPE.end())
    {
        if (NON_LETTER_TO_TOKEN_TYPE.at(character) == TokenType::NUMBER)
        {
            return Number(std::stod(std::string{character}));
        }

        return NON_LETTER_TO_TOKEN_TYPE.at(character);
    }

    return character;
}