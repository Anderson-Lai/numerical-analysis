#include <iostream>
#include "parser.hpp"


Parser::Parser() : m_integrator(Integrator()), m_differentiator(Differentiator())
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
    return this->m_differentiator.Differentiate();
}

double Parser::Integration()
{
    ReadTokens();
    return this->m_integrator.Integrate();
}

void Parser::Cleanup()
{
    m_tokens.clear();
}