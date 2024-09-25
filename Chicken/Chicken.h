#include <cstring>
#include <iostream>

class Chicken {
private:
  int age = 1;
  char *name = nullptr;

public:
  Chicken() {}
  Chicken(int _age) : age(_age) {}
  Chicken(int _age, const char *_name) : age(_age) {
    name = new char[strlen(_name) + 1];
    strcpy(name, _name);
  }
  Chicken(const char *_name) : age(1) {
    name = new char[strlen(_name) + 1];
    strcpy(name, _name);
  }

  Chicken(const Chicken &other) {
    age = other.age;
    if (other.name != nullptr) {
      if (name != nullptr) {
        delete[] name;
        name = nullptr;
      }
      name = new char[strlen(other.name) + 1];
      strcpy(name, other.name);
    }
  }

  Chicken &operator=(const Chicken &other) {
    if (this != &other) {
      age = other.age;
      if (other.name != nullptr) {
        if (name != nullptr) {
          delete[] name;
          name = nullptr;
        }
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
      }
    }
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &os, const Chicken &chicken) {
    if (chicken.name != nullptr) {
      os << "Name: " << chicken.name << ", Age: " << chicken.age;
    } else {
      os << "Name: undefined, Age: " << chicken.age;
    }
    return os;
  }

  ~Chicken() {
    if (name != nullptr) {
      delete[] name;
      name = nullptr;
    }
  }

  void setAge(int _age) { age = _age; }

  void setName(const char *_name) {
    if (name == _name) {
      return;
    }
    if (name != nullptr) {
      delete[] name; // prevent memory leak
      name = nullptr;
    }
    name = new char[strlen(_name) + 1];
    strcpy(name, _name);
  }

  const char *getName() const { return name; }

  int getAge() const { return age; }
};
