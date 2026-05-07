# step1

ある文字列と辞書が与えられたときに、文字列が辞書内の単語で構成されるかどうかを判定する。

- 文字ごとに見ていって、文字列を作っていけばいい。で、辞書のなかにあるかどうかで判断する。

- 詳細に考えると。
  - 文字列の箱を用意する。
  - 1文字ずつ見ていって、文字列の箱に文字を入れていって文字列を作る。
  - 追加するたびに、辞書のなかにその単語がないかを判断していく。
  - 単語があれば、文字列を空っぽにしてまた始める。
  - 最後まで進めて、文字列の箱に文字が残されていたら、すべてを辞書から単語に分割できなかったのでfalse   

- 時間計算量としては、文字列の長さをL, 単語の数をNとすると
  - ハッシュ化に文字列の長さ分かかるとしたら、O(N + L^2)かな
    - unordered_setを用意するのに、O(N)
    - L回分ループが回る。全文字列捜査
      - そのときの作られた文字列の長さ分のhash化
  - O(1)でunordered_mapが使えるなら、O(N + L)


- 間違っていた。そんなに単純ではなかったよう

```cpp
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
```

- 落ちたケースは、
  - s = "aaaaaaa"
  - wordDict = ["aaaa","aaa"]

- こういうのは考えられていなかった
- ユニークだからといって、辞書内の文字列間に包含関係がないわけではない。

- どんな区切り方がいいのかわからない。
  s = "bcde"で、dict = ["bc", "de", "bcd"]
  なら、長いbcdを選んでしまったら、eが選べなくなる。

---

わからなくて答えを見た。色々なやり方がありそう。

## 解法 1

- まずは、単純に、単語を作っていく作業を地道にやる方法。

- どうやったら適切な単語の切れ目を見つけられるだろう？と思っていたけど、単純なやり方、遅いけど着実にできる方法に、すべての選択肢を見つけるというほうほうがある。
- つまり、最初の1文字目を部分文字列の1文字目と選んだならば、そこから1つずつ最後まで文字を足して部分文字列を作って、それを選択肢として、queueに入れる。BFSをしようということだ。最終的に、lengthまでたどり着けるpathがあれば、それは正しいと言える。

- LeetCodeの答えを見てから、自分ならこう書くなーと考えながら書いて、Acceptすることはできた。
- 答えと変えたところ。
  - 変数名
  - 部分文字列を作るときに、substrメソッドを作っていたけど、それだと重なる部分をいちいち作っているので、それを単純にappendする方式にした。


```cpp
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>
class Solution {
 public:
  bool wordBreak(const std::string s,
                 const std::vector<std::string>& word_dict) {
    std::unordered_set<std::string> word_set(word_dict.begin(),
                                             word_dict.end());
    std::vector<int> position_reached(s.length(), false);
    std::queue<int> start_positions({0});

    while (!start_positions.empty()) {
      int start = start_positions.front();
      start_positions.pop();

      if (start == s.length()) {
        return true;
      }

      std::string substring = "";
      for (int end = start; end < s.length(); ++end) {
        substring.push_back(s[end]);
        if (position_reached[end]) {
          continue;
        }
        if (word_set.contains(substring)) {
          position_reached[end] = true;
          start_positions.push(end + 1);
        }
      }
    }

    return false;
  }
};
```

- 計算量があまり想像つかない。
- position_reachedで書くポジションには一回だけ処理するようにしているけれど、結局毎回 end から s.length() - 1まではfor文は回るのであって、それは変わらない。
- だから予想できないのは、whileの2回目のループ以降だろう。

文字列の長さをL、word_dictの大きさをN、word_dictの中の単語の平均の長さをKとすると
- word_setのに、O(N * K)
- position_reachedを作るのに、O(L)
- start_positionsに入ってくるのは、最大でL。position_reachedで、単語を作っていきながらたどり着いた場所を記録しているので、どれだけ細かく単語がわかれても、与えられた文字列の長さだけしか、たどり着く場所はないから。
  - 各start_positionsのstartから、文字列の最後まで単語を作り続ける。
  - 毎回 Lだけ作るとする。
