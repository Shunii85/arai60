class Solution {
 public:
  int kthGrammar(int n, int k) { return Helper(1 << (n - 1), k); }
  int Helper(int num_symbols, int k) {
    if (num_symbols == 1) {
      return 0;
    }
    if (k > num_symbols / 2) {
      return Helper(num_symbols / 2, k - num_symbols / 2) ^ 1;
    } else {
      return Helper(num_symbols / 2, k);
    }
  }
};
