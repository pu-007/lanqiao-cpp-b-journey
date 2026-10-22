// knapsack：训练收益规划
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 knapsack.md
// 复杂度：时间 O(nB)，空间 O(B)

#include <algorithm>
#include <iostream>
#include <vector>
int main() {
    int n,budget; if(!(std::cin>>n>>budget)) return 0;
    std::vector<long long> dp(budget+1,0); // 不要求用完预算，空方案始终合法。
    for(int i=0;i<n;++i) {
        int cost; long long value; std::cin>>cost>>value;
        // 倒序让 dp[c-cost] 还没有使用当前物品。
        for(int c=budget;c>=cost;--c)
            dp[c]=std::max(dp[c],dp[c-cost]+value);
    }
    std::cout<<dp[budget]<<'\n';
}
