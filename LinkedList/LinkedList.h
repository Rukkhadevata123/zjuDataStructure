#include <initializer_list>
#include <iostream>

template <typename T> class SingleLinkedList {
private:
  class Node {
    T data;
    Node *next = nullptr;
    Node(const T &data) : data(data), next(nullptr) {}
    Node(const T &data, Node *next) : data(data), next(next) {}
    friend class SingleLinkedList<T>;
  };

  Node *head = nullptr;
  Node *currentPos = nullptr;
  int size = 0;

  void _copy(const SingleLinkedList<T> &other) {
    Node *p = other.head;
    while (p != nullptr) {
      insert(p->data);
      p = p->next;
    }
  }

public:
  SingleLinkedList() = default;
  SingleLinkedList(const SingleLinkedList<T> &other) { _copy(other); }
  SingleLinkedList(std::initializer_list<T> list) {
    for (const T &val : list) {
      insert(val);
    }
  }
  ~SingleLinkedList() { emptyList(); }
  SingleLinkedList<T> &operator=(const SingleLinkedList<T> &other) {
    if (this != &other) {
      emptyList();
      _copy(other);
    }
    return *this;
  }

  T getCurrentVal() const {
    if (currentPos == nullptr) {
      throw std::runtime_error("No current element");
    }
    return currentPos->data;
  }

  void setCurrentVal(const T &val) {
    if (currentPos == nullptr) {
      throw std::runtime_error("No current element");
    }
    currentPos->data = val;
  }

  bool isEmpty() const { return size == 0; }
  int getSize() const { return size; }

  void emptyList() {
    Node *p = head;
    while (p != nullptr) {
      Node *temp = p;
      p = p->next;
      delete temp;
    }
    head = nullptr;
    currentPos = nullptr;
    size = 0;
  }

  bool find(const T &val) {
    Node *p = head;
    while (p != nullptr) {
      if (p->data == val) {
        currentPos = p;
        return true;
      }
      p = p->next;
    }
    return false;
  }
  void insert(const T &val) {
    Node *newNode = new Node(val);
    if (head == nullptr) {
      head = newNode;
      currentPos = head;
    } else if (currentPos == nullptr) {
      newNode->next = head;
      head = newNode;
    } else {
      newNode->next = currentPos->next;
      currentPos->next = newNode;
    }
    currentPos = newNode;
    ++size;
  }
  void remove() {
    if (currentPos == nullptr) {
      throw std::runtime_error("No current element");
    }
    if (currentPos == head) {
      Node *temp = head;
      head = head->next;
      delete temp;
      currentPos = head;
    } else {
      Node *prev = head;
      Node *temp = head->next;
      while (temp != currentPos) {
        prev = temp;
        temp = temp->next;
      }
      prev->next = currentPos->next;
      delete currentPos;
      currentPos = prev->next;
    }
    --size;
  }

  void printList() const {
    Node *p = head;
    while (p != nullptr) {
      std::cout << p->data << "->";
      p = p->next;
    }
    std::cout << "nullptr" << std::endl;
  }
};