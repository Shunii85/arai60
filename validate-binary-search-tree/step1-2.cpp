// オーバーフローする
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
  bool isValidBST(TreeNode* root) {
    return IsValidBSTHelper(root, std::numeric_limits<int>::min(),
                            std::numeric_limits<int>::max());
  }

 private:
  bool IsValidBSTHelper(TreeNode* node, int min_value, int max_value) {
    if (!node) {
      return true;
    }
    if (!(min_value <= node->val && node->val <= max_value)) {
      return false;
    }
    return IsValidBSTHelper(node->left, min_value, node->val - 1)
           && IsValidBSTHelper(node->right, node->val + 1, max_value);
  }
};
