// 原创基础练习：统计合格成绩；题意见 ../practice.md
#include <iostream>
int main() {
    int n; std::cin >> n;
    int count=0;
    for (int i=0;i<n;++i) {
        int score; std::cin >> score;
        if (score>=60) ++count; // 边界 60 包含在内。
    }
    std::cout << count << '\n';
}
