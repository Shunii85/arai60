# step1

linked-list-cycle1と前提は変わらない様子。

今度は、循環が始まる場所を返す。場所とは？
解答の仕方がわからないと一瞬思ったけど、LeetCodeの`detectCycle`メソッドの帰り値でそのポインタを返せばいいと判明。

# step2

特に修正するところはないなと思った。

同じような解き方をされている方

https://github.com/Ryotaro25/leetcode_first60/pull/2/changes#diff-f76415a86863cb3dc18eb0d159540652884d086e1c7fa50829a83d26a611c845

# step3

特に何もなく、3回書いた。前回の問題とほぼ同じだったのでスルスルとかけた。

そういえばなんとなく書いていたnullptrが何なのか気になった。NULLは0と定義されるけど、それは本当にポインタとして使われないの？ではnullptrは何？
任意の型への変換というのがキーワードらしい。

https://cpprefjp.github.io/lang/cpp11/nullptr.html

```c++
template <class T>
void f(T p);
```

> この関数にヌルポインタ値を渡したい場合、0やNULLマクロを使用すると、テンプレートの型推論によって整数型と見なされてしまっていた。これによって、引数をほかの関数に転送するプログラムを書く際に型が合わない問題が発生した。

nullptr自体が何なのかはまだわかっていない。これもゼロを指すのか？
