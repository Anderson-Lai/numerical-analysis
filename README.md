# Numerical Calculus
A command line tool to numerically approximate derivatives (at a point) and (finite) definite integrals.

> [!NOTE]
> Only single letter variable names are currently supported.

> [!NOTE]
> Use `arcsin(x)` over `sin^(-1)(x)`, `arccos(x)` over `cos^(-1)(x)`, `arccsc(x)` over `csc^(-1)(x)`, etc.

> [!NOTE]
> Implicit multiplication is not yet supported. For example, use `42 * sin(x)` rather than `42sin(x)`.

> [!NOTE]
> It is best practice to surround **all** function calls (e.g., `sin(x)`, `cos(ln(13 * arcsin(x)))`) with parantheses to avoid the parser misinterpreting your expression.

> [!WARNING]
> Real numbers are represented using a `double`. Hence, results become increasingly more inaccurate for extremely large and small numbers.