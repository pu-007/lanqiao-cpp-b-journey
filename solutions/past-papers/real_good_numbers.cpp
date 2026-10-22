// real_good_numbers：好数
// 来源：2024 省赛 C/C++ B 组；https://www.luogu.com.cn/problem/P10424
// 题面、范围、样例和训练步骤见同目录 real_good_numbers.md
// 复杂度：时间 O(N log N)，空间 O(1)

#include <iostream>
bool good(int value) {
    int position=1;
    while(value>0) {
        int digit=value%10;
        if(digit%2!=position%2)return false;
        value/=10;++position;
    }
    return true;
}
int main() {
    int n;if(!(std::cin>>n))return 0;
    int count=0;
    for(int x=1;x<=n;++x)if(good(x))++count;
    std::cout<<count<<'\n';
}
