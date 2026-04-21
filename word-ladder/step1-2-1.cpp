// 実行時間が結構かかる。
#include <queue>
#include <string>
#include <unordered_map>
class Solution {
 public:
  int ladderLength(std::string beginWord, std::string endWord,
                   std::vector<std::string>& wordList) {
    std::queue<std::string> next_words;
    std::unordered_map<std::string, int> word_to_transformation_order;
    next_words.push(beginWord);
    word_to_transformation_order[beginWord] = 1;
    while (!next_words.empty()) {
      auto word = std::move(next_words.front());
      next_words.pop();
      if (word == endWord) {
        return word_to_transformation_order[word];
      }
      int next_order = word_to_transformation_order[word] + 1;
      // ここで毎回wordlistを引き回しているのが原因。
      for (auto maybe_next_word : wordList) {
        bool visited = word_to_transformation_order[maybe_next_word] > 0;
        if (!visited && IsTransformable(word, maybe_next_word)) {
          next_words.push(maybe_next_word);
          word_to_transformation_order[maybe_next_word] = next_order;
        }
      }
    }
    return 0;
  }

 private:
  bool IsTransformable(std::string& before_str, std::string& after_str) {
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