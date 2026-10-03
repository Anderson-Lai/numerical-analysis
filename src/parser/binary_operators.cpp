#include "parser/operators/binary_operators.hpp"

// only do addition for now
StatementNumber Addition::Evaluate() const
{
    return m_leftOperand->Evaluate() + m_rightOperand->Evaluate();
}