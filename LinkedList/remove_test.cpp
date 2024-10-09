#include "LinkedList.h"
#include <iostream>

int main() {
  SingleLinkedList<int> list;
  for (int i = 0; i < 100; i++) {
    list.insert(i);
  }
  list.find(50);
  for (int i = 0; i < 100; i++) {
    list.remove();
    if (list.getSize() > 0) {
      std::cout << "Size: " << list.getSize() << "  ";

      std::cout << "Remove" << list.getCurrentVal() << std::endl;
    }
  }
}
