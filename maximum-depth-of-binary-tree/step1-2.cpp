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
  int maxDepth(TreeNode* root) { return MaxDepthHelper(root, 1); }

 private:
  int MaxDepthHelper(TreeNode* node, int depth) {
    if (!node) {
      return depth - 1;
    }
    int left_max_depth = MaxDepthHelper(node->left, depth + 1);
    int right_max_depth = MaxDepthHelper(node->right, depth + 1);
    return std::max(left_max_depth, right_max_depth);
  }
};
