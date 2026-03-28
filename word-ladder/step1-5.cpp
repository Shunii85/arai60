// 隣接リスト
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
using WordAndDistance = std::pair<std::string, int>;
class Solution {
 public:
  int ladderLength(std::string beginWord, std::string endWord,
                   std::vector<std::string> wordList) {
    wordList.push_back(beginWord);
    auto word_to_adjacents = createWordToAdjacents(beginWord, wordList);
    std::queue<WordAndDistance> word_and_distance;
    std::unordered_set<std::string> visited;
    word_and_distance.push({beginWord, 1});
    visited.insert(beginWord);
    while (!word_and_distance.empty()) {
      auto [word, distance] = std::move(word_and_distance.front());
      word_and_distance.pop();
      for (auto next_word : word_to_adjacents[word]) {
        if (next_word == endWord) {
          return distance + 1;
        }
        if (visited.contains(next_word)) {
          continue;
        }
        word_and_distance.push({next_word, distance + 1});
        visited.insert(next_word);
      }
    }
    return 0;
  }

 private:
  std::unordered_map<std::string, std::vector<std::string>>
  createWordToAdjacents(std::string begin_word,
                        const std::vector<std::string>& word_list) {
    std::unordered_map<std::string, std::vector<std::string>> word_to_adjacents(
        word_list.size());
    for (auto word1 : word_list) {
      for (auto word2 : word_list) {
        if (word1 == word2) {
          continue;
        }
        if (IsTransformable(word1, word2)) {
          word_to_adjacents[word1].push_back(word2);
          word_to_adjacents[word2].push_back(word1);
        }
      }
    }
    return std::move(word_to_adjacents);
  }
  bool IsTransformable(const std::string& before_str,
                       const std::string& after_str) {
    if (before_str.length() != after_str.length()) {
      return false;
    }
    int different_char_num = 0;
    for (int str_index = 0; str_index < before_str.length(); ++str_index) {
      if (before_str[str_index] != after_str[str_index]) {
        ++different_char_num;
      }
      if (different_char_num > 1) {
        return false;
      }
    }
    return different_char_num == 1;
  };
};