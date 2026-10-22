// merge_cost：连续文件合并
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 merge_cost.md
// 复杂度：时间 O(n³)，空间 O(n²)

#include <algorithm>
#include <iostream>
#include <vector>
int main() {
    int n;if(!(std::cin>>n))return 0;
    std::vector<long long> prefix(n+1,0);
    for(int i=1;i<=n;++i){long long x;std::cin>>x;prefix[i]=prefix[i-1]+x;}
    std::vector<std::vector<long long>>dp(n,std::vector<long long>(n,0));
    for(int length=2;length<=n;++length) {
        for(int l=0;l+length<=n;++l) {
            int r=l+length-1;
            dp[l][r]=(1LL<<62);
            for(int k=l;k<r;++k) {
                long long cost=dp[l][k]+dp[k+1][r]+prefix[r+1]-prefix[l];
                dp[l][r]=std::min(dp[l][r],cost);
            }
            // 长度为 1 时无须合并，初始化的 0 就是正确边界。
        }
    }
    std::cout<<dp[0][n-1]<<'\n';
}
