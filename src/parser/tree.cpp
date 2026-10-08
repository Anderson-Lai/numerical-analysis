#include "parser/tree.hpp"

TreeNode::TreeNode(const std::shared_ptr<TreeNode> &left, const std::shared_ptr<TreeNode> &right,
    const std::shared_ptr<Statement> &value) 
    : m_left(left), m_right(right), m_value(value)
{

}

void TreeNode::SetLeft(const std::shared_ptr<TreeNode>& left)
{
    m_left = left;
}

void TreeNode::SetRight(const std::shared_ptr<TreeNode>& right)
{
    m_right = right;
}

void TreeNode::SetValue(const std::shared_ptr<Statement>& value)
{
    m_value = value;
}

std::shared_ptr<TreeNode> TreeNode::GetLeft() const
{
    return m_left;
}

std::shared_ptr<TreeNode> TreeNode::GetRight() const
{
    return m_right;
}

std::shared_ptr<Statement> TreeNode::GetValue() const
{
    return m_value;
}