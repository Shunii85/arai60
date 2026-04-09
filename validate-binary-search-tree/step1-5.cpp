struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

#include <vector>
class Solution {
 public:
  bool isValidBST(TreeNode* root) {
    if (!root) {
      return false;
    }
    std::vector<int> sorted_inorder_values;
    SortInorder(root, sorted_inorder_values);
    int prev_value = sorted_inorder_values[0];
    for (int i = 1; i < sorted_inorder_values.size(); ++i) {
      int current_value = sorted_inorder_values[i];
      if (!(prev_value < current_value)) {
        return false;
      }
      prev_value = current_value;
    }
    return true;
  }

 private:
  void SortInorder(TreeNode* node, std::vector<int>& sorted) {
    if (!node) {
      return;
    }
    SortInorder(node->left, sorted);
    sorted.push_back(node->val);
    SortInorder(node->right, sorted);
  }
};
