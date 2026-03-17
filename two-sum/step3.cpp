#include <unordered_map>
#include <vector>
using namespace std;
class Solution {
 public:
  vector<int> twoSum(const vector<int>& nums, int target) {
    vector<int> two_num_indices;
    unordered_map<int, int> num_to_index;
    int num = 0;
    for (int num_i = 0; num_i < nums.size(); ++num_i) {
      num = nums[num_i];
      if (!num_to_index.contains(num)) {
        num_to_index.insert({target - num, num_i});
      } else {
        two_num_indices.push_back(num_i);
        two_num_indices.push_back(num_to_index[num]);
        break;
      }
    }
    return two_num_indices;
  }
};