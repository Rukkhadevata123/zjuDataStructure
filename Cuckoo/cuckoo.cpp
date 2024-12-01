#include "cuckoo.h"
#include <cmath>

// 辅助函数：生成素数
auto nextPrime(int n) -> int {
    if (n <= 2) return 2;
    if (n % 2 == 0) ++n; // 如果是偶数，先加1变成奇数

    while (true) {
        bool isPrime = true;
        int sqrt_n = static_cast<int>(std::sqrt(n));
        for (int i = 3; i <= sqrt_n; i += 2) {
            if (n % i == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            return n;
        }
        n += 2; // 只检查奇数
    }
}