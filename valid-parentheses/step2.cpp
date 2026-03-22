#include <map>
#include <stack>
#include <string>

using namespace std;

// LeetCodeには上のプログラムは必要ない

class Solution {
 public:
  bool isValid(string s) {
    std::stack<char> open_brackets;
    std::map<char, char> match_brackets{
        {'(', ')'},
        {'{', '}'},
        {'[', ']'},
    };
    for (char bracket : s) {
      switch (bracket) {
        case '(':
        case '{':
        case '[':
          open_brackets.push(bracket);
          break;
        case ')':
        case '}':
        case ']':
          if (open_brackets.empty()
              || match_brackets[open_brackets.top()] != bracket) {
            return false;
          }
          open_brackets.pop();
          break;
        default:
          return false;
      }
    }
    return open_brackets.empty();
  }
};
