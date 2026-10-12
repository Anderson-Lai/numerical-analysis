#pragma once

#include <vector>
#include <memory>

#include "parser/statements/statement.hpp"

class TreeNode
{
private:
    std::shared_ptr<Statement> m_value;
    std::vector<std::shared_ptr<TreeNode>> m_children;
public:
    TreeNode(const std::shared_ptr<Statement>& value, 
        const std::vector<std::shared_ptr<TreeNode>>& children);
    TreeNode(const std::shared_ptr<Statement>& value);
    ~TreeNode() = default;
public:
    void AttachAtBottomLeft(const std::shared_ptr<TreeNode>& child);
public:
    void SetValue(const std::shared_ptr<Statement>& value);

    void AddChild(const std::shared_ptr<TreeNode>& child);
    void SetChild(const std::shared_ptr<TreeNode>& child, const size_t index);
    void SetChildren(const std::vector<std::shared_ptr<TreeNode>>& children);
    
    const std::shared_ptr<Statement>& GetValue() const;
    const std::vector<std::shared_ptr<TreeNode>>& GetChildren() const;
};