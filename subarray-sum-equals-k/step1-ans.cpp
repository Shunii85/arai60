// 標高の考え方で書いた。
#include <unordered_map>
#include <vector>
class Solution {
 public:
  int subarraySum(const std::vector<int>& nums, int k) {
    std::unordered_map<int, int> elevation_to_count;
    int elevation = 0;
    int count = 0;
    elevation_to_count.insert({elevation, 1});
    for (int difference : nums) {
      elevation += difference;
      if (elevation_to_count.contains(elevation - k)) {
        count += elevation_to_count[elevation - k];
      }
      elevation_to_count[elevation] += 1;
    }
    return count;
  }
};