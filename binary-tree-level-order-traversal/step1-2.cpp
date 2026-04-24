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
    if (!root) {
      return {};
    }
    std::vector<std::vector<int>> level_order_values;
    std::vector<TreeNode*> current_level_nodes{root};
    while (!current_level_nodes.empty()) {
      std::vector<int> values;
      std::vector<TreeNode*> next_level_nodes;
      for (auto node : current_level_nodes) {
        values.push_back(node->val);
        if (node->left) {
          next_level_nodes.push_back(node->left);
        }
        if (node->right) {
          next_level_nodes.push_back(node->right);
        }
      }
      current_level_nodes = std::move(next_level_nodes);
      level_order_values.push_back(std::move(values));
    }
    return level_order_values;
  }
};
