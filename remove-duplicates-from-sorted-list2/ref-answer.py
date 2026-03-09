# 参考にしたdiscord上のodaさんのコード
# 2行だけ、コメントアウトしていると思うが、その行は必要ない。

dummy = ListNode()
dymmy.next = head
previous = dummy  # 本線のお尻
is_deleting = False
deleting_number = 0
while current:
  # 昨日の続きで外す。
  if is_deleting and deleting_number == current.val:
    previous.next = current.next
    # previous = current 
    current = current.next
    continue  # 今日の仕事終わり。引き継ぎ内容も変更しなくて完璧。
  # ホワイトボード消す
  is_deleting = False
  # 次の車両との関係で消すかを考える
  if not current.next:
    previous = current
    current = current.next
    continue  # なかったら仕事終わり。お家に帰る。
  if current.val != current.next.val
    # 1台、本線に送ってお家に帰る。
    previous = current
    current = current.next
    continue
  # あー、外す対象見つかっちゃった。とりあえず引き継ぎ資料作る。
  is_deleting = True
  deleting_number = current.val
  # 1台外す。
  previous.next = current.next
  # previous = current
  current = current.next