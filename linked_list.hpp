#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <memory>
#include <cstddef>
#include <utility>

template<typename Type>
class LinkedList {
public:
  LinkedList() = default;

  LinkedList(const LinkedList& other) {
    auto traverse = &other.head;
    auto new_node = &head;

    while (*traverse) {
      *new_node = std::make_unique<Node>((*traverse)->data);
      traverse = &(*traverse)->next;
      new_node = &(*new_node)->next;
    }
  }

  LinkedList& operator=(LinkedList other) {
    std::swap(head, other.head);
    return *this;
  }

  LinkedList(LinkedList&& other) {
    std::swap(head, other.head);
  }

  LinkedList& operator=(LinkedList&& other) {
    std::swap(head, other.head);
    return *this;
  }

  virtual ~LinkedList() {
    auto end = &head;

    while (*end) {
      *end = std::move((*end)->next);
    }
  }

  Type& operator[](std::size_t index) {
    auto target = &head;

    for (auto i = 0u; i < index; i++) {
      target = &(*target)->next;
    }

    return (*target)->data;
  }
  
  void push_back(const Type& data) {
    auto end = &head;

    while (*end) {
      end = &(*end)->next;
    }

    *end = std::make_unique<Node>(data);
  }

  Type pop_back() {
    auto end = &head;
    auto previous = &head;

    while (*end) {
      previous = end;
      end = &(*end)->next;
    }

    const Type data = (*previous)->data;
    *previous = nullptr;
    return data;
  }

  void push_front(const Type& data) {
    auto new_head = std::make_unique<Node>(data);
    new_head->next = std::move(head);
    head = std::move(new_head);
  }

  Type pop_front() {
    const Type data = head->data;
    head = std::move(head->next);
    return data;
  }

  void insert_at(std::size_t index, const Type& data) {
    auto target = &head;

    for (auto i = 0u; i < index; i++) {
      target = &(*target)->next;
    }

    auto new_node = std::make_unique<Node>(data);
    new_node->next = std::move(*target);
    *target = std::move(new_node);
  }

  void delete_at(std::size_t index) {
    auto target = &head;
    auto previous = &head;
    
    for (auto i = 0u; i <= index; i++) {
      previous = target;
      target = &(*target)->next;
    }

    *previous = std::move(*target);
  }

private:
  class Node {
  public:
    Node(const Type& data) : data {data} {}
    std::unique_ptr<Node> next = nullptr;
    Type data;
  };

  std::unique_ptr<Node> head = nullptr;
};

#endif
