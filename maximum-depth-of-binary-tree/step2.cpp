#include <algorithm>
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
    if (!root) {
      return 0;
    }
    return MaxReachableDepth(root);
  }

 private:
  // `node` should exits, mustn't nullptr
  int MaxReachableDepth(TreeNode* node) {
    if (!node->left && !node->right) {
      return 1;
    }
    int left_max_depth = 0;
    int right_max_depth = 0;
    if (node->left) {
      left_max_depth = MaxReachableDepth(node->left);
    }
    if (node->right) {
      right_max_depth = MaxReachableDepth(node->right);
    }
    return 1 + std::max(left_max_depth, right_max_depth);
  }
};
