#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <random>
#include "cuckoo.h"
#include "student.h"

int main()
{
    std::vector<int> data_sizes;
    for (int i = 1000; i <= 20000; i += 100)
    {
        data_sizes.push_back(i);
    }
    constexpr int num_hash_functions = 20;

    std::ofstream insert_outfile("insert_times.txt");
    std::ofstream search_outfile("search_times.txt");
    if (!insert_outfile.is_open() || !search_outfile.is_open())
    {
        std::cerr << "Failed to open file for writing.\n";
        return 1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    for (const auto &num_students : data_sizes)
    {
        std::vector<Student> students;
        for (int i = 1; i <= num_students; ++i)
        {
            students.emplace_back("Stu" + std::to_string(i), "Tom" + std::to_string(i));
        }

        // INITIAL_TABLE_SIZE, MAX_LOAD_FACTOR, MAX_REHASH_ATTEMPTS
        hashTableParams = HashTableParams(203, 0.45, 100);

        // 测试插入性能
        {
            CuckooHashTable<Student> cuckoo_table(num_hash_functions);
            auto start_time = std::chrono::high_resolution_clock::now();
            for (const auto &student : students)
            {
                cuckoo_table.insert(student);
            }
            auto end_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end_time - start_time;
            insert_outfile << num_students << " " << duration.count() << "\n";
            std::cout << "Inserted " << num_students << " students in " << duration.count() << " seconds.\n";

            // 测试查找性能
            std::uniform_int_distribution<> dis(0, num_students - 1);
            int random_index = dis(gen);
            const auto &random_student = students[random_index];

            start_time = std::chrono::high_resolution_clock::now();
            cuckoo_table.find(random_student);
            end_time = std::chrono::high_resolution_clock::now();
            duration = end_time - start_time;
            search_outfile << num_students << " " << duration.count() << "\n";
            std::cout << "Searched for student " << random_student.id << " in " << duration.count() << " seconds.\n";
        }
    }

    insert_outfile.close();
    search_outfile.close();
    return 0;
}