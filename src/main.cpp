#include <iostream>
#include <iomanip> 

#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

int main(int argc, char* argv[])
{
    while (true)
    {
        std::cout << "Expression: ";
        try
        {
            Lexer lexer;
            Parser parser;

            lexer.ReadTokens();
            parser.Parse(lexer.GetTokens());

#ifdef DEBUG_BUILD
            std::cout << std::endl << "Tokens: " << std::endl;
            lexer.PrintTokens();

            std::cout << std::endl << "AST: " << std::endl;
            Parser::PrintAST(parser.GetRoot());
#endif
            std::cout << std::fixed << std::setprecision(9);

#ifndef DEBUG_EXPRESSIONS
            const StatementNumber result = parser.EvaluateAST();
            std::cout << "Result: " << result.GetValue() << std::endl;
#else
            double testInputs[] =
    #ifdef DEBUG_NEGATIVE_NUMBERS
            {3.1415, 2.71828, 1, -1, 0, 13, -6, 5};
    #else
            {3.1415, 2.71828, 1, 0.001, 13, 6, 5};
    #endif
            for (const double input : testInputs)
            {
                std::cout << std::endl;
                std::cout << "Input: " << input << std::endl;
                std::cout << "Result: " << parser.EvaluateAST(StatementNumber(input)).GetValue()
                          << std::endl;
            }
            
            std::cout << std::endl;
#endif
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        std::cout << std::endl;
    }

    return 0;
}