#pragma once

#include "statements/statement.hpp"

class TreeNode
{
private:
    std::shared_ptr<TreeNode> m_left;
    std::shared_ptr<TreeNode> m_right;
    std::shared_ptr<TreeNode> m_parent;
    std::shared_ptr<Statement> m_value;
public:
    TreeNode(const std::shared_ptr<TreeNode>& left, const std::shared_ptr<TreeNode>& right, const std::shared_ptr<TreeNode>& parent, const std::shared_ptr<Statement>& value);
    ~TreeNode() = default;
public:
    void SetLeft(const std::shared_ptr<TreeNode>& left);
    void SetRight(const std::shared_ptr<TreeNode>& right);
    void SetParent(const std::shared_ptr<TreeNode>& parent);
    void SetValue(const std::shared_ptr<Statement>& value);
    std::shared_ptr<TreeNode> GetLeft() const;
    std::shared_ptr<TreeNode> GetRight() const;
    std::shared_ptr<TreeNode> GetParent() const;
    std::shared_ptr<Statement> GetValue() const;
};