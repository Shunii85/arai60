#include <string>
#include <unordered_set>
#include <vector>
class Solution {
 public:
  bool wordBreak(std::string s, std::vector<std::string>& wordDict) {
    std::unordered_set<std::string> candidate_words(wordDict.begin(),
                                                    wordDict.end());
    std::string maked_word = "";
    for (char c : s) {
      maked_word.push_back(c);
      if (candidate_words.contains(maked_word)) {
        maked_word.clear();
      }
    }

    return maked_word.empty();
  }
};
