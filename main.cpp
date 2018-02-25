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
    Node<Type>* end = head.get();
    
    while (end) {
      if (!end->next)
	break;
      end = end->next.get();
    }

    end->next = std::make_unique<Node<Type>>(data);
  }

  Type pop_back() {
    Node<Type>* end = head.get();
    Node<Type>* previous = nullptr;

    while (end) {
      previous = end;
      if (!end->next)
	break;
      end = end->next.get();
    }
    
    const Type data = end->data;

    if (previous) {
      previous->next = nullptr;
    }

    return data;
  }

  void push_front(const Type& data) {
    std::unique_ptr<Node<Type>> new_head = std::make_unique<Node<Type>>(data);
    new_head->next = std::move(head);
    head = std::move(new_head);
  }

  Type pop_front() {
    if (!head) {
      throw;
    }

    const Type data = head->data;
    head = std::move(head->next);
    return data;
  }
  
  ~LinkedList() {
    if (!head) {
      return;
    }

    while (head->next) {
      head = std::move(head->next);
    }

    head = nullptr;
  }

private:
  std::unique_ptr<Node<Type>> head = nullptr;
};

int main() {
  LinkedList<int> list;

  list.push_front(0);
  list.push_front(1);
  list.push_front(2);

  list.pop_back();
  list.pop_back();
  list.pop_back();
}
