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

private:
    struct BinaryNode {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt): element{theElement}, left{lt},
            right{rt} {
        }

        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt): element{std::move(theElement)}, left{lt},
                                                                             right{rt} {
        }
    };

    BinaryNode *root;

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
    
    void remove(const Comparable &x, BinaryNode *&t) {
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

    // void transplant()

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