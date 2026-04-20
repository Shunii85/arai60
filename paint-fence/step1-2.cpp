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
    int nth = 2;
    int same = k;
    int different = k * (k - 1);
    while (nth < n) {
      int prev_same = same;
      int prev_different = different;
      same = prev_different;
      different = (prev_same + prev_different) * (k - 1);
      ++nth;
    }
    return same + different;
  }
};
