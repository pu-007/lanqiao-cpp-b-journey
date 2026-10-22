// real_delete_edge：删边问题
// 来源：2023 国赛 C/C++ B 组 F；https://www.luogu.com.cn/problem/P9424
// 题面、范围、样例和训练步骤见同目录 real_delete_edge.md
// 复杂度：时间 O(n+m)，空间 O(n+m)

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
int main() {
    std::ios::sync_with_stdio(false);std::cin.tie(nullptr);
    int n,m;if(!(std::cin>>n>>m))return 0;
    std::vector<long long>sum(n+1);long long total=0;
    for(int i=1;i<=n;++i){std::cin>>sum[i];total+=sum[i];}
    std::vector<std::vector<std::pair<int,int>>>g(n+1);
    for(int id=0;id<m;++id){int u,v;std::cin>>u>>v;g[u].push_back({v,id});g[v].push_back({u,id});}
    std::vector<int>tin(n+1,0),low(n+1),parent(n+1,0),edge(n+1,-1);
    std::vector<std::size_t>next(n+1,0);
    std::vector<long long>component_sums,bridge_sums;
    int timer=0;
    for(int root=1;root<=n;++root)if(!tin[root]) {
        std::vector<int>stack={root};tin[root]=low[root]=++timer;
        while(!stack.empty()) {
            int u=stack.back();
            if(next[u]<g[u].size()) {
                auto[v,id]=g[u][next[u]++];
                if(id==edge[u])continue;
                if(!tin[v]) {
                    parent[v]=u;edge[v]=id;tin[v]=low[v]=++timer;stack.push_back(v);
                }else low[u]=std::min(low[u],tin[v]);
            }else {
                stack.pop_back();
                if(parent[u]) {
                    int p=parent[u];
                    if(low[u]>tin[p])bridge_sums.push_back(sum[u]);
                    low[p]=std::min(low[p],low[u]);sum[p]+=sum[u];
                }
            }
        }
        component_sums.push_back(sum[root]);
    }
    long long answer=(1LL<<62);
    if(component_sums.size()==1) {
        for(long long s:bridge_sums)answer=std::min(answer,std::llabs(total-2*s));
    }else if(component_sums.size()==2 && static_cast<int>(bridge_sums.size())<m) {
        // 至少有一条非桥可删；删除后仍保持两个连通分量。
        answer=std::llabs(component_sums[0]-component_sums[1]);
    }
    std::cout<<(answer==(1LL<<62)?-1:answer)<<'\n';
}
