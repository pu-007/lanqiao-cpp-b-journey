// maze：迷宫导航器
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 maze.md
// 复杂度：时间 O(hw)，空间 O(hw)

#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>
int main() {
    int h,w; if (!(std::cin >> h >> w)) return 0;
    std::vector<std::string> grid(h);
    for (auto& row : grid) std::cin >> row;
    if (grid[0][0]=='#' || grid[h-1][w-1]=='#') {
        std::cout << -1 << '\n'; return 0;
    }
    std::vector<std::vector<int>> dist(h, std::vector<int>(w,-1));
    std::queue<std::pair<int,int>> frontier;
    frontier.push({0,0}); dist[0][0]=0;
    const int dx[]={1,0,0,-1}, dy[]={0,-1,1,0}; // D,L,R,U。
    while (!frontier.empty()) {
        auto current=frontier.front(); frontier.pop();
        int x=current.first, y=current.second;
        for (int direction=0; direction<4; ++direction) {
            int nx=x+dx[direction], ny=y+dy[direction];
            if (nx<0 || nx>=h || ny<0 || ny>=w) continue;
            if (grid[nx][ny]=='#' || dist[nx][ny]!=-1) continue;
            dist[nx][ny]=dist[x][y]+1; // 入队就标记，不能等出队。
            frontier.push({nx,ny});
        }
    }
    std::cout << dist[h-1][w-1] << '\n';
}
