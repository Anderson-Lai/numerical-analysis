#include "parser/tree.hpp"

TreeNode::TreeNode(const std::shared_ptr<Statement>& value, const std::vector<std::shared_ptr<TreeNode>>& children) 
    : m_value(value), m_children(children)
{

}

TreeNode::TreeNode(const std::shared_ptr<Statement>& value) 
    : TreeNode(value, std::vector<std::shared_ptr<TreeNode>>{})
{

}

void TreeNode::AttachAtBottomLeft(const std::shared_ptr<TreeNode>& child)
{
    if (!m_value)
    {
        m_value = child->GetValue();
        m_children = child->GetChildren();
        return;
    }

    auto traverser = std::make_shared<TreeNode>(*this);
    auto head = traverser;
    while (!traverser->GetChildren().empty() && traverser->GetChildren().front()->GetValue())
    {
        traverser = traverser->GetChildren().front();
    }

    // if (traverser->GetChildren().empty())
    // {
    //     traverser->AddChild(child);
    // }
    // else
    // {
        traverser->SetChild(child, 0);
    // }

    this->SetValue(head->GetValue());
    this->SetChildren(head->GetChildren());
}

void TreeNode::SetValue(const std::shared_ptr<Statement>& value)
{
    m_value = value;
}

void TreeNode::AddChild(const std::shared_ptr<TreeNode>& child)
{
    m_children.push_back(child);
}

void TreeNode::SetChild(const std::shared_ptr<TreeNode>& child, const size_t index)
{
    if (index >= m_children.size())
    {
        throw std::out_of_range("Index is out of range for children vector");
    }
    m_children[index] = child;
}

void TreeNode::SetChildren(const std::vector<std::shared_ptr<TreeNode>>& children)
{
    m_children = children;
}

const std::shared_ptr<Statement>& TreeNode::GetValue() const
{
    return m_value;
}

const std::vector<std::shared_ptr<TreeNode>>& TreeNode::GetChildren() const
{
    return m_children;
}