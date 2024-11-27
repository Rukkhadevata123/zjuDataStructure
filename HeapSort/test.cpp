#include <iostream>
#include <vector>
#include "HeapSort.h" 

int main() {
    long long size = 1e7 + 5;

    // 测试不同排列组合
    std::vector<std::pair<Order, Repeat>> combinations = {
        {Order::ASC, Repeat::NO},
        {Order::ASC, Repeat::YES},
        {Order::DESC, Repeat::NO},
        {Order::DESC, Repeat::YES},
        {Order::RANDOM, Repeat::NO},
        {Order::RANDOM, Repeat::YES}
    };

    for (const auto& combination : combinations) {
        Order order = combination.first;
        Repeat repeat = combination.second;

        std::cout << "Testing with Order: " 
                  << (order == Order::ASC ? "ASC" : (order == Order::DESC ? "DESC" : "RANDOM"))
                  << ", Repeat: " 
                  << (repeat == Repeat::NO ? "NO" : "YES") 
                  << std::endl;

        std::cout << "Test integer:" << '\n';
        std::vector<int> data_int = generate_data_int(size, order, repeat);
        compare(data_int);

        std::cout << "Test double:" << '\n';
        std::vector<double> data_double = generate_data_double(size, order, repeat);
        compare(data_double);
    }

    return 0;
}