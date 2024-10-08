#include "LinkedList.h"

int main() {
  // 创建链表对象
  SingleLinkedList<int> list;

  // 插入元素
  list.insert(1);
  list.insert(2);
  list.insert(3);
  list.printList(); // 输出: 1->2->3->nullptr

  // 查找元素
  if (list.find(2)) {
    std::cout << "Found: " << list.getCurrentVal()
              << std::endl; // 输出: Found: 2
  }

  // 修改当前元素的值
  list.setCurrentVal(4);
  list.printList(); // 输出: 1->4->3->nullptr

  // 删除当前元素
  list.remove();
  list.printList(); // 输出: 1->3->nullptr

  // 清空链表
  list.emptyList();
  list.printList(); // 输出: nullptr

  // 使用初始化列表构造链表
  SingleLinkedList<int> list2 = {5, 6, 7};
  list2.printList(); // 输出: 5->6->7->nullptr

  // 使用拷贝构造函数
  SingleLinkedList<int> list3 = list2;
  list3.printList(); // 输出: 5->6->7->nullptr

  // 使用赋值运算符
  SingleLinkedList<int> list4;
  list4 = list2;
  list4.printList(); // 输出: 5->6->7->nullptr

  // 修改 list2 后，检查 list3 和 list4 是否保持不变
  list2.find(6);
  list2.setCurrentVal(8);
  list2.printList(); // 输出: 5->8->7->nullptr
  list3.printList(); // 输出: 5->6->7->nullptr
  list4.printList(); // 输出: 5->6->7->nullptr

  return 0;
}