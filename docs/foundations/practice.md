# 12 道基础练习：先自己做，再看思路

这些是原创教学题，按从容易到稍难排列，和后续蓝桥杯真题不同。每题都有独立可运行的 C++17 文件；先把题目写在 `practice/`，再对照参考实现。它们不在原先 `lab.py` 的题目列表里，用下方 g++ 命令运行。

每题建议：先用纸算样例 → 独立写 15–30 分钟 → 看提示 → 再看参考代码 → 自己构造边界。时间 O(n) 表示数据翻倍时，操作次数大致翻倍。

```bash
g++ -std=c++17 -O2 docs/foundations/worked-code/01_max.cpp -o /tmp/foundation-demo
/tmp/foundation-demo
```

Windows PowerShell 可改为 `g++ -std=c++17 -O2 docs/foundations/worked-code/01_max.cpp -o foundation-demo.exe`，然后运行 `.\foundation-demo.exe`。

## 01 · 找到最高温度

输入 n（1≤n≤100000）及 n 个整数（-10^9≤x≤10^9），输出其中最大值。

输入：
```text
5
-4 -8 -1 -9 -3
```
输出：
```text
-1
```

另测边界输入：`1 / -42`（`/` 表示换行），输出 `-42`。

<details><summary>先看提示</summary>

遍历一遍，边读边比较。想一想全是负数时初值能不能设为 0。

</details>

<details><summary>参考思路</summary>

用第一个数初始化最大值；每看一个数，就把它与当前最大值比较。看完前 i 个数后，best 就是它们之中的最大值。时间 O(n)，额外空间 O(1)。

</details>

[打开完整参考代码](worked-code/01_max.cpp)

---

## 02 · 统计合格成绩

输入 n（1≤n≤100000）和 n 个整数成绩（0..100），输出大于等于 60 的数量。

输入：
```text
6
60 59 100 0 60 80
```
输出：
```text
4
```

另测边界输入：`1 / 59`（`/` 表示换行），输出 `0`。

<details><summary>先看提示</summary>

先为每个成绩写一个真假判断；条件成立才让计数器加 1。

</details>

<details><summary>参考思路</summary>

读到的成绩如果达到 60 分，就增加 1；60 分本身也要算。时间 O(n)，额外空间 O(1)。

</details>

[打开完整参考代码](worked-code/02_count.cpp)

---

## 03 · 数位之和

输入一个整数 x（0≤x≤10^18），输出十进制各位数字之和。

输入：
```text
2026
```
输出：
```text
10
```

另测边界输入：`0`（`/` 表示换行），输出 `0`。

<details><summary>先看提示</summary>

x % 10 取末位，x / 10 去掉末位。画出 2026→202→20→2→0。

</details>

<details><summary>参考思路</summary>

依次取出末位并累加，直到数字为 0。原数为 0 时循环不执行，初值 0 就是答案。时间 O(log(x+1))，空间 O(1)。

</details>

[打开完整参考代码](worked-code/03_digit_sum.cpp)

---

## 04 · 反转单词

输入一个不含空格的非空 ASCII 单词，长度不超过 100000，输出逆序后的单词。

输入：
```text
bridge
```
输出：
```text
egdirb
```

另测边界输入：`x`（`/` 表示换行），输出 `x`。

<details><summary>先看提示</summary>

可以从末尾往开头输出，也可以调用 reverse。

</details>

<details><summary>参考思路</summary>

下标从 size-1 递减到 0，按顺序输出每个字符。强制转成 int 后再减，避免无符号数从 0 继续减而绕回。时间 O(n)，空间 O(n) 保存输入。

</details>

[打开完整参考代码](worked-code/04_reverse.cpp)

---

## 05 · 第一次出现的位置

输入 n 和 target（1≤n≤100000，数值均为 -10^9..10^9），再输入 n 个数。输出 target 第一次出现的下标，使用从 1 开始的编号；不存在输出 -1。

输入：
```text
5 7
2 7 4 7 1
```
输出：
```text
2
```

另测边界输入：`3 5 / 1 2 3`（`/` 表示换行），输出 `-1`。

<details><summary>先看提示</summary>

从左向右寻找，第一次匹配就记下位置。后面的重复值不能覆盖第一次的位置。

</details>

<details><summary>参考思路</summary>

答案初始化为 -1。依次读取，在第一次相等时保存编号；继续读完输入但不再修改答案。时间 O(n)，额外空间 O(1)。

</details>

[打开完整参考代码](worked-code/05_find.cpp)

---

## 06 · 统计不同数字

输入 n（1≤n≤100000）和 n 个 -10^9..10^9 的整数，输出不同数字的个数。

输入：
```text
7
3 1 3 2 1 1 5
```
输出：
```text
4
```

另测边界输入：`4 / 8 8 8 8`（`/` 表示换行），输出 `1`。

<details><summary>先看提示</summary>

排序后，相同的数字挨在一起，数一数有几段。

</details>

<details><summary>参考思路</summary>

