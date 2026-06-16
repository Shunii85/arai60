class Solution {
 public:
  double myPow(double x, int n) {
    long long times = n;
    if (times < 0) {
      times = -times;
      x = 1 / x;
    }
    double power = 1;
    double base_num = x;
    while (times > 0) {
      if (times % 2 == 1) {
        power *= base_num;
      }
      base_num *= base_num;
      times /= 2;
    }
    return power;
  }
};
