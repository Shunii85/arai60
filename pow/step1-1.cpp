#include <cmath>
class Solution {
 public:
  double myPow(double x, int n) {
    double power = 1;
    unsigned int times = std::abs(n);
    for (int i = 0; i < times; ++i) {
      power *= x;
    }
    return n >= 0 ? power : 1 / power;
  }
};