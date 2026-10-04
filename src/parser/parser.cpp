#include "parser/parser.hpp"
#include "parser/tree.hpp"

void Parser::Parse(const std::vector<Token>& tokens)
{
    m_root = std::make_shared<TreeNode>(nullptr, nullptr, nullptr);
}