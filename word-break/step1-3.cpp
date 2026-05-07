#include <string>
#include <vector>
class Solution {
 public:
  bool wordBreak(const std::string& s,
                 const std::vector<std::string>& word_dict) {
    // -1: not calculated yet. 0: unable. 1: able
    std::vector<int> reachable_memo(s.length(), -1);
    return reachable(s.length() - 1, s, reachable_memo, word_dict);
  }

 private:
  bool reachable(const int index, const std::string& target_str,
                 std::vector<int>& reachable_memo,
                 const std::vector<std::string>& word_dict) {
    if (index == -1) {
      return true;
    }
    if (reachable_memo[index] != -1) {
      return reachable_memo[index];
    }

    for (const auto& word : word_dict) {
      int start = index - word.length() + 1;
      if (start < 0) {
        continue;
      }
      if (!reachable(start - 1, target_str, reachable_memo, word_dict)) {
        continue;
      }
      std::string sub_string = target_str.substr(start, word.length());
      if (sub_string == word) {
        return reachable_memo[index] = 1;
      }
    }

    return reachable_memo[index] = 0;
  }
};
