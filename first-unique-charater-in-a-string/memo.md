# step1

文字列の中で、ユニークでかつ最も始めに登場する文字の場所を突き止めたい。

## 解法1

登場した文字と、登場した場所をメモしていく。
登場した場所の数が1つなら、そのなかでインデックスが最も小さいものを選ぶ。

mapのCompareを、indexのfirstに設定しておけば実装はできそう。
でももっといい方法はないかなぁ、、、

---

実装方法がわからずに答えを見た。

単純に、一回目は登場回数を確認して、2回目の探索で、ユニークならそこで初めて返すということにすればいい。

### 計算量

- 時間計算量
  - O(N)
  - 最大10^5が入って、
  - 10^-4 ~ 10^-3 sec
  - 1ms ~ 10ms
  - 実際はこの2倍ほどかかる。

- 空間計算量
  - O(N)
  - 1char と int(4Byte)
  - 10^5charと10^5int
  - よって5*10^5Byte
  - 500KB

---

1パスで書く方法はないのだろうか。



## 解法2
新しい文字を発見したら、その文字かどうかをひたすら探していく。

これはしんどい。もし文字がものすごく大きい距離をもってして配置されていたらやろうとは思わない。

## 他の人のコードを見る

1passでの実装方法

https://github.com/colorbox/leetcode/pull/29/changes#r1861430039


```c++
class Solution {
  struct CharacterAndIndex {
    char c;
    int index;
  };

 public:
  int firstUniqChar(string s) {
    map<char, int> char_to_count;
    queue<CharacterAndIndex> characters;
    for (int i = 0; i < s.size(); ++i) {
      char c = s[i];
      characters.push({c, i});
      ++char_to_count[c];

      while (!characters.empty() && char_to_count[characters.front().c] >= 2) {
        characters.pop();
      }
    }

    if (!characters.empty()) {
      return characters.front().index;
    }

    return -1;
  }
};
```

この考え方としては、携帯電話をもった2人の仲間を用意して、一人には文字を走って確認させる。
一人は先頭に立つようにする。

文字ごとの登場回数をメモするシートを2人で共有しておく。

文字を1文字確認して共有シートを更新する。

先頭に立っている人は、今自分が見ている文字の登場回数が1回の場合はそのまま待機。
もし、2回になっていたら、前の文字に進む。
登場回数が1回の文字まですすめたら、それを仲間に連絡する。

これを参考にして、queueを使わなくても行けるなと思って`step1-2.cpp`に書いてみた。

1passだけど、時間が解法1よりも結構かかっている。なぜだろう。

geminiに相談してみると、単純にunordered_mapを確認する回数が多いかららしい。

だけど最悪の場合は確認回数は変わらないんじゃないかな？

先頭に立っている人が共有シートを確認する回数は、最大でN回になるはずで、

解法1でも最後まで行くときはN回 char_to_count[s[c]] == cか確認する。


# step2

解法1を採用する。

ほぼ変更なし。

``cpp
#include <string>
#include <unordered_map>
#include <vector>
class Solution {
 public:
  int firstUniqChar(const std::string& s) {
    std::unordered_map<char, int> char_to_count;
    for (char c : s) {
      char_to_count[c] += 1;
    }
    for (int char_i = 0; char_i < s.length(); ++char_i) {
      if (char_to_count[s[char_i]] == 1) {
        return char_i;
      }
    }
    return -1;
  }
};
```