// digit_filter：数字筛选器
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 digit_filter.md
// 复杂度：时间 O(N log N)，空间 O(1)

#include <iostream>
bool contains_two(int value) { // 按值传参，局部修改不会影响调用者。
    while (value > 0) {
        if (value % 10 == 2) return true; // 找到一位就够了。
        value /= 10;                    // 整数除法会丢掉末位。
    }
    return false;
}
int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    int count = 0;
    for (int value = 1; value <= n; ++value) {
        if (contains_two(value)) ++count;
    }
    std::cout << count << '\n';
}
