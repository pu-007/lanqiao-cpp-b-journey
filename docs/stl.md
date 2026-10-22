# STL：先学够用的部分

建议学习顺序：vector/string → sort/pair → map/set → stack/queue → priority_queue/deque → lower_bound。每个 API 当天都在项目里用一次。

## 从熟悉的语言迁移

| 开发中的习惯 | C++ 写法 | 必须记住 |
| --- | --- | --- |
| 动态列表 | `vector<int>` | 下标越界不会自动给友好异常；`at()` 才检查 |
| 字符串 | `string` | `size()` 是无符号类型；汉字 UTF-8 字节不等于字符 |
| 字典 | `map<K,V>` / `unordered_map<K,V>` | 前者有序 O(log n)，后者平均 O(1)、最坏 O(n) |
| 去重集合 | `set<T>` / `unordered_set<T>` | `set` 按比较器排序，不按插入顺序 |
| 二元记录 | `pair<A,B>` | 默认先比 first，再比 second |
| 优先级任务 | `priority_queue<T>` | 默认最大堆；最小堆要换比较器 |

`auto` 是编译期推导类型，不是动态类型。`const auto&` 表示只读引用，避免复制；`auto` 是副本，改它不会改容器中的元素。

## vector 和 string

```cpp
#include <vector>
#include <string>
#include <algorithm>
std::vector<int> a(5, 0); // size=5，有五个零
std::vector<int> b;
b.reserve(5);            // 仅预留容量；此时 b.size() 仍是 0，不能 b[0]=1
b.push_back(3);
b.push_back(1);
for (int& x : b) x *= 2; // 引用会修改原元素
std::sort(b.begin(), b.end());
std::string s = "abc";
s += 'd';
std::reverse(s.begin(), s.end());
```

常用复杂度：vector 按下标 O(1)，push_back 均摊 O(1)，中间插入/删除 O(n)。不要对 20 万次队首弹出使用 `vector.erase(begin())`，那会退化到 O(n²)。扩容可能使迭代器、指针、引用失效。

连续读 `cin >> n` 再读整行时，要处理残留换行。可用 `getline(cin >> ws, s)` 跳过前导空白，但如果空行有意义则不能这样用；显式忽略上次输入行尾即可。

## 排序、去重与二分

```cpp
#include <algorithm>
#include <vector>
std::vector<int> a = {3, 1, 3, 2};
std::sort(a.begin(), a.end()); // [1,2,3,3]
a.erase(std::unique(a.begin(), a.end()), a.end()); // [1,2,3]
auto it = std::lower_bound(a.begin(), a.end(), 2); // 第一个 >=2
if (it != a.end()) { int value = *it; (void)value; }
auto upper = std::upper_bound(a.begin(), a.end(), 2); // 第一个 >2
auto count = upper - it; // 重复值数量（必须在去重前算才有原来的含义）
```

所有范围是 **[begin,end)**；end 指向末尾之后，不可解引用。二分前必须满足相应排序/分区条件。对 vector 的 lower_bound 为 O(log n)；对 set 应使用 `s.lower_bound(x)`，通用算法在非随机访问迭代器上可能有线性移动成本。

比较器写 `a.score > b.score`，不写 `>=`。元素等于自己时比较器必须返回 false。排序后才用 unique 去重，unique 只把不重复段挤到前面并返回新末尾，不会缩短容器。

## map 和 set

```cpp
#include <map>
#include <set>
#include <string>
std::map<std::string, int> count;
++count["bfs"];                   // 缺失时插入 0 后递增
auto it = count.find("dp");
bool exists = it != count.end();   // 只查询，不新增
std::set<int> seen;
bool inserted = seen.insert(7).second;
seen.erase(7);
```

map/set 的查询、插入、按键删除通常是 O(log n)。不要用 `if (count[key])` 判断存在性而忘了它会修改映射。需要保留重复值时使用 multiset；`erase(value)` 删除所有相等元素，`erase(iterator)` 只删除那个位置。

## 栈、队列、堆、双端队列

```cpp
#include <stack>
#include <queue>
#include <deque>
#include <functional>
#include <vector>
std::stack<int> st; st.push(1);
if (!st.empty()) { int x = st.top(); st.pop(); (void)x; }
std::queue<int> q; q.push(1);
if (!q.empty()) { int x = q.front(); q.pop(); (void)x; }
std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
min_heap.push(4); min_heap.push(2); // top() 是 2
std::deque<int> dq; dq.push_back(1); dq.push_front(2);
```

stack/queue 的 push/pop 为 O(1)；堆 push/pop 为 O(log n)，top 为 O(1)。pop 不返回元素，读取和删除分成两步。任何 top/front/back 都先保证非空。

## 其他常用工具

`<numeric>` 中的 `accumulate(a.begin(),a.end(),0LL)` 用 long long 累加；传 0 会用 int 累加。`iota` 生成连续值，C++17 的 `gcd` 求最大公约数。`min/max/swap/reverse` 来自标准头文件；`memset` 是按字节填充，不能用它把 int 数组设成一般整数值。

浮点 pow 不适合精确整数幂；整数平方可写 `1LL*x*x`，先提升类型再相乘。`1<<n` 的类型默认 int，n 很大时不安全；即使换 `1LL<<n`，仍必须保证移位宽度合法。

本地资料可查 [Hello 算法](https://github.com/krahets/hello-algo) 和 [OI Wiki](https://github.com/OI-wiki/OI-wiki) 的相关章节；先用本仓库项目练习，再把百科当查询工具。
