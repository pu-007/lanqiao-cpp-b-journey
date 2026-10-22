// real_submatrix：统计子矩阵
// 来源：2022 省赛 C/C++ B 组；https://www.luogu.com.cn/problem/P8783
// 题面、范围、样例和训练步骤见同目录 real_submatrix.md
// 复杂度：时间 O(min(N,M)²·max(N,M))，空间 O(NM)

#include <algorithm>
#include <iostream>
#include <vector>
int main() {
    int n,m;long long limit;if(!(std::cin>>n>>m>>limit))return 0;
    std::vector<std::vector<int>>a(n,std::vector<int>(m));
    for(auto&row:a)for(auto&x:row)std::cin>>x;
    if(n>m) { // 转置不改变矩形答案，使平方枚举维度尽量小。
        std::vector<std::vector<int>>b(m,std::vector<int>(n));
        for(int i=0;i<n;++i)for(int j=0;j<m;++j)b[j][i]=a[i][j];
        a.swap(b);std::swap(n,m);
    }
    long long answer=0;
    for(int top=0;top<n;++top) {
        std::vector<long long>column(m,0);
        for(int bottom=top;bottom<n;++bottom) {
            for(int j=0;j<m;++j)column[j]+=a[bottom][j];
            int left=0;long long sum=0;
            for(int right=0;right<m;++right) {
                sum+=column[right];
                while(left<=right&&sum>limit)sum-=column[left++];
                answer+=right-left+1;
            }
        }
    }
    std::cout<<answer<<'\n';
}
