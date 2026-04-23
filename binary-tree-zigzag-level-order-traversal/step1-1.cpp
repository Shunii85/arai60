struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

#include <algorithm>
#include <vector>
class Solution {
 public:
  std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root) {
    if (!root) {
      return {};
    }
    std::vector<std::vector<int>> zigzag_level_order_values;
    std::vector<TreeNode*> current_level_nodes({root});
    bool from_right = false;
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
      if (from_right) {
        std::reverse(values.begin(), values.end());
      }
      zigzag_level_order_values.push_back(std::move(values));
      current_level_nodes = std::move(next_level_nodes);
      from_right = !from_right;
    }
    return zigzag_level_order_values;
  }
};
