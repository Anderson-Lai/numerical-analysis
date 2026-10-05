#pragma once

#include <variant>
#include "lexer/types.hpp"

enum class TokenType
{
    ADDITION,
    SUBTRACTION,
    DIVISION,
    MULTIPLICATION,

    SUBSCRIPT,
    EXPONENTIATION,

    NUMBER,

    PARANTHESES_OPEN,
    PARANTHESES_CLOSE,

    VARIABLE,

    SINE,
    COSINE,
    TANGENT,
    COTANGENT,
    SECANT,
    COSECANT,

    ASINE,
    ACOSINE,
    ATANGENT,
    ACOTANGENT,
    ASECANT,
    ACOSECANT,

    LOGARITHM,
    NATURAL_LOGARITHM,
    EXPONENTIAL,

    PI,

    DIFFERENTIATION,
    INTEGRATION,
    DIFFERENTIAL,

    SPACE,
    LINE_BREAK,

    INVALID
};

typedef std::variant<TokenType, Number, Variable> Token;
typedef std::variant<TokenType, char> CharacterOrWhitespace;