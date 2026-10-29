# 算法可视化资源：先看懂过程，再自己写

这份清单面向刚开始学习算法的人：先观察少量数据怎样变化，再回到仓库运行代码。每次挑一个问题花 10–20 分钟，计入每周已有的 8–10 小时，不必额外增加一整门课。

核验日期：2026-10-28。以下是公开页面的内容与链接核验；可视化主要依赖浏览器 JavaScript，本次未逐一实际操作全部按钮。网站可能调整界面、账号或服务条件；页面打不开时可用本仓库手动画表替代。

## 先收藏这四个入口

| 资源 | 为什么适合你 | 语言与费用 | 注意 |
| --- | --- | --- | --- |
| [Hello 算法](https://www.hello-algo.com/) | 中文图解、动画和多语言代码，适合第一次理解概念 | 有简体中文；作者说明在线教程开源免费，也有另售纸质书 | 主要是教程配图，不是每一幅图都能自定义输入 |
| [VisuAlgo 中文首页](https://visualgo.net/zh) | 能观察排序、栈、队列、搜索和图算法状态的变化 | 中文页面和英文页面均可公开浏览；部分讲解未完全翻译 | 有独立的训练/测试与账号功能，不假定全部功能无需登录；需要 JavaScript |
| [USF 算法可视化](https://www.cs.usfca.edu/~galles/visualization/Algorithms.html) | 首页按栈、递归、排序、图论、DP 列出很多独立动画 | 英文为主；公开网页可访问 | 具体动画运行需要浏览器脚本；界面比较简洁，不能替代题解 |
| [C++ Tutor](https://pythontutor.com/cpp.html) | 输入你自己的小段 C++，逐步查看变量、调用栈 | 英文为主；页面标明免费 | 代码会发送到网站执行，勿输入密码或私人数据；有运行时间和功能限制，不适合大数据或所有 C++ 特性 |

另外，[OI Wiki](https://oi-wiki.org/) 适合查更详细的竞赛知识和证明，通常不以交互动画为主；遇到概念不熟时先看 Hello 算法，再查它。

## 跟仓库项目一起使用

| 当前主题 | 看什么 | 看完做什么 |
| --- | --- | --- |
| 数组、`vector`、复杂度 | Hello 算法首页的“复杂度”“数组与链表”章节 | 回到 [sum64](../projects/00-basics/sum64.md)，说清循环执行次数和整数范围 |
| 排序与 STL | [VisuAlgo：排序](https://visualgo.net/zh/sorting)；[Hello 算法：二分查找](https://www.hello-algo.com/chapter_searching/binary_search/) | 看 3、1、2 如何排序；自己完成 [ranking](../projects/01-stl/ranking.md) 的比较器 |
| 栈和队列 | [VisuAlgo：链表、栈、队列](https://visualgo.net/zh/list) | 画出 `([])` 每一步的栈，再做 [brackets](../projects/01-stl/brackets.md) |
| 递归与重复子问题 | [VisuAlgo：递归树和动态规划](https://visualgo.net/zh/recursion) | 对 n=4 画搜索树，找出重复状态；完成 [subsets](../projects/04-search/subsets.md) |
| BFS / DFS | [VisuAlgo：图的遍历](https://visualgo.net/zh/dfsbfs)；[USF：BFS](https://www.cs.usfca.edu/~galles/visualization/BFS.html) | 比较同一张图的两种访问顺序；理解队列后做 [maze](../projects/04-search/maze.md) |
| 并查集 | [VisuAlgo：并查集](https://visualgo.net/zh/ufds) | 合并 1–2、2–3、4–5；判断 1 和 3、1 和 4 是否连通，再做 [dsu](../projects/05-graphs/dsu.md) |
| 最短路 | [VisuAlgo：单源最短路](https://visualgo.net/zh/sssp) | 比较 1→2=10 与 1→3=1、3→2=2；做 [dijkstra](../projects/05-graphs/dijkstra.md) |
| 最小生成树 | [VisuAlgo：最小生成树](https://visualgo.net/zh/mst) | 比较 Kruskal 的选边过程与最短路不同的目标；做 [kruskal](../projects/05-graphs/kruskal.md) |
| 背包 DP | [Hello 算法：0-1 背包](https://www.hello-algo.com/chapter_dynamic_programming/knapsack_problem/) | 自己写表格，不抄结论；回到 [knapsack](../projects/06-dp/knapsack.md) 说明倒序原因 |

个别网站对图的编号和邻接顺序有自己的约定。同一张图的 BFS/DFS 访问顺序可以因邻居顺序不同而不同；检查是否满足算法规则，不要只看序列是否一模一样。

## 第一次使用 VisuAlgo：3 分钟看懂队列

1. 打开[链表、栈、队列](https://visualgo.net/zh/list)，选择顶部的“队列”。如果停留在电子讲座，切换到“探索模式”；其排序页面说明 `Esc` 可切换模式，其他页面如界面更新请使用页面上的模式选项。
2. 插入 3、7、9，观察三者排列。删除一次，再观察哪个元素先离开。
3. 暂停动画，猜下一次删除会得到什么，再单步前进。先进入的 3 先离开，随后才是 7；这就是 FIFO。
4. 打开 [maze.cpp](../projects/04-search/maze.cpp)，找 `frontier.push` 与 `frontier.pop`。解释为什么 BFS 要按发现顺序处理格子。

网站的颜色和节点布局是演示手段；要把它翻译成自己的文字：“队列里有哪些待处理点？我在哪里记录已经访问过？”

## 用 C++ Tutor 观察递归和作用域

打开 [C++ Tutor](https://pythontutor.com/cpp.html)，把下面的**非敏感小程序**粘进去，点击 `Visualize Execution`，再用前进/后退按钮观察 `sum_to` 的调用和返回：

```cpp
#include <iostream>
int sum_to(int n) {
    if (n == 0) return 0;
    return n + sum_to(n - 1);
}
int main() {
    std::cout << sum_to(3) << '\n';
}
```

暂停在 `sum_to(0)` 时，试着回答：栈上有哪几次调用？返回后每一层的 `n` 是多少？最后输出应为 6。然后回到 [subsets.cpp](../projects/04-search/subsets.cpp)，对比它每层如何决定“选/不选”。网站若不支持某种语法或标准库特性，可先缩小程序；正式题目仍以本地编译器与比赛环境为准。

## 真正看懂的三步验收

1. **预测**：暂停动画，先猜下一步会访问哪个点或修改哪个变量。
2. **解释**：不看动画，画出一组 3–5 个元素的小例子；指出边界条件与算法前提。
3. **实现**：关闭网页，自己写对应仓库练习；用提供的本地测试和自己设计的反例检查。

动画只展示有限输入，不能证明算法适用于所有数据。每看完一个动画，至少回答“这个算法在哪种条件下不适用”，例如带负边的图不能直接使用 Dijkstra。
