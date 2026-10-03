#include "parser/operators/binary_operators.hpp"

StatementNumber Addition::Evaluate() const
{
    return m_leftOperand->Evaluate() + m_rightOperand->Evaluate();
}

StatementNumber Subtraction::Evaluate() const
{
    return m_leftOperand->Evaluate() - m_rightOperand->Evaluate();
}

StatementNumber Multiplication::Evaluate() const
{
    return m_leftOperand->Evaluate() * m_rightOperand->Evaluate();
}

StatementNumber Division::Evaluate() const
{
    return m_leftOperand->Evaluate() / m_rightOperand->Evaluate();
}

StatementNumber Exponentiation::Evaluate() const
{
    return m_leftOperand->Evaluate() ^ m_rightOperand->Evaluate();
}