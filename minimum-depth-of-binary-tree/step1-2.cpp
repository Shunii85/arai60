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
#include <climits>
class Solution {
 public:
  int minDepth(TreeNode* root) {
    if (!root) {
      return 0;
    }
    return MinDepthHelper(root);
  }

 private:
  int MinDepthHelper(TreeNode* node) {
    if (!node->left && !node->right) {
      return 1;
    }
    int left_min_depth = INT_MAX;
    int right_min_depth = INT_MAX;
    if (node->left) {
      left_min_depth = MinDepthHelper(node->left);
    }
    if (node->right) {
      right_min_depth = MinDepthHelper(node->right);
    }
    return 1 + std::min(left_min_depth, right_min_depth);
  }
};