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

    PARANTHESES_OPEN,
    PARANTHESES_CLOSE,

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

    SQUARE_ROOT,
    CUBE_ROOT,

    LOGARITHM,
    NATURAL_LOGARITHM,

    EXPONENTIAL,
    PI,

    DIFFERENTIATION,
    INTEGRATION,
    DIFFERENTIAL,

    SPACE,
    LINE_BREAK
};

typedef std::variant<TokenType, Number, Variable> Token;
typedef std::variant<TokenType, char> CharacterOrWhitespace;