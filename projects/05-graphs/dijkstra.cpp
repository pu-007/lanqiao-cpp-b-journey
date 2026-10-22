// dijkstra：校园快递最短路
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 dijkstra.md
// 复杂度：时间 O((n+m) log(n+m))，空间 O(n+m)

#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);
    int n,m,s; if (!(std::cin >> n >> m >> s)) return 0;
    std::vector<std::vector<std::pair<int,long long>>> graph(n+1);
    for(int i=0;i<m;++i) {
        int u,v; long long w; std::cin >> u >> v >> w;
        graph[u].push_back({v,w}); // 有向边；无向题必须再加反向边。
    }
    const long long INF=(1LL<<62); // 大于最大路径，并留出加法余量。
    std::vector<long long> distance(n+1,INF);
    using State=std::pair<long long,int>; // (距离,点)，堆先按距离排序。
    std::priority_queue<State,std::vector<State>,std::greater<State>> heap;
    distance[s]=0; heap.push({0,s});
    while(!heap.empty()) {
        auto [d,u]=heap.top(); heap.pop(); // C++17 结构化绑定。
        if(d!=distance[u]) continue;      // 旧距离已被更优距离取代。
        for(auto [v,w]:graph[u]) {
            if(distance[v]>d+w) {
                distance[v]=d+w;
                heap.push({distance[v],v});
            }
        }
    }
    for(int v=1;v<=n;++v) {
        if(v>1) std::cout << ' ';
        std::cout << (distance[v]==INF?-1:distance[v]);
    }
    std::cout << '\n';
}
