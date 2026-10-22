// real_weights：砝码称重
// 来源：2021 第一轮省赛 A/B 共享题；https://www.luogu.com.cn/problem/P8742
// 题面、范围、样例和训练步骤见同目录 real_weights.md
// 复杂度：时间 O(nS)，空间 O(S)

#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>
int main() {
    int n;if(!(std::cin>>n))return 0;
    std::vector<int>w(n);for(auto&x:w)std::cin>>x;
    int total=std::accumulate(w.begin(),w.end(),0);
    std::vector<char>dp(total+1,false);dp[0]=true;
    int processed_sum=0;
    for(int x:w) {
        auto next=dp; // 不使用当前砝码的状态直接保留。
        for(int d=0;d<=processed_sum;++d)if(dp[d]) {
            next[d+x]=true;
            next[std::abs(d-x)]=true;
        }
        dp.swap(next);processed_sum+=x;
    }
    int answer=0;
    for(int d=1;d<=total;++d)answer+=dp[d];
    std::cout<<answer<<'\n';
}
