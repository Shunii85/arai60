# step1

- 与えられた配列から、和が最大になる部分配列を返す。
- 部分配列は、もとの配列の要素が隣同士のもので構成されるものでないといけない。

- 前の、駅と駅の間の標高を考えるやり方で。
- 一番標高が低い場所と、高い場所がそれぞれわかれば、その間の標高差を求めれば、sumがわかる。

```cpp
#include <algorithm>
#include <vector>
class Solution {
 public:
  int maxSubArray(const std::vector<int>& nums) {
    int lowest_elevation = 0;
    int highest_elevation = 0;
    int elevation = 0;
    for (int difference : nums) {
      elevation += difference;
      lowest_elevation = std::min(elevation, lowest_elevation);
      highest_elevation = std::max(elevation, highest_elevation);
    }
    return highest_elevation - lowest_elevation;
  }
};
```

- なんかそう簡単にはできなさそう。
- これ、lowest_elevationとhighest_elevationの向きとういか、横軸方向の関係が崩れる気がする。最初に最も標高の高い場所がでてきて、あとから最も低い場所がでてきたら、それは違う。
- 最も低い標高がでたからといって、そのあと標高が上がる場所があるかどうかはわからない。
  - 結局比べあいっこしないとわからない。
- あと、ひたすら下っていった場合、nums[0]が最大になるところが難点だなと思っている。

```cpp
class Solution {
 public:
  int maxSubArray(const std::vector<int>& nums) {
    if (nums.size() == 0) {
      return 0;
    }
    // includes each largest sums
    std::vector<int> gaps(nums.size());
    gaps[0] = nums[0];
    int elevation = nums[0];
    int lowest_elevation = nums[0] < 0 ? nums[0] : 0;
    for (int i = 1; i < nums.size(); ++i) {
      elevation += nums[i];
      if (elevation < lowest_elevation) {
        lowest_elevation = elevation;
        gaps[i] = nums[i];
        continue;
      }
      gaps[i] = elevation - lowest_elevation;
    }
    return *std::max_element(gaps.begin(), gaps.end());
  }
};
```

- 最も低い標高のみを記録することにした。
- gaps[i]には、i番目を含めた、0からi番目までの部分配列を作る時、最もその和が大きいものを記録する。
- 標高が下がる時(nums[i] < 0)、最も標高が低い地点(lowest_elevation)よりも下がってしまうなら、上がれないということ。つまり、下がる標高がなるべく小さい、自分自身のみの値をgaps[i]に入れる。

- けど、gaps[i]っていらなくないか？

```cpp
#include <algorithm>
#include <limits>
#include <vector>
class Solution {
 public:
  int maxSubArray(const std::vector<int>& nums) {
    if (nums.size() == 0) {
      return 0;
    }
    int elevation = 0;
    int lowest_elevation = 0;
    int max_difference = std::numeric_limits<int>::min();
    for (int differnece : nums) {
      elevation += differnece;
      if (elevation < lowest_elevation) {
        lowest_elevation = elevation;
        max_difference = std::max(max_difference, differnece);
        continue;
      }
      max_difference = std::max(max_difference, elevation - lowest_elevation);
    }
    return max_difference;
  }
};
```

- できた。
- なんか自分のコードがなぜ動いているのかわからなくなった。というかわかっていなかった。
- 特に、elevation < lowest_elevationの中
  - よくないのが、最初にこの条件のときは、lowest_elevationを更新だけして、次に進むという実装をしたときに
    [-2, -1]のようなケースでうまく動かなくて、ここがわるかったのかと変更した。
  - 標高が下がっていくときに、どのように考えればよいのかわかっていなさそう。
    - [-2, 1, -3, ...]となったとき、-3を含む部分列で和が大きくなるのは、[1, -3]の-2。
  - どれだけ上昇できたかを知りたいけど、ひたすら上昇しない可能性もある。

- なぜか落ちたケースによくわからないアプローチをとって、意味のわからないコードを書いていた。なぜ通ったのかはわからないし、たぶん通ってはだめだったように思う。
- lowest_elevationが更新されるときは、elevation - lowest_elevationが下ったとしても最もその下り具合が小さく済む。だから、これでいい。

```cpp
class Solution {
 public:
  int maxSubArray(const std::vector<int>& nums) {
    if (nums.size() == 0) {
      return 0;
    }
    int elevation = 0;
    int lowest_elevation = 0;
    int max_difference = std::numeric_limits<int>::min();
    for (int differnece : nums) {
      elevation += differnece;
      if (elevation < lowest_elevation) {
        max_difference = std::max(max_difference, elevation - lowest_elevation);
        lowest_elevation = elevation;
        continue;
      }
      max_difference = std::max(max_difference, elevation - lowest_elevation);
    }
    return max_difference;
  }
};
```

- で、まとめられそうだから

```cpp
class Solution {

 public:
  int maxSubArray(const std::vector<int>& nums) {
    if (nums.size() == 0) {
      return 0;
    }
    int elevation = 0;
    int lowest_elevation = 0;
    int max_difference = std::numeric_limits<int>::min();
    for (int differnece : nums) {
      elevation += differnece;
      max_difference = std::max(max_difference, elevation - lowest_elevation);
      lowest_elevation = std::min(lowest_elevation, elevation);
    }
    return max_difference;
  }
};
```
# step3

1. 3分20秒
2. 2分20秒
2. 2分10秒

- Kadaneというアルゴリズムがあるらしい。
  - https://github.com/sakupan102/arai60-practice/pull/33#discussion_r1611415355
    - 書き換えられるらしいけど、あまりよくわからなかった。
