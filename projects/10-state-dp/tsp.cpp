// tsp：小型配送路线
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 tsp.md
// 复杂度：时间 O(n²2^n)，空间 O(n2^n)，n=17 时 DP 约 17 MiB

#include <algorithm>
#include <iostream>
#include <vector>
int main() {
    int n;if(!(std::cin>>n))return 0;
    std::vector<std::vector<long long>>cost(n,std::vector<long long>(n));
    for(auto&row:cost)for(auto&x:row)std::cin>>x;
    const int total=1<<n;const long long INF=(1LL<<62);
    // 连续内存减少 vector<vector<...>> 的大量小分配。
    std::vector<long long>dp(static_cast<std::size_t>(total)*n,INF);
    auto at=[&](int mask,int u)->long long&{return dp[static_cast<std::size_t>(mask)*n+u];};
    at(1,0)=0;
    for(int mask=1;mask<total;++mask) {
        if(!(mask&1))continue; // 必须包含起点 0。
        for(int u=0;u<n;++u) {
            if(at(mask,u)==INF)continue;
            for(int v=0;v<n;++v)if(!(mask&(1<<v))) {
                int next=mask|(1<<v);
                at(next,v)=std::min(at(next,v),at(mask,u)+cost[u][v]);
            }
        }
    }
    long long answer=INF;
    for(int u=0;u<n;++u) answer=std::min(answer,at(total-1,u)+cost[u][0]);
    std::cout<<answer<<'\n';
}
