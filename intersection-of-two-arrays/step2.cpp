
#include <algorithm>
#include <vector>
using namespace std;
class Solution {
 public:
  vector<int> intersection(vector<int> nums1, vector<int> nums2) {
    vector<int> intersection;
    ranges::sort(nums1, ranges::greater());
    ranges::sort(nums2, ranges::greater());
    while (!nums1.empty() && !nums2.empty()) {
      int num1 = nums1.back();
      int num2 = nums2.back();
      if (num1 < num2) {
        nums1.pop_back();
        continue;
      }
      if (num1 > num2) {
        nums2.pop_back();
        continue;
      }
      if (num1 == num2) {
        nums1.pop_back();
        nums2.pop_back();
        if (!intersection.empty() && intersection.back() == num1) {
          continue;
        }
        intersection.push_back(num1);
      }
    }
    return intersection;
  }
};
