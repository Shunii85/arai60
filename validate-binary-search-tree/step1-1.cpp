// ACできていない
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

#include <limits>
class Solution {
 public:
  bool isValidBST(TreeNode* node) {
    if (!node) {
      return true;
    }
    int left_child_value = std::numeric_limits<int>::min();
    int right_child_value = std::numeric_limits<int>::max();
    if (node->left) {
      left_child_value = node->left->val;
    }
    if (node->right) {
      right_child_value = node->right->val;
    }
    if (!(left_child_value < node->val && node->val < right_child_value)) {
      return false;
    }
    return isValidBST(node->left) && isValidBST(node->right);
  }
};
