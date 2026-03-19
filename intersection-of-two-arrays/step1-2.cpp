#include <algorithm>
#include <set>
#include <vector>
using namespace std;
class Solution {
 public:
  vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    vector<int> intersection;
    set<int> unique_nums1(nums1.begin(), nums1.end());
    set<int> unique_nums2(nums2.begin(), nums2.end());
    set_intersection(unique_nums1.begin(), unique_nums1.end(),
                     unique_nums2.begin(), unique_nums2.end(),
                     back_inserter(intersection));
    return intersection;
  }
};
