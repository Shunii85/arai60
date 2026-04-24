struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

#include <queue>
#include <vector>
class Solution {
 public:
  std::vector<std::vector<int>> levelOrder(TreeNode* root) {
    if (!root) {
      return {};
    }
    std::vector<std::vector<int>> level_grouped_values;
    std::queue<TreeNode*> nodes({root});
    while (!nodes.empty()) {
      std::vector<int> level_values;
      int levelSize = nodes.size();
      for (int i = 0; i < levelSize; ++i) {
        auto node = nodes.front();
        level_values.push_back(node->val);
        nodes.pop();
        if (node->left) {
          nodes.push(node->left);
        }
        if (node->right) {
          nodes.push(node->right);
        }
      }
      level_grouped_values.push_back(std::move(level_values));
    }
    return level_grouped_values;
  }
};
