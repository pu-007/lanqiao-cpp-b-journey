// 原创基础练习：反转单词；题意见 ../practice.md
#include <iostream>
#include <string>
int main() {
    std::string s; std::cin >> s;
    for (int i=static_cast<int>(s.size())-1;i>=0;--i)
        std::cout << s[i];
    std::cout << '\n';
}
