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
    if (!head) {
      head = std::make_unique<Node<Type>>(data);
      return;
    }

    Node<Type>* end = head.get();

    while (end->next) {
      end = end->next.get();
    }

    end->next = std::make_unique<Node<Type>>(data);
  }

  Type pop_back() {
    if (!head) {
      throw;
    }
    
    Node<Type>* end = head.get();
    Node<Type>* previous = nullptr;
    
    while (end->next) {
      previous = end;
      end = end->next.get();
    }

    Type data = end->data;

    if (previous) {
      previous->next = nullptr;
    }

    return data;
  }

  void push_front(const Type& data) {
    if (!head) {
      head = std::make_unique<Node<Type>>(data);
      return;
    }

    std::unique_ptr<Node<Type>> new_head = std::make_unique<Node<Type>>(data);
    new_head->next = std::move(head);
    head = std::move(new_head);
  }

  Type pop_front() {
    if (!head) {
      throw;
    }

    Type data = head->data;
    head.reset(head->next.get());
    return data;
  }
  
  std::size_t size() const {
    /* check for empty list */
    if (!head) {
      return 0;
    }
    
    std::size_t size = 1;
    Node<Type>* traverse = head.get();

    while (traverse->next) {
      traverse = traverse->next.get();
      size++;
    }

    return size;
  }

private:
  std::unique_ptr<Node<Type>> head = nullptr;
};

int main() {
  LinkedList<int> list;
  list.push_front(1);
  list.push_back(2);

  std::cout << list.pop_back() << '\n';
  std::cout << list.pop_front() << '\n';
}
