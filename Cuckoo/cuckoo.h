#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <utility>
#include <random>
#include <optional>
#include <type_traits>
#include <concepts>
#include <tuple>

// 辅助函数：生成素数
auto nextPrime(int n) -> int;

// 定义可哈希概念
template <typename T>
concept Hashable = requires(T t) {
    { std::hash<T>{}(t) } -> std::convertible_to<std::size_t>;
    { t == t } -> std::convertible_to<bool>;
};

// 定义可打印概念
template <typename T>
concept Printable = requires(T t, std::ostream &os) {
    { os << t } -> std::convertible_to<std::ostream &>;
};

// 哈希函数族类
template <Hashable Key, typename Hash = std::hash<Key>>
class HashFunctionFamily
{
    std::vector<int> primes;
    int num_functions;
    Hash user_hash;

public:
    explicit HashFunctionFamily(const int num_functions) : num_functions(num_functions)
    {
        if (num_functions <= 0)
        {
            throw std::invalid_argument("Number of hash functions must be positive.");
        }

        for (int i = 0; i < num_functions; ++i)
        {
            primes.push_back(nextPrime(i + 1));
        }
    }

    auto hash(const Key &key, const int function_index, int table_size) const -> int
    {
        return (user_hash(key) + primes[function_index]) % table_size;
    }
};

// 哈希表参数结构体
struct HashTableParams
{
    int initial_table_size = 47;
    double max_load_factor = 0.5;
    int max_rehash_attempts = 50;

    HashTableParams() = default;

    HashTableParams(int initial_table_size,
                    double max_load_factor,
                    int max_rehash_attempts)
    {
        this->initial_table_size = initial_table_size;
        this->max_load_factor = max_load_factor;
        this->max_rehash_attempts = max_rehash_attempts;
    }

    HashTableParams(const HashTableParams &other)
    {
        initial_table_size = other.initial_table_size;
        max_load_factor = other.max_load_factor;
        max_rehash_attempts = other.max_rehash_attempts;
    }

    HashTableParams &operator=(const HashTableParams &other)
    {
        if (this != &other)
        {
            initial_table_size = other.initial_table_size;
            max_load_factor = other.max_load_factor;
            max_rehash_attempts = other.max_rehash_attempts;
        }
        return *this;
    }
};

static HashTableParams hashTableParams;

template <Hashable Key, typename Hash = std::hash<Key>>
class CuckooHashTable
{
    int INITIAL_TABLE_SIZE = hashTableParams.initial_table_size;
    double MAX_LOAD_FACTOR = hashTableParams.max_load_factor;
    int MAX_REHASH_ATTEMPTS = hashTableParams.max_rehash_attempts;

    std::vector<std::vector<std::optional<Key>>> tables; // 多张哈希表
    int num_elements;                                    // 元素个数
    int table_size;                                      // 当前哈希表大小
    HashFunctionFamily<Key, Hash> hash_functions;

    void rehash()
    {
        std::cout << "Rehashing..." << std::endl;
        auto old_tables = tables;                                                  // 保存旧表
        table_size = nextPrime(2 * table_size);                                    // 扩大表
        tables.assign(tables.size(), std::vector<std::optional<Key>>(table_size)); // 重新分配表

        num_elements = 0;

        // 重新插入元素
        for (const auto &old_table : old_tables)
        {
            for (const auto &key : old_table)
            {
                if (key.has_value())
                {
                    insert(std::move(key.value()));
                }
            }
        }
    }

    // 计算负载因子
    auto loadFactor() const -> double
    {
        return static_cast<double>(num_elements) / (tables.size() * table_size);
    }

public:
    explicit CuckooHashTable(const int num_functions) : num_elements(0), table_size(INITIAL_TABLE_SIZE),
                                                        hash_functions(num_functions)
    {
        tables.assign(num_functions, std::vector<std::optional<Key>>(table_size));
    }

    // 插入元素（左值引用）
    void insert(const Key &key)
    {
        Key temp_key = key;
        insert(std::move(temp_key));
    }

    // 插入元素（右值引用）
    void insert(Key &&key)
    {
        if (loadFactor() > MAX_LOAD_FACTOR)
        {
            rehash();
        }

        int attempts = 0;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> table_dist(0, tables.size() - 1);

        while (attempts < MAX_REHASH_ATTEMPTS)
        {
            for (int i = 0; i < tables.size(); ++i)
            {
                int index = hash_functions.hash(key, i, table_size);
                if (!tables[i][index].has_value())
                {
                    tables[i][index] = std::move(key);
                    ++num_elements;
                    return;
                }
                // 替换已有元素
                std::swap(key, tables[i][index].value());
            }

            // 没有可用位置，随机踢出一个元素
            int table_index = table_dist(gen);
            int index = hash_functions.hash(key, table_index, table_size);
            std::swap(key, tables[table_index][index].value());
            ++attempts;
        }

        // 超过最大次数
        rehash();
        insert(std::move(key));
    }

    // 查找元素
    auto find(const Key &key) const -> bool
    {
        for (int i = 0; i < tables.size(); ++i)
        {
            int index = hash_functions.hash(key, i, table_size);
            if (tables[i][index].has_value() && tables[i][index].value() == key)
            {
                return true;
            }
        }

        return false;
    }

    // 删除元素
    void erase(const Key &key)
    {
        for (int i = 0; i < tables.size(); ++i)
        {
            int index = hash_functions.hash(key, i, table_size);
            if (tables[i][index].has_value() && tables[i][index].value() == key)
            {
                tables[i][index].reset();
                --num_elements;
                return;
            }
        }

        throw std::runtime_error("Key not found.");
    }

    // 打印哈希表
    void printTable() const
        requires Printable<Key>
    {
        for (int i = 0; i < tables.size(); ++i)
        {
            std::cout << "Table " << i << ": ";
            for (int j = 0; j < table_size; ++j)
            {
                if (tables[i][j].has_value())
                {
                    std::cout << tables[i][j].value() << " ";
                }
                else
                {
                    std::cout << "- ";
                }
            }
            std::cout << std::endl;
        }
    }
};
