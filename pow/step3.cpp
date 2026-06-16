#include <cstdint>
class Solution {
 public:
  double myPow(double base_num, int64_t times) {
    if (times < 0) {
      base_num = 1 / base_num;
      times = -times;
    }
    return PowHelper(base_num, times);
  }
  double PowHelper(double base_num, int64_t times) {
    if (times == 0) {
      return 1;
    }
    if (times % 2 == 1) {
      return base_num * PowHelper(base_num * base_num, times / 2);
    }
    return PowHelper(base_num * base_num, times / 2);
  }
};