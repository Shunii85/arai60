# step1
stackに突っ込んで取り出せばいい話、というのはわかったので問題としては単純。
この、突っ込んで取り出せば順番が変わるというのは便利だなと思った。

コードを書いていて注意しなければいけないなと思ったのは、最後のノードについて。最後のノードのつながった先は
直前のノードであるのだから、これはnullptrにするべきだ。
stackに突っ込む際にnextをすべてnullptrにリセットしておいてもいいだろう(これは試してみたけど、めんどくさい。前に進めなくなる)。順番はstackが決めてくれている。
今回は単純に最後のノードのnextのみを更新した。

ひとつ考えたいのは、dummyの呪縛から逃れたいということ。番兵という言葉自体はdiscordで散見されるけれど、
dummyという変数名は実際使われているのだろうか。何かいいものはないだろうか。
前に、managerを付けてみたり、LinkedListであればholderなどを考えたことはあるがしっくりこない。

時間/領域計算量ともにO(N)となる。

---

解き方について、stackを使わなくてよければ、領域計算量は小さくできそう。
step1-2.cppで考えてみよう。

おそらくこれは簡単な話で、目的地を反転させるという簡単な作業だ。
これに必要なのは、直前のノードの情報。

なんだかこの方法では、進むための道が確保されなくなって、うまくいかなくなった。道を反転させれば反対側の道はなくなってしまう。
それがやっかい。

---

> 進むための道が確保されなくなって
普通に、道を記憶しておけばいいだけの話だったので、実装できそう。

step1-2.cpp

これについても、3回繰り返して書いておいた。簡潔でわかりやすかった。

# step2
> stackに突っ込む際にnextをすべてnullptrにリセットしておいてもいいだろう([step1より](#step1))
これで書き直してみた。少し行数は増えるが、いいかもしれない。

最初、こうやって書き直していた。

```
class Solution {
 public:
  ListNode* reverseList(ListNode* head) {
    std::stack<ListNode*> warehouse;
    ListNode* node = head;
    ListNode* cutted = nullptr;
    ListNode* dummy = new ListNode(-1);
    while (node) {
      cutted = node;
      node = node->next;
      cutted->next = nullptr;
      warehouse.push(cutted);
    }
    node = dummy;
    while (!warehouse.empty()) {
      node->next = warehouse.top();
      warehouse.pop();
      node = node->next;
    }
    return dummy->next;
  }
};
```

# step3

でも、このcuttedが何かややこしくて素直には感じなかった。まずnextに行き先を保存しておくのがわかりやすかった。

```c++
while (node) {
  next = node->next;
  node->next = nullptr;
  warehouse.push(node);
  node = next;
}
```
s
※一部抜粋

# step4

再帰を使って書いてみた。

step4-1.cppでは、ひっくり返した頭と尻尾を両方返すようにした。

step4-2.cppでは、尻尾は省略できるのでそれバージョン。

