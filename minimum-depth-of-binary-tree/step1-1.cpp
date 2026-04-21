#include <vector>
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};
class Solution {
 public:
  int minDepth(TreeNode* root) {
    if (!root) {
      return 0;
    }
    std::vector<TreeNode*> same_depth_nodes{root};
    int depth = 0;
    while (!same_depth_nodes.empty()) {
      ++depth;
      std::vector<TreeNode*> next_depth_nodes;
      for (const auto& node : same_depth_nodes) {
        if (IsLeafNode(node)) {
          return depth;
        }
        if (node->left) {
          next_depth_nodes.push_back(node->left);
        }
        if (node->right) {
          next_depth_nodes.push_back(node->right);
        }
      }
      same_depth_nodes = std::move(next_depth_nodes);
    }
    return -1;
  }

 private:
  bool IsLeafNode(TreeNode* node) { return !node->left && !node->right; }
};