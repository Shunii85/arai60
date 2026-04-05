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
  bool isValidBST(TreeNode* root) {
    return IsValidBSTHelper(root, nullptr, nullptr);
  }

 private:
  bool IsValidBSTHelper(TreeNode* node, TreeNode* min_node,
                        TreeNode* max_node) {
    if (!node) {
      return true;
    }
    if (min_node && node->val <= min_node->val) {
      return false;
    }
    if (max_node && node->val >= max_node->val) {
      return false;
    }
    return IsValidBSTHelper(node->left, min_node, node)
           && IsValidBSTHelper(node->right, node, max_node);
  }
};
