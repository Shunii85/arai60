class Solution {
 public:
  int numWays(int n, int k) {
    if (n == 0) {
      return 0;
    }
    if (n == 1) {
      return k;
    }
    if (n == 2) {
      return k * k;
    }
    int two_back = k;
    int one_back = k * k;
    int current = 0;
    for (int nth = 3; nth <= n; ++nth) {
      current = one_back * (k - 1);   // chose different color from last;
      current += two_back * (k - 1);  // chose same color from last;

      two_back = one_back;
      one_back = current;
    }
    return current;
  }
};
