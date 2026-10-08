# Numerical Calculus
A command line tool to numerically approximate derivatives (at a point) and (finite) definite integrals.

> [!NOTE]
> - Only use single letter variable names.
> - Use `arcsin(x)` instead of `sin^(-1)(x)` and `(sin(x))^(-1)`, `arccsc(x)` instead of `csc^(-1)(x)` and `(csc(x))^(-1)`, etc. for the inverse trig functions.
> - Put parantheses around all function calls and subscripts (for logarithm bases). For example: `log_(32)(sin(x))`.
> - `log` defaults to base-10 without a subscript (base) and `ln` defaults to base-e.
> - Implicit multiplication is not yet supported. Thus, ensure to explicitly add multiplication signs (e.g., `42 * sin(5 / x)`).

> [!WARNING]
> Real numbers are represented using a `double`. Hence, results become increasingly more inaccurate for extremely large and small numbers.