#include <algorithm>
#include <vector>
class KthLargest {
 private:
  int k_idx;
  std::vector<int> scores;

 public:
  KthLargest(int k, std::vector<int>& nums) : k_idx(k - 1) {
    std::sort(nums.begin(), nums.begin() + k);
    std::copy(nums.begin(), nums.begin() + k, scores);
  }

  int add(int val) {
    if (val < scores.at(k_idx)) {
      return scores.at(k_idx);
    }
    scores[k_idx] = val;
    std::sort(scores.begin(), scores.end(), std::greater<int>{});
    return scores.at(k_idx);
  }
};