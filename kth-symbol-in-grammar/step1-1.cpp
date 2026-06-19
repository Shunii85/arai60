class Solution {
 public:
  int kthGrammar(int n, int k) {
    bool reversed = false;
    int num_nth_symbols = 1 << (n - 1);

    while (num_nth_symbols > 1) {
      num_nth_symbols /= 2;
      if (k > num_nth_symbols) {
        reversed = !reversed;
        k -= num_nth_symbols;
      }
    }

    return !reversed ? 0 : 1;
  }
};
