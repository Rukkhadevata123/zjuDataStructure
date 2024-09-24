#include "Chicken.h"
#include <cstring>
#include <iostream>

int main(void) {
  // 使用不同的构造函数创建对象
  Chicken chicken1;
  Chicken chicken2(2);
  Chicken chicken3(3, "Hen");
  Chicken chicken4("Rooster");

  // 输出对象信息
  std::cout << chicken1 << std::endl;
  std::cout << chicken2 << std::endl;
  std::cout << chicken3 << std::endl;
  std::cout << chicken4 << std::endl;

  // 测试深拷贝构造函数
  Chicken chicken5 = chicken3;
  std::cout << "After copy construction: " << chicken5 << std::endl;
  chicken3.setName("New Hen");
  std::cout << "After modifying original: " << chicken3 << std::endl;
  std::cout << "After modifying original, copied: " << chicken5 << std::endl;

  // 测试赋值运算符
  chicken1 = chicken4;
  std::cout << "After assignment: " << chicken1 << std::endl;
  chicken4.setAge(5);
  std::cout << "After modifying original: " << chicken4 << std::endl;
  std::cout << "After modifying original, assigned: " << chicken1 << std::endl;

  // 测试set和get方法
  chicken2.setAge(4);
  chicken2.setName("Chick");
  std::cout << "After setting new values: " << chicken2 << std::endl;
  std::cout << "Get name: " << chicken2.getName() << std::endl;
  std::cout << "Get age: " << chicken2.getAge() << std::endl;

  return 0;
}
