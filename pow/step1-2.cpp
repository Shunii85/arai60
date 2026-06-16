class Solution {
 public:
  double myPow(double x, int n) {
    long long times = n;
    if (n < 0) {
      times = -times;
      x = 1 / x;
    }
    return PowHelper(x, times);
  }
  double PowHelper(double x, long long n) {
    if (n == 0) {
      return 1;
    }
    if (n % 2 == 1) {
      return x * PowHelper(x * x, n / 2);
    }
    return PowHelper(x * x, n / 2);
  }
};
