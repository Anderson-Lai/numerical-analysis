#include <iostream>
#include <iomanip> 

#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

int main(int argc, char* argv[])
{
    while (true)
    {
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

#ifndef DEBUG_EXPRESSIONS
            std::cout << std::fixed << std::setprecision(9) 
                << "\nResult: " << parser.EvaluateAST().GetValue() 
            << std::endl;
#else
            double testInputs[] =
    #ifdef DEBUG_NEGATIVE_NUMBERS
             {3.1415, 2.71828, 1, -1, 0, 13, -6, 5};
    #else
            {3.1415, 2.71828, 1, 0, 13, 6, 5};
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
    }

    return 0;
}