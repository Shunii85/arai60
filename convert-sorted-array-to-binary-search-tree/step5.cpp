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
  TreeNode* build(const std::vector<int>& nums, int start_position,
                  int end_position) {
    if (start_position > end_position) {
      return nullptr;
    }
    int middle_position = (start_position + end_position) / 2;
    return new TreeNode(nums[middle_position],
                        build(nums, start_position, middle_position - 1),
                        build(nums, middle_position + 1, end_position));
  }
};