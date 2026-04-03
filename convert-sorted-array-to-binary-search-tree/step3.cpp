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
  TreeNode* sortedArrayToBST(const std::vector<int>& nums) {
    return build(nums, 0, nums.size() - 1);
  }

 private:
  TreeNode* build(const std::vector<int>& nums, int left_i, int right_i) {
    if (!(left_i <= right_i)) {
      return nullptr;
    }
    int middle_i = (left_i + right_i) / 2;
    return new TreeNode(nums[middle_i], build(nums, left_i, middle_i - 1),
                        build(nums, middle_i + 1, right_i));
  }
};