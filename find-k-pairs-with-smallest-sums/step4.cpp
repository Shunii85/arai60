#include <queue>
#include <vector>
using IndexPair = std::pair<int, int>;
class Solution {
 public:
  std::vector<std::vector<int>> kSmallestPairs(std::vector<int>& nums1,
                                               std::vector<int>& nums2, int k) {
    std::vector<std::vector<int>> k_smallests;
    auto ascending_with_sum = [&nums1, &nums2](const IndexPair& p1,
                                               const IndexPair& p2) {
      return nums1[p1.first] + nums2[p1.second]
             > nums1[p2.first] + nums2[p2.second];
    };
    std::priority_queue<IndexPair, std::vector<IndexPair>,
                        decltype(ascending_with_sum)>
        smallest_index_pairs(ascending_with_sum);
    for (int nums1_i = 0; nums1_i < nums1.size(); ++nums1_i) {
      smallest_index_pairs.push({nums1_i, 0});
    }
    int count = 0;
    while (count < k) {
      auto [nums1_i, nums2_i] = smallest_index_pairs.top();
      smallest_index_pairs.pop();
      k_smallests.push_back({nums1[nums1_i], nums2[nums2_i]});
      if (nums2_i + 1 < nums2.size()) {
        smallest_index_pairs.push({nums1_i, nums2_i + 1});
      }
      ++count;
    }
    return k_smallests;
  }
};