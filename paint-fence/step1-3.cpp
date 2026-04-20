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
    int nth = 2;  // now complete the num of patterns by 2th;
    int two_back = k;
    int one_back = k * k;
    int current = 0;
    while (nth < n) {
      current = one_back * (k - 1) + two_back * (k - 1);
      two_back = one_back;
      one_back = current;
      ++nth;
    }
    return current;
  }
};
