#include <algorithm>
#include <vector>
class KthLargest {
 private:
  int k_idx;
  std::vector<int> scores;

 public:
  KthLargest(int k, std::vector<int>& nums) : k_idx(k - 1), scores(nums) {}

  int add(int val) {
    scores.push_back(val);
    std::sort(scores.begin(), scores.end(), std::greater<int>{});
    return scores.at(k_idx);
  }
};

// KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
// kthLargest.add(3); // return 4
// kthLargest.add(5); // return 5
// kthLargest.add(10); // return 5
// kthLargest.add(9); // return 8
// kthLargest.add(4); // return 8