// 単方向BFS
#include <string>
#include <unordered_set>
#include <vector>
class Solution {
 public:
  int ladderLength(std::string beginWord, std::string endWord,
                   std::vector<std::string>& wordList) {
    std::unordered_set<std::string> word_set(wordList.begin(), wordList.end());
    if (!word_set.contains(endWord)) {
      return 0;
    }
    std::unordered_set<std::string> frontier_words{beginWord};
    std::unordered_set<std::string> visited;
    int ladder_length = 1;
    while (!frontier_words.empty()) {
      std::unordered_set<std::string> next_words;
      for (auto word : frontier_words) {
        for (int i = 0; i < word.size(); ++i) {
          char original = word[i];
          for (char c = 'a'; c <= 'z'; ++c) {
            if (c == original) {
              continue;
            }
            word[i] = c;
            if (word == endWord) {
              return ladder_length + 1;
            }
            if (!visited.count(word) && word_set.count(word)) {
              next_words.insert(word);
              visited.insert(word);
            }
          }
          word[i] = original;
        }
      }
      frontier_words = std::move(next_words);
      ++ladder_length;
    }
    return 0;
  }
};