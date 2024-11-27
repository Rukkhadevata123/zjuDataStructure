#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <random>
#include <unordered_set>

// 计时器类
class Timer {
public:
    Timer() : start_time_point(std::chrono::high_resolution_clock::now()) {}

    ~Timer() {
        stop();
    }

    void stop() {
        auto end_time_point = std::chrono::high_resolution_clock::now();
        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(start_time_point).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_time_point).time_since_epoch().count();

        auto duration = end - start;
        double seconds = duration * 0.000001;

        std::cout << std::fixed << std::setprecision(4) << "Duration: " << seconds << " seconds" << std::endl;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_point;
};

// 大顶堆排序
template <typename T> 
void sift_down(std::vector<T> &heap, int start, int end) {
    int parent = start;         // 父节点下标
    int child = 2 * parent + 1; // 左孩子下标

    while (child <= end) { // 防止越界
        if (child + 1 <= end && heap[child] < heap[child + 1]) {
            child += 1; // 选择较大的孩子
        }

        if (heap[parent] < heap[child]) {
            std::swap(heap[parent], heap[child]); // 调整父子节点
            parent = child;
            child = 2 * parent + 1;
        } else {
            break;
        }
    }
}

// 建堆
template <typename T> 
void heapify(std::vector<T> &heap) {
    int n = heap.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
        sift_down(heap, i, n - 1);
    } // 从最后一个子节点的父节点开始调整
}

// 堆排序
template <typename T> 
void heap_sort(std::vector<T> &arr) {
    Timer timer; // 开始计时
    heapify(arr); // 建堆

    for (int i = arr.size() - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]); // 将堆顶元素与最后一个元素交换
        sift_down(arr, 0, i - 1);  // 调整堆
    }
    // 计时器在析构函数中自动停止并输出时间
}

// 验证排序正确性
template <typename T>
bool check_sort(const std::vector<T> &arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}

// 对标准堆排序计时
template <typename T>
void stl_heap_sort(std::vector<T> &arr) {
    Timer timer; // 开始计时
    std::make_heap(arr.begin(), arr.end());
    std::sort_heap(arr.begin(), arr.end());
    // 计时器在析构函数中自动停止并输出时间
}

// 比较两种排序算法
template <typename T>
void compare(std::vector<T> &arr) {
    std::vector<T> arr1(arr);
    std::vector<T> arr2(arr);

    std::cout << "My Heap Sort: ";
    heap_sort(arr1);

    std::cout << "STL Heap Sort: ";
    stl_heap_sort(arr2);

    if (check_sort(arr1) && check_sort(arr2)) {
        std::cout << "Two sorting algorithms are correct." << std::endl;
    } else {
        std::cout << "Two sorting algorithms are wrong." << std::endl;
    }
    std::cout << std::endl;
}

// 生成测试序列
enum class Order {
    ASC, // 升序
    DESC, // 降序
    RANDOM // 随机
};

enum class Repeat {
    NO, // 无重复
    YES // 有重复
};

// 填充数据辅助方法
template <typename T>
void fill_data(std::vector<T>& arr, std::function<T()> generator, Repeat repeat) {
    if (repeat == Repeat::NO) {
        std::unordered_set<T> unique_elements;
        for (long long i = 0; i < arr.size(); ++i) {
            T value;
            do {
                value = generator();
            } while (unique_elements.find(value) != unique_elements.end());
            unique_elements.insert(value);
            arr[i] = value;
        }
    } else {
        for (long long i = 0; i < arr.size(); ++i) {
            arr[i] = generator();
        }
    }
}

std::vector<int> generate_data_int(long long size, Order order, Repeat repeat) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, size);

    auto generator = [&]() { return dis(gen); };
    fill_data<int>(arr, generator, repeat);

    if (order == Order::ASC) {
        std::sort(arr.begin(), arr.end());
    } else if (order == Order::DESC) {
        std::sort(arr.begin(), arr.end(), std::greater<int>());
    }

    return arr;
}

std::vector<double> generate_data_double(long long size, Order order, Repeat repeat) {
    std::vector<double> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(1.0, static_cast<double>(size));

    auto generator = [&]() { return dis(gen); };
    fill_data<double>(arr, generator, repeat);

    if (order == Order::ASC) {
        std::sort(arr.begin(), arr.end());
    } else if (order == Order::DESC) {
        std::sort(arr.begin(), arr.end(), std::greater<double>());
    }

    return arr;
}