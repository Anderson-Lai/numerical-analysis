#include "parser/tree.hpp"

TreeNode::TreeNode(const std::shared_ptr<Statement>& left, const std::shared_ptr<Statement>& right, const std::shared_ptr<Statement>& parent) : m_left(left), m_right(right), m_parent(parent)
{

}

void TreeNode::SetLeft(const std::shared_ptr<Statement>& left)
{
    m_left = left;
}

void TreeNode::SetRight(const std::shared_ptr<Statement>& right)
{
    m_right = right;
}

void TreeNode::SetParent(const std::shared_ptr<Statement>& parent)
{
    m_parent = parent;
}

std::shared_ptr<Statement> TreeNode::GetLeft() const
{
    return m_left;
}

std::shared_ptr<Statement> TreeNode::GetRight() const
{
    return m_right;
}

std::shared_ptr<Statement> TreeNode::GetParent() const
{
    return m_parent;
}