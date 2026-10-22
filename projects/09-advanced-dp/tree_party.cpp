// tree_party：团队代表选择
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 tree_party.md
// 复杂度：时间 O(n)，空间 O(n)

#include <algorithm>
#include <iostream>
#include <vector>
int main() {
    int n;if(!(std::cin>>n))return 0;
    std::vector<long long> take(n+1),skip(n+1,0);
    for(int i=1;i<=n;++i)std::cin>>take[i];
    std::vector<std::vector<int>>graph(n+1);
    for(int i=1;i<n;++i){int u,v;std::cin>>u>>v;graph[u].push_back(v);graph[v].push_back(u);}
    std::vector<int>parent(n+1,0),order={1};
    for(std::size_t i=0;i<order.size();++i) {
        int u=order[i];
        for(int v:graph[u])if(v!=parent[u]) {parent[v]=u;order.push_back(v);}
    }
    // 父亲在 order 中先出现；逆序处理时孩子的 DP 已完成。
    for(int i=n-1;i>0;--i) {
        int u=order[i],p=parent[u];
        take[p]+=skip[u];
        skip[p]+=std::max(take[u],skip[u]);
    }
    std::cout<<std::max(take[1],skip[1])<<'\n';
}
