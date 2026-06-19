class Solution {
 public:
  int kthGrammar(int n, int k) {
    if (n == 1) {
      return 0;
    }
    int previous_row_num_symbols = 1 << (n - 2);
    if (k > previous_row_num_symbols) {
      return 1 ^ kthGrammar(n - 1, k - previous_row_num_symbols);
    }
    return kthGrammar(n - 1, k);
  }
};
