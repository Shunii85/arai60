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
    return valid(root, std::numeric_limits<long long>::min(),
                 std::numeric_limits<long long>::max());
  }

 private:
  bool valid(TreeNode* node, long long minimum, long long maximum) {
    if (!node) {
      return true;
    }
    if (!(minimum < node->val && node->val < maximum)) {
      return false;
    }

    return valid(node->left, minimum, node->val)
           && valid(node->right, node->val, maximum);
  }
};
