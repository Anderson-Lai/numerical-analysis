#pragma once

#include "statements/statement.hpp"

class TreeNode
{
private:
    std::shared_ptr<Statement> m_left;
    std::shared_ptr<Statement> m_right;
    std::shared_ptr<Statement> m_parent;
public:
    TreeNode(const std::shared_ptr<Statement>& left, const std::shared_ptr<Statement>& right, const std::shared_ptr<Statement>& parent);
    ~TreeNode() = default;
public:
    void SetLeft(const std::shared_ptr<Statement>& left);
    void SetRight(const std::shared_ptr<Statement>& right);
    void SetParent(const std::shared_ptr<Statement>& parent);
    std::shared_ptr<Statement> GetLeft() const;
    std::shared_ptr<Statement> GetRight() const;
    std::shared_ptr<Statement> GetParent() const;
};