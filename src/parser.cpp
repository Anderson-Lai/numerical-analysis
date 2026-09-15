#include "parser.hpp"
#include <iostream>

Parser::Parser()
{

}

void Parser::ReadTokens()
{
    std::string token;
    int res;
    while ((res = getchar()) != '\n')
    {
        // space character
        if (res == 32) 
        {
            if (!token.empty())
            {
                m_tokens.push_back(token);
                token.clear();
            }
        }
        else
        {
            token += static_cast<char>(res);
        }
    }
    if (!token.empty())
    {
        m_tokens.push_back(token);
    }
}

void Parser::LogTokens()
{
    for (const auto& token : m_tokens)
    {
        std::cout << token << std::endl;
    }
}

double Parser::Differentiation()
{
    ReadTokens();
    LogTokens();
    return 0.0;
}

double Parser::Integration()
{
    ReadTokens();
    return 0.0;
}

void Parser::Cleanup()
{
    m_tokens.clear();
}