#include "List.h"
#include <iostream>

int main() {
  // Create an empty List of integers
  List<int> list1;

  // Testing push_back
  std::cout << "Testing push_back...\n";
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);
  for (const auto &elem : list1) {
    std::cout << elem << " "; // Should print: 1 2 3
  }
  std::cout << std::endl;

  // Testing push_front
  std::cout << "Testing push_front...\n";
  list1.push_front(0);
  for (const auto &elem : list1) {
    std::cout << elem << " "; // Should print: 0 1 2 3
  }
  std::cout << std::endl;

  // Testing pop_back
  std::cout << "Testing pop_back...\n";
  list1.pop_back();
  for (const auto &elem : list1) {
    std::cout << elem << " "; // Should print: 0 1 2
  }
  std::cout << std::endl;

  // Testing pop_front
  std::cout << "Testing pop_front...\n";
  list1.pop_front();
  for (const auto &elem : list1) {
    std::cout << elem << " "; // Should print: 1 2
  }
  std::cout << std::endl;

  // Testing size
  std::cout << "List size: " << list1.size() << std::endl; // Should print: 2

  // Testing empty
  std::cout << "Testing empty function...\n";
  std::cout << "List is empty: " << std::boolalpha << list1.empty()
            << std::endl; // Should print: false

  // Testing insert and erase
  std::cout << "Testing insert and erase...\n";
  auto it = list1.begin();
  ++it;                 // Move to second element
  list1.insert(it, 99); // Insert 99 before the second element
  for (const auto &elem : list1) {
    std::cout << elem << " "; // Should print: 1 99 2
  }
  std::cout << std::endl;

  list1.erase(--list1.end()); // Erase the last element (2)
  for (const auto &elem : list1) {
    std::cout << elem << " "; // Should print: 1 99
  }
  std::cout << std::endl;

  // Testing initializer_list constructor
  std::cout << "Testing initializer_list constructor...\n";
  List<int> list2{10, 20, 30, 40};
  for (const auto &elem : list2) {
    std::cout << elem << " "; // Should print: 10 20 30 40
  }
  std::cout << std::endl;

  // Testing copy constructor
  std::cout << "Testing copy constructor...\n";
  List<int> list3(list2); // Copy list2 to list3
  for (const auto &elem : list3) {
    std::cout << elem << " "; // Should print: 10 20 30 40
  }
  std::cout << std::endl;

  // Testing move constructor
  std::cout << "Testing move constructor...\n";
  List<int> list4(std::move(list3)); // Move list3 to list4
  for (const auto &elem : list4) {
    std::cout << elem << " "; // Should print: 10 20 30 40
  }
  std::cout << std::endl;

  // Check that list3 is now empty after the move
  std::cout << "After move, list3 size: " << list3.size()
            << std::endl; // Should print: 0

  // Testing assignment operator
  std::cout << "Testing assignment operator...\n";
  List<int> list5;
  list5 = list4; // Assign list4 to list5
  for (const auto &elem : list5) {
    std::cout << elem << " "; // Should print: 10 20 30 40
  }
  std::cout << std::endl;

  // Modify list5 and ensure list4 is unchanged (deep copy test)
  list5.push_back(50);
  std::cout << "After modifying list5...\n";
  std::cout << "list5: ";
  for (const auto &elem : list5) {
    std::cout << elem << " "; // Should print: 10 20 30 40 50
  }
  std::cout << std::endl;

  std::cout << "list4: ";
  for (const auto &elem : list4) {
    std::cout << elem << " "; // Should print: 10 20 30 40 (unchanged)
  }
  std::cout << std::endl;

  // Testing clear function
  std::cout << "Testing clear function...\n";
  list5.clear(); // Clear all elements in list5
  std::cout << "After clearing, list5 size: " << list5.size()
            << std::endl; // Should print: 0
  std::cout << "list5 is empty: " << std::boolalpha << list5.empty()
            << std::endl; // Should print: true

  return 0;
}
