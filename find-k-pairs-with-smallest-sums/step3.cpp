#include <queue>
#include <set>
#include <vector>
using namespace std;

using IdxPair = pair<int, int>;
class Solution {
 public:
  vector<vector<int>> kSmallestPairs(const vector<int>& nums1,
                                     const vector<int>& nums2, int k) {
    priority_queue<pair<int, IdxPair>, vector<pair<int, IdxPair>>,
                   greater<pair<int, IdxPair>>>
        smallests;
    set<IdxPair> picked;
    vector<vector<int>> k_smallest_pairs;

    smallests.push({nums1[0] + nums2[0], {0, 0}});
    picked.insert({0, 0});
    while (k-- && !smallests.empty()) {
      auto [_, kth_smallest_idx_pair] = smallests.top();
      auto [i, j] = kth_smallest_idx_pair;
      smallests.pop();
      k_smallest_pairs.push_back({nums1[i], nums2[j]});
      if (i + 1 < nums1.size() && !picked.contains({i + 1, j})) {
        smallests.push({nums1[i + 1] + nums2[j], {i + 1, j}});
        picked.insert({i + 1, j});
      }
      if (j + 1 < nums2.size() && !picked.contains({i, j + 1})) {
        smallests.push({nums1[i] + nums2[j + 1], {i, j + 1}});
        picked.insert({i, j + 1});
      }
    }
    return k_smallest_pairs;
  }
};