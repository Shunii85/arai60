struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

#include <cassert>
#include <deque>
#include <unordered_map>
#include <vector>
class Solution {
 public:
  TreeNode* buildTree(const std::vector<int>& preorder,
                      const std::vector<int>& inorder) {
    std::deque<int> preorder_store(preorder.begin(), preorder.end());
    std::unordered_map<int, int> inorder_value_to_index;
    inorder_value_to_index.reserve(inorder.size());
    for (int index = 0; index < inorder.size(); ++index) {
      inorder_value_to_index[inorder[index]] = index;
    }
    return build(preorder_store, inorder_value_to_index, 0, inorder.size() - 1);
  }

 private:
  TreeNode* build(std::deque<int>& preorder_store,
                  const std::unordered_map<int, int>& inorder_value_to_index,
                  int start_position, int end_position) {
    if (start_position > end_position) {
      return nullptr;
    }
    assert(!preorder_store.empty());
    int sub_root_value = preorder_store.front();
    preorder_store.pop_front();
    assert(inorder_value_to_index.contains(sub_root_value));
    int position = inorder_value_to_index.at(sub_root_value);
    return new TreeNode(sub_root_value,
                        build(preorder_store, inorder_value_to_index,
                              start_position, position - 1),
                        build(preorder_store, inorder_value_to_index,
                              position + 1, end_position));
  }
};
