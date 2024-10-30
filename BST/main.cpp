#include "BinarySearchTree.h"
#include <iostream>

int main() {
    BinarySearchTree<int> bst;

    // 测试插入
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(18);

    std::cout << "树的内容：" << std::endl;
    bst.printTree();
    std::cout << std::endl;

    // 测试查找最小值和最大值
    try {
        std::cout << "最小值: " << bst.findMin() << std::endl;
        std::cout << "最大值: " << bst.findMax() << std::endl;
    } catch (const UnderflowException &e) {
        std::cout << "树为空，无法查找最小值或最大值。" << std::endl;
    }

    // 测试包含
    std::cout << "树包含10: " << bst.contains(10) << std::endl;
    std::cout << "树包含20: " << bst.contains(20) << std::endl;

    // 测试删除
    std::cout << "删除15后树的内容：" << std::endl;
    bst.remove(15);
    bst.printTree();
    std::cout << std::endl;

    std::cout << "删除10后树的内容：" << std::endl;
    bst.remove(10);
    bst.printTree();
    std::cout << std::endl;

    std::cout << "删除5后树的内容：" << std::endl;
    bst.remove(5);
    bst.printTree();
    std::cout << std::endl;

    std::cout << "删除3后树的内容：" << std::endl;
    bst.remove(3);
    bst.printTree();
    std::cout << std::endl;

    std::cout << "删除7后树的内容：" << std::endl;
    bst.remove(7);
    bst.printTree();
    std::cout << std::endl;

    std::cout << "删除12后树的内容：" << std::endl;
    bst.remove(12);
    bst.printTree();
    std::cout << std::endl;

    std::cout << "删除18后树的内容：" << std::endl;
    bst.remove(18);
    bst.printTree();
    std::cout << std::endl;

    return 0;
}