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
  TreeNode* sortedArrayToBST(std::vector<int>& nums) {
    return convert(nums, 0, nums.size() - 1);
  }

 private:
  TreeNode* convert(std::vector<int>& nums, int left, int right) {
    if (left > right) {
      return nullptr;
    }
    int middle = left + (right - left) / 2;
    TreeNode* node = new TreeNode(nums[middle]);
    node->left = convert(nums, left, middle - 1);
    node->right = convert(nums, middle + 1, right);
    return node;
  }
};
