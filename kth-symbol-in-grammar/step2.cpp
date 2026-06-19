class Solution {
 public:
  int kthGrammar(int n, int k) {
    if (n == 1) {
      return 0;
    }
    int num_symbols = 1 << (n - 1);
    if (k > num_symbols / 2) {
      return 1 ^ kthGrammar(n - 1, k - num_symbols / 2);
    } else {
      return kthGrammar(n - 1, k);
    }
  }
};
