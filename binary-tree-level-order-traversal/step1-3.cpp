struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

#include <vector>
class Solution {
 public:
  std::vector<std::vector<int>> levelOrder(TreeNode* root) {
    std::vector<std::vector<int>> level_grouped_values;
    GroupNodeValuesByLevel(root, 1, level_grouped_values);
    return level_grouped_values;
  }

 private:
  void GroupNodeValuesByLevel(
      TreeNode* node, int level,
      std::vector<std::vector<int>>& level_grouped_values) {
    if (!node) return;
    while (level_grouped_values.size() < level) {
      level_grouped_values.push_back({});
    }
    level_grouped_values[level - 1].push_back(node->val);
    GroupNodeValuesByLevel(node->left, level + 1, level_grouped_values);
    GroupNodeValuesByLevel(node->right, level + 1, level_grouped_values);
  }
};