从小到大排序；每当当前位置是开头，或者与前一个值不同，就发现一个新数。时间 O(n log n)，空间 O(n)。

</details>

[打开完整参考代码](worked-code/06_distinct.cpp)

---

## 07 · 一次预处理，多次查询

输入 n q（1≤n,q≤100000），接着 n 个整数（绝对值≤10^9），之后 q 行 l r（1≤l≤r≤n）。每行输出第 l 到 r 个数的和。

输入：
```text
5 3
2 1 4 -2 3
1 3
2 5
4 4
```
输出：
```text
7
6
-2
```

另测边界输入：`1 1 / 1000000000 / 1 1`（`/` 表示换行），输出 `1000000000`。

<details><summary>先看提示</summary>

先算从第 1 个到第 i 个的总和。区间 [l,r] 可以用两个这样的总和相减。

</details>

<details><summary>参考思路</summary>

令 p[0]=0，p[i]=p[i-1]+a[i]。例如 [2,5] 的和是 p[5]-p[1]=8-2=6。预处理 O(n)，每次查询 O(1)，空间 O(n)。

</details>

[打开完整参考代码](worked-code/07_prefix.cpp)

---

## 08 · 有序数组中找第一次

输入 n x（1≤n≤100000），再输入非递减的 n 个整数（绝对值≤10^9）。输出第一个大于等于 x 的数的 1 开始下标；如果不存在，输出 -1。

输入：
```text
6 4
1 2 4 4 7 9
```
输出：
```text
3
```

另测边界输入：`3 8 / 1 2 3`（`/` 表示换行），输出 `-1`。

<details><summary>先看提示</summary>

数组按条件自然分成 <x 和 ≥x 两段，找后半段第一个位置。

</details>

<details><summary>参考思路</summary>

使用 lower_bound；它返回首个 ≥x 的迭代器，找不到返回 end。注意空的后半段不能解引用 end。时间 O(log n) 查询，空间 O(n) 保存数组。

</details>

[打开完整参考代码](worked-code/08_lower_bound.cpp)

---

## 09 · 最大公约数

输入两个正整数 a b（1≤a,b≤10^18），输出它们的最大公约数。

输入：
```text
48 18
```
输出：
```text
6
```

另测边界输入：`7 7`（`/` 表示换行），输出 `7`。

<details><summary>先看提示</summary>

48÷18 余 12；18÷12 余 6；12÷6 余 0。

</details>

<details><summary>参考思路</summary>

a、b 的公约数与 b、a%b 的公约数相同。不断替换，直到 b=0，此时 a 即答案。时间 O(log min(a,b))，空间 O(1)。

</details>

[打开完整参考代码](worked-code/09_gcd.cpp)

---

## 10 · 判断质数

输入整数 n（1≤n≤10^12），输出 YES 表示质数，否则输出 NO。

输入：
```text
49
```
输出：
```text
NO
```

另测边界输入：`2`（`/` 表示换行），输出 `YES`。

<details><summary>先看提示</summary>

如果 n=a×b，一定有至少一个因子不超过 √n。

</details>

<details><summary>参考思路</summary>

从 2 试到 √n；发现因子就不是质数。1 不是质数。写 d≤n/d 可避免 d*d 在其他范围下溢出。时间 O(√n)，空间 O(1)。

</details>

[打开完整参考代码](worked-code/10_prime.cpp)

---

## 11 · 连续子数组的目标和

输入 n k（1≤n≤2000，-10^9≤k≤10^9），接着 n 个 -10^9..10^9 的整数，输出和恰好为 k 的非空连续子数组数量。

输入：
```text
4 3
1 2 1 2
```
输出：
```text
3
```

另测边界输入：`3 0 / 0 0 0`（`/` 表示换行），输出 `6`。

<details><summary>先看提示</summary>

枚举左端点，再逐个延伸右端点并维护当前和；无需每次从头累加。

</details>

<details><summary>参考思路</summary>

固定左端点 l，从 l 开始逐项加到右端点 r。每次和等于 k 就加 1。允许负数，所以不能因为 sum>k 就提前停止。时间 O(n²)，空间 O(n)。

</details>

[打开完整参考代码](worked-code/11_subarray.cpp)

---

## 12 · 爬楼梯的方案数

输入 n（0≤n≤100000），每次可以爬 1 级或 2 级。输出到达第 n 级的不同方案数，对 1000000007 取模。把不动作为到达第 0 级的一种方案。

输入：
```text
4
```
输出：
```text
5
```

另测边界输入：`0`（`/` 表示换行），输出 `1`。

<details><summary>先看提示</summary>

到第 i 级的最后一步只可能来自第 i-1 级或第 i-2 级。先列 0、1、2、3 级的答案。

</details>

<details><summary>参考思路</summary>

定义 dp[i] 为到第 i 级的方案数，dp[0]=1、dp[1]=1；i≥2 时 dp[i]=dp[i-1]+dp[i-2]。只保留前两项即可。时间 O(n)，空间 O(1)。

</details>

[打开完整参考代码](worked-code/12_stairs.cpp)

---
