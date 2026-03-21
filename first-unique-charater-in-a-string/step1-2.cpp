#include <string>
#include <unordered_map>
class Solution {
 public:
  int firstUniqChar(const std::string& s) {
    std::unordered_map<char, int> char_to_count;
    int maybe_first_unique_pos = 0;
    int checking_pos = 0;
    while (checking_pos < s.length()) {
      char c = s[checking_pos++];
      ++char_to_count[c];

      while (maybe_first_unique_pos < s.length()
             && char_to_count[s[maybe_first_unique_pos]] > 1) {
        ++maybe_first_unique_pos;
      }
    }
    if (maybe_first_unique_pos == s.length()) return -1;
    return maybe_first_unique_pos;
  }
};