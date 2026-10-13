# Numerical Analysis
A command line tool to numerically approximate (finite) limits, derivatives (at a point), (finite) definite integrals, and to evaluate functions at a point.

> [!NOTE]
> - Only use single letter variable names.
> - Use `arcsin(x)` instead of `sin^(-1)(x)` and `(sin(x))^(-1)`, `arccsc(x)` instead of `csc^(-1)(x)` and `(csc(x))^(-1)`, etc. for the inverse trig functions.
> - Put parantheses around all function calls and subscripts (for logarithm bases). For example: `log_(32)(sin(x))`.
> - `log` defaults to base-10 without a subscript (base) and `ln` is always base-e (do not include a subscript for `ln`).
> - Implicit multiplication is not yet supported. Thus, ensure to explicitly add multiplication signs (e.g., `42 * sin(5 / x)`).

> [!WARNING]
> Real numbers are represented using a `double`. Hence, results become increasingly more inaccurate for extremely large and small numbers.

## Building
Run `./scripts/debug.sh` for a debug build and `./scripts/release.sh` for a release build. Run `./debug/numerical_calculus < text.txt` to run the test suite. Examine the output to see if the program is running as expected.

## Extending the Interpreter
When adding ***new tokens***, ensure to add it to these places:
- `token.hpp` in `TokenType` enum 
- `lexer.hpp` in `Lexer::PrintTokens()` for **debugging purposes**
- `lexer.hpp` in `NON_LETTER` member variable
- `lexer.cpp` in `Lexer::Tokenize(const char character)` member function
- `lexer.cpp` in `Lexer::ReadConsecutiveCharacter()` member function

When adding ***new keywords***, ensure to add the first character of the keyword to:
- `lexer.cpp` in `Lexer::Tokenize(const char character)` member function

and the entire keyword to:

- `lexer.cpp` in `Lexer::DeterminePossibleToken(const std::string& token)` member function

Remember to implement `LogConcreteType()` if it is a child of the `Statement` class for **debugging purposes**.

## To Do
- implement parantheses checks (all opened parantheses are closed, no extraneous parantheses)