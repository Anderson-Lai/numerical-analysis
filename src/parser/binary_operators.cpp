#include "parser/operators/binary_operators.hpp"

StatementNumber AdditionOperator::Evaluate() const
{
    return m_leftOperand->Evaluate() + m_rightOperand->Evaluate();
}

StatementNumber SubtractionOperator::Evaluate() const
{
    return m_leftOperand->Evaluate() - m_rightOperand->Evaluate();
}

StatementNumber MultiplicationOperator::Evaluate() const
{
    return m_leftOperand->Evaluate() * m_rightOperand->Evaluate();
}

StatementNumber DivisionOperator::Evaluate() const
{
    return m_leftOperand->Evaluate() / m_rightOperand->Evaluate();
}

StatementNumber ExponentiationOperator::Evaluate() const
{
    return m_leftOperand->Evaluate() ^ m_rightOperand->Evaluate();
}