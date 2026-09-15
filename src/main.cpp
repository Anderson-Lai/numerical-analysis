#include "parser.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    Parser parser;
    std::string input;
    
    while (true)
    {
        std::cin >> input;
        switch (std::stoi(input)) 
        {
            case 1:
                parser.Differentiation();
                break;
            case 2:
                parser.Integration();
                break;
            default:
                std::cout << "Invalid input\n";
                break;
        }
        parser.Cleanup();
    }

    return 0;
}