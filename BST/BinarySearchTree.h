#include <cstddef>
class UnderflowException {
};

class IllegalArgumentException {
};

class ArrayIndexOutOfBoundsException {
};

class IteratorOutOfBoundsException {
};

class IteratorMismatchException {
};

class IteratorUninitializedException {
};

#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;

template<typename Comparable>
class BinarySearchTree {
public:
    BinarySearchTree(): root{nullptr} {
    };

    BinarySearchTree(const BinarySearchTree &rhs): root{nullptr} {
        root = clone(rhs.root);
    }

    BinarySearchTree(BinarySearchTree &&rhs) noexcept : root{rhs.root} {
        rhs.root = nullptr;
    }

    ~BinarySearchTree() {
        makeEmpty();
    }

    BinarySearchTree &operator=(const BinarySearchTree &rhs) {
        BinarySearchTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    BinarySearchTree &operator=(BinarySearchTree &&rhs) noexcept {
        std::swap(root, rhs.root);
        return *this;
    }

    const Comparable &findMin() const {
        if (isEmpty()) {
            throw UnderflowException{};
        }
        return findMin(root)->element;
    }

    const Comparable &findMax() const {
        if (isEmpty()) {
            throw UnderflowException{};
        }
        return findMax(root)->element;
    }

    bool contains(const Comparable &x) const {
        return contains(x, root);
    }

    [[nodiscard]] bool isEmpty() const {
        return root == nullptr;
    }

    void printTree(ostream &out = cout) const {
        if (isEmpty()) {
            out << "Empty tree" << endl;
        } else {
            printTree(root, out);
        }
    }

    void makeEmpty() {
        makeEmpty(root);
    }

    void insert(const Comparable &x) {
        insert(x, root);
    }

    void insert(Comparable &&x) {
        insert(std::move(x), root);
    }

    void remove(const Comparable &x) {
        remove(x, root);
    }

    void another_remove(const Comparable &x) {
        another_remove(x, root);
    }

    void yet_another_remove(const Comparable &x) {
        yet_another_remove(x, root);
    }

protected:
    struct BinaryNode {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        int height;

        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt, int h = 0)
            : element{theElement}, left{lt}, right{rt}, height{h} {
        }

        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt, int h = 0)
            : element{std::move(theElement)}, left{lt}, right{rt}, height{h} {
        }
    };

    BinaryNode *root;

    int height(BinaryNode *t) const {
        return t == nullptr ? 0 : t->height;
    }

    void rotateWithLeftChild(BinaryNode *&k2) {
        BinaryNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = std::max(height(k2->left), height(k2->right)) + 1;
        k1->height = std::max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    void rotateWithRightChild(BinaryNode *&k1) {
        BinaryNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = std::max(height(k1->left), height(k1->right)) + 1;
        k2->height = std::max(height(k2->right), k1->height) + 1;
        k1 = k2;
    }

    void doubleWithLeftChild(BinaryNode *&k3) {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    void doubleWithRightChild(BinaryNode *&k1) {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }

    void balance(BinaryNode *&t) {
        if (t == nullptr) {
            return;
        }

        if (height(t->left) - height(t->right) > 1) {
            if (height(t->left->left) >= height(t->left->right)) {
                rotateWithLeftChild(t);
            } else {
                doubleWithLeftChild(t);
            }
        } else if (height(t->right) - height(t->left) > 1) {
            if (height(t->right->right) >= height(t->right->left)) {
                rotateWithRightChild(t);
            } else {
                doubleWithRightChild(t);
            }
        }

        t->height = std::max(height(t->left), height(t->right)) + 1;
    }

    void insert(const Comparable &x, BinaryNode * &t) {
        if (t == nullptr) {
            t = new BinaryNode{x, nullptr, nullptr};
        } else if (x < t->element) {
            insert(x, t->left);
        } else if (t->element < x) {
            insert(x, t->right);
        } else {
            ; // Duplicate; do nothing
        }
        balance(t);
    }

    void remove(const Comparable &x, BinaryNode *&t) {
        another_remove(x, t);
        balance(t);
    }

    BinaryNode* removeMin(BinaryNode *&t) {
        if (t == nullptr) {
            return nullptr;
        }
        if (t->left != nullptr) {
            return removeMin(t->left);
        } else {
            BinaryNode *oldNode = t;
            t = t->right;
            return oldNode;
        }
    }
    
    void another_remove(const Comparable &x, BinaryNode *&t) {
        if (t == nullptr) {
            return;
        }
        if (x < t->element) {
            remove(x, t->left);
        } else if (t->element < x) {
            remove(x, t->right);
        } else {
            BinaryNode *oldNode = t;
            if (t->left != nullptr && t->right != nullptr) {
                t = removeMin(t->right);
                t->right = oldNode->right;
                t->left = oldNode->left;
            } else {
                t = (t->left != nullptr) ? t->left : t->right;
            }
            delete oldNode;
        }
    }

    BinaryNode* findNode(const Comparable &x, BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        } else if (x < t->element) {
            return findNode(x, t->left);
        } else if (t->element < x) {
            return findNode(x, t->right);
        } else {
            return t;
        }
    }

    BinaryNode* findParent(BinaryNode *child, BinaryNode *t) const {
        if (t == nullptr || t == child) {
            return nullptr;
        }
        if ((t->left != nullptr && t->left == child) || (t->right != nullptr && t->right == child)) {
            return t;
        }
        if (child->element < t->element) {
            return findParent(child, t->left);
        } else {
            return findParent(child, t->right);
        }
    }

    void transplant(BinaryNode *u, BinaryNode *v) {
        BinaryNode *parent = findParent(u, root);
        if (parent == nullptr) {
            root = v;
        } else if (parent->left == u) {
            parent->left = v;
        } else {
            parent->right = v;
        }
    }

    void yet_another_remove(const Comparable &x, BinaryNode *&t) {
        BinaryNode *z = findNode(x, t);
        if (z == nullptr) {
            return;
        }
        if (z->left == nullptr) {
            transplant(z, z->right);
        } else if (z->right == nullptr) {
            transplant(z, z->left);
        } else {
            BinaryNode *y = findMin(z->right);
            if (findParent(y, z) != z) {
                transplant(y, y->right);
                y->right = z->right;
            }
            transplant(z, y);
            y->left = z->left;
        }
        delete z;
    }

    BinaryNode *findMin(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        if (t->left == nullptr) {
            return t;
        }
        return findMin(t->left);
    }

    static BinaryNode *findMax(BinaryNode *t) {
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    }

    bool contains(const Comparable &x, BinaryNode *t) const {
        if (t == nullptr) {
            return false;
        } else if (x < t->element) {
            return contains(x, t->left);
        } else if (t->element < x) {
            return contains(x, t->right);
        } else {
            return true;
        }
    }

    void makeEmpty(BinaryNode * &t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    void printTree(BinaryNode *t, ostream &out, int indent = 0, bool isRight = false, const std::string &prefix = "") const {
        if (t != nullptr) {
            if (t->right) {
                printTree(t->right, out, indent + 4, true, prefix + (isRight ? "    " : "│   "));
            }
            out << prefix;
            if (isRight) {
                out << "┌──";
            } else if (indent) {
                out << "└──";
            }
            out << t->element << "\n";
            if (t->left) {
                printTree(t->left, out, indent + 4, false, prefix + (isRight ? "│   " : "    "));
            }
        }
    }

    BinaryNode *clone(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        } else {
            return new BinaryNode{t->element, clone(t->left), clone(t->right)};
        }
    }
};