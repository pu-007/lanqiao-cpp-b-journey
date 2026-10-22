// bridges：网络关键边审计
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 bridges.md
// 复杂度：时间 O(n+m)，空间 O(n+m)

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
int main() {
    int n,m;if(!(std::cin>>n>>m))return 0;
    std::vector<std::vector<std::pair<int,int>>>g(n+1);
    for(int id=0;id<m;++id){int u,v;std::cin>>u>>v;g[u].push_back({v,id});g[v].push_back({u,id});}
    std::vector<int>tin(n+1,0),low(n+1),parent(n+1,0),parent_edge(n+1,-1);
    std::vector<std::size_t>next_edge(n+1,0);
    int timer=0,answer=0;
    for(int root=1;root<=n;++root) {
        if(tin[root])continue;
        tin[root]=low[root]=++timer;
        std::vector<int>stack={root};
        while(!stack.empty()) {
            int u=stack.back();
            if(next_edge[u]<g[u].size()) {
                auto [v,id]=g[u][next_edge[u]++];
                if(id==parent_edge[u])continue; // 只跳过来的那一条边。
                if(!tin[v]) {
                    parent[v]=u;parent_edge[v]=id;
                    tin[v]=low[v]=++timer;stack.push_back(v);
                } else low[u]=std::min(low[u],tin[v]);
            } else {
                stack.pop_back(); // 模拟递归返回：子树已完成。
                if(parent[u]) {
                    int p=parent[u];
                    if(low[u]>tin[p])++answer;
                    low[p]=std::min(low[p],low[u]);
                }
            }
        }
    }
    std::cout<<answer<<'\n';
}
