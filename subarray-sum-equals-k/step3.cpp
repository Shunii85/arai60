#include <unordered_map>
#include <vector>
class Solution {
 public:
  int subarraySum(const std::vector<int>& nums, int k) {
    int count = 0;
    int prefix_sum = 0;
    std::unordered_map<int, int> prefix_sum_to_count;
    prefix_sum_to_count.insert({0, 1});
    for (int n : nums) {
      prefix_sum += n;
      if (prefix_sum_to_count.contains(prefix_sum - k)) {
        count += prefix_sum_to_count[prefix_sum - k];
      }
      prefix_sum_to_count[prefix_sum] += 1;
    }
    return count;
  }
};