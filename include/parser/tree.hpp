#pragma once

#include "parser/statements/statement.hpp"

class TreeNode
{
private:
    std::shared_ptr<TreeNode> m_left;
    std::shared_ptr<TreeNode> m_right;
    std::shared_ptr<Statement> m_value;
public:
    TreeNode(const std::shared_ptr<TreeNode>& left, const std::shared_ptr<TreeNode>& right,
        const std::shared_ptr<Statement>& value);
    ~TreeNode() = default;
public:
    void SetLeft(const std::shared_ptr<TreeNode>& left);
    void SetRight(const std::shared_ptr<TreeNode>& right);
    void SetValue(const std::shared_ptr<Statement>& value);
    std::shared_ptr<TreeNode> GetLeft() const;
    std::shared_ptr<TreeNode> GetRight() const;
    std::shared_ptr<Statement> GetValue() const;
};