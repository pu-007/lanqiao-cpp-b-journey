// subsets：装备组合搜索
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 subsets.md
// 复杂度：时间 O(2^n)，递归栈 O(n)（另存输入 O(n)）

#include <functional>
#include <iostream>
#include <vector>
int main() {
    int n; long long target;
    if (!(std::cin >> n >> target)) return 0;
    std::vector<long long> weight(n);
    for (auto& x : weight) std::cin >> x;
    long long answer=0;
    std::function<void(int,long long)> dfs = [&](int index, long long sum) {
        if (sum>target) return; // 只有非负数才能使用这个剪枝。
        if (index==n) {
            if (sum==target) ++answer;
            return;
        }
        dfs(index+1,sum);               // 不选当前物品。
        dfs(index+1,sum+weight[index]); // 选当前物品。
        // 状态按值传递，不需撤销；若修改共享路径 vector，就必须 pop_back。
    };
    dfs(0,0);
    std::cout << answer << '\n';
}
