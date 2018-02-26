#include <iostream>
#include <memory>
#include <cstddef>
#include <utility>

template<typename Type>
class Node {
public:
  Node(const Type& data) : data {data} {}
  std::unique_ptr<Node<Type>> next = nullptr;
  Type data;
};

template<typename Type>
class LinkedList {
public:
  void push_back(const Type& data) {
    auto end = &head;

    while (*end) {
      end = &(*end)->next;
    }

    *end = std::make_unique<Node<Type>>(data);
  }

  Type pop_back() {
    auto end = &head;
    auto previous = &head;

    while (*end) {
      previous = end;
      end = &(*end)->next;
    }

    const Type data = (*previous)->data;
    (*previous) = nullptr;
    return data;
  }

  void push_front(const Type& data) {
    std::unique_ptr<Node<Type>> new_head = std::make_unique<Node<Type>>(data);
    new_head->next = std::move(head);
    head = std::move(new_head);
  }

  Type pop_front() {
    const Type data = head->data;
    head = std::move(head->next);
    return data;
  }
  
  ~LinkedList() {
    auto end = &head;

    while (*end) {
      (*end) = std::move((*end)->next);
    }
  }

private:
  std::unique_ptr<Node<Type>> head = nullptr;
};

int main() {
  LinkedList<int> list;

  list.push_back(0);
  list.push_back(1);
  list.push_back(2);

  list.pop_back();
  list.pop_back();
  list.pop_back();

  list.push_front(0);
  list.push_front(1);
  list.push_front(2);

  list.pop_front();
  list.pop_front();
  list.pop_front();

  list.push_front(0);
  list.push_back(1);
  list.push_front(2);
}
