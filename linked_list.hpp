#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

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
    *previous = nullptr;
    return data;
  }

  void push_front(const Type& data) {
    auto new_head = std::make_unique<Node<Type>>(data);
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

    auto new_node = std::make_unique<Node<Type>>(data);
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

  Type& operator[](std::size_t index) {
    auto target = &head;

    for (auto i = 0u; i < index; i++) {
      target = &(*target)->next;
    }

    return (*target)->data;
  }
  
  virtual ~LinkedList() {
    auto end = &head;

    while (*end) {
      *end = std::move((*end)->next);
    }
  }

private:
  std::unique_ptr<Node<Type>> head = nullptr;
};

#endif
