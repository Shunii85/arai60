#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
 public:
  vector<int> twoSum(const vector<int>& nums, int target) {
    unordered_map<int, int> num_to_index;
    vector<int> two_num_indices;
    int num = 0;
    for (int num_i = 0; num_i < nums.size(); ++num_i) {
      num = nums[num_i];
      if (num_to_index.contains(num)) {
        int idx1 = num_to_index[num];
        two_num_indices.push_back(num_i);
        two_num_indices.push_back(idx1);
        break;
      }
      num_to_index.insert({target - num, num_i});
    }
    return two_num_indices;
  }
};