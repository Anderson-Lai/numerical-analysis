# Numerical Analysis
A command line tool to numerically evaluate finite limits, derivatives at a point, finite definite integrals, finite sums, finite products, and functions at a point. It also contains a custom interpreter that tokenizes and parses inputted math expressions from `stdin`.

## Documentation
See [usage.md](./docs/usage.md) for the full documentation. Below are some examples.

[TO INSERT EXAMPLES]

To evaluate multiple expressions from a file, say from `expressions.txt`, redirect the file to be `stdin` by running `./release/numerical_analysis < expressions.txt`. Ensure that each expression in the file is separated by a line break and that each expression is at most one line (i.e., the expression itself can not have any line breaks).

## Building
Run `./scripts/debug.sh` for a debug build and `./scripts/release.sh` for a release build. Run `./debug/numerical_analysis < tests.txt` to run the test suite. Examine the output to see if the program is running as expected.

## Features
- [x] implement limits
- [ ] implement derivatives
- [ ] implement integrals
- [ ] implement sums
- [ ] implement products
- [ ] implement function evaluation at a point
- [ ] implement root finding of functions
- [ ] add support for decimals in inputted expressions
- [ ] implement the absolute value function (either as abs(x), |x|, or both)
- [ ] implement parantheses checks
  - [ ] all opened parantheses are closed
  - [ ] no extraneous parantheses
- [ ] implement check that only one variable is used in each function call provided by the api
- [ ] implement support `(sin(x))^(-1)`, `(sec(x))^(-1)`, etc. by implicitly converting them to `arcsin(x)`, `arcsec(x)`, etc. in the AST rather than literally evaluating them as `1/(sin(x))`, `1/(sec(x))`, etc.
- [ ] implement implicit multiplication

## Extending the Interpreter
When adding new *operators or symbols*, ensure to add it to these places:
- `token.hpp` in `TokenType` enum 
- `lexer.hpp` in `NON_LETTER_TO_TOKEN_TYPE` member variable
- `lexer.hpp` in `Lexer::PrintTokens()` for **debugging purposes**
- `lexer.cpp` in `Lexer::Tokenize()` member function

When adding new *keywords*, ensure to add the first character of the keyword to:
- `lexer.cpp` in `Lexer::Tokenize()` member function

and the entire keyword to:
- `token.hpp` in `TokenType` enum
- `lexer.hpp` in `Lexer::PrintTokens()` for **debugging purposes**
- `lexer.cpp` in `Lexer::DeterminePossibleKeyword()` member function
- `parser.cpp` in `Parser::ReadExpression()` member function
- `parser.cpp` in `Parser::IsFunctionIdentifier()` member function

Remember to implement `LogConcreteType()` if it is a child of the `Statement` class (which it normally should be) for **debugging purposes**.