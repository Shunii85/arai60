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
  double PowHelper(double base_num, int64_t n) {
    if (n == 0) {
      return 1;
    }
    if (n % 2 == 1) {
      return base_num * PowHelper(base_num * base_num, n / 2);
    }
    return PowHelper(base_num * base_num, n / 2);
  }
};