- そうすると、whileの部分は、L^2かな。word_set.containsで、文字列の長さ分ハッシュの計算にかかるとすると、L^3かかるか？

- よって、時間計算量は、
 - O(L^3 + N * K)

- 以下の制約の最大を適用すると、
```
1 <= s.length <= 300
1 <= wordDict.length <= 1000
1 <= wordDict[i].length <= 20
```

- 2.7 * 10^7 + 2 * 10^4
だいたい、2.7*10^7

- 一秒以内では終わる。

## 解法2

- top-downのDP。要するに、文字列の各文字に人をおいて、その文字まで作れるかどうかを教えてもらう。
- それで、末尾の文字から始めるから、top - down

```cpp
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

    for (const auto word : word_dict) {
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
```

## 解法3

- bottom-up dp
  - top-downは、s.length() - 1から始める方法だった。順番に先頭に向かって評価していって最終最後の文字までword breakができるかどうか評価された。
  - それにくらべて、これまで自分で書いてきたようなDP、最初から始める方法。
- 今回も、LeetCodeの答えを理解してから、自分なりに思い出しながら、書き直しながらやって1回でできた。
- これのおかげで、top-downのDPへの理解にもつながったような気がする。

- reachableは順番に決まっていくから、iより先のほうが、先に計算されることはない。

```cpp
#include <string>
#include <vector>
class Solution {
 public:
  bool wordBreak(const std::string& s,
                 const std::vector<std::string>& word_dict) {
    std::vector<int> reachable(s.length(), false);

    for (int i = 0; i < s.length(); ++i) {
      if (reachable[i]) { // ここの条件節いらない。
        continue;
      }
      for (const auto& word : word_dict) {
        int start = i - word.length() + 1;
        if (start < 0) {
          continue;
        }
        if (start == 0 || reachable[start - 1]) {
          if (s.substr(start, word.length()) == word) {
            reachable[i] = true;
          }
        }
      }
    }

    return reachable[s.length() - 1];
  }
};
```

## コメント集を読んだ

- オートマトンというワードが出てきた。
  - なにか聞き覚えはある。正規表現のエンジンを作ろうみたいなので聞いたことがある。


# step2

- 解法3で取り組む。
- 他のコードなどを読んでいて、部分文字列を作る前に、最初の文字同士の区別で、少し時間短縮ができるかもしれないと思った。

```cpp
#include <string>
#include <vector>
class Solution {
 public:
  bool wordBreak(const std::string& s,
                 const std::vector<std::string>& word_dict) {
    std::vector<int> reachable(s.length(), false);

    for (int i = 0; i < s.length(); ++i) {
      for (const auto& word : word_dict) {
        int start = i - word.length() + 1;
        if (start < 0 || s[start] != word[0]) {
          continue;
        }
        if (start == 0 || reachable[start - 1]) {
          if (s.substr(start, word.length()) == word) {
            reachable[i] = true;
          }
        }
      }
    }

    return reachable[s.length() - 1];
  }
};
```

# step3

1. 3分44秒

少し書き方変わった。

```cpp
#include <string>
#include <vector>
class Solution {
 public:
  bool wordBreak(const std::string& s,
                 const std::vector<std::string>& word_dict) {
    std::vector<int> reachable(s.length(), false);

    for (int i = 0; i < s.length(); ++i) {
      for (const auto& word : word_dict) {
        int start = i - word.length() + 1;
        if (start < 0 || s[start] != word[0]) {
          continue;
        }
        if (start == 0 || reachable[start - 1]) {
          if (s.substr(start, word.length()) == word) {
            reachable[i] = true;
          }
        }
      }
    }

    return reachable[s.length() - 1];
  }
};
```

2. 3分18秒
3. 3分04秒
