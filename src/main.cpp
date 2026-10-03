#include "lexer/lexer.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    std::string input;

    while (true)
    {
        Lexer lexer;

#ifdef DEBUG_BUILD
        lexer.Differentiation();
#endif

#ifndef DEBUG_BUILD
        std::cin >> input;
        switch (std::stoi(input)) 
        {
            case 1:
                lexer.Differentiation();
                break;
            case 2:
                lexer.Integration();
                break;
            default:
                std::cout << "Invalid input\n";
                break;
        }
        lexer.Cleanup();
#endif
    }

    return 0;
}