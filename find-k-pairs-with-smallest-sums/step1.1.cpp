
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>
using namespace std;

using comb = vector<int>;
class Solution {
 public:
  vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2,
                                     int k) {
    int boundary_pos = ceil(sqrt(k));
    map<int, comb> combination_map;
    for (int i = 0; i < boundary_pos; i++) {
      for (int j = 0; j < boundary_pos; j++) {
        combination_map.insert({nums1[i] + nums2[j], {nums1[i], nums2[j]}});
      }
    }
    int counter = 0;
    vector<comb> k_smallest_comb;
    auto itr = combination_map.begin();
    while (counter <= k && itr != combination_map.end()) {
      k_smallest_comb.push_back(itr->second);
      itr++;
      counter++;
    }
    return k_smallest_comb;
  }
};