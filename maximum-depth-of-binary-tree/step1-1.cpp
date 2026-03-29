#include <unordered_set>

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
  int maxDepth(TreeNode* root) {
    if (root == nullptr) {
      return 0;
    }
    std::unordered_set<TreeNode*> same_depth_nodes{root};
    int depth = 0;
    while (!same_depth_nodes.empty()) {
      std::unordered_set<TreeNode*> next_depth_nodes;
      ++depth;
      for (auto node : same_depth_nodes) {
        if (node->left) {
          next_depth_nodes.insert(node->left);
        }
        if (node->right) {
          next_depth_nodes.insert(node->right);
        }
      }
      same_depth_nodes = std::move(next_depth_nodes);
    }
    return depth;
  }
};
