#include <cmath>
class Solution {
 public:
  int kthGrammar(int n, int k) {
    if (n == 1) {
      return 0;
    }
    int parent = kthGrammar(n - 1, std::ceil(k / 2));
    bool odd_indexed_position = k % 2 == 1;
    if (parent == 1) {
      return odd_indexed_position ? 1 : 0;
    } else {
      return odd_indexed_position ? 0 : 1;
    }
  }
};
