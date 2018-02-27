#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <memory>
#include <cstddef>
#include <utility>

template<typename Type>
class LinkedList {
private:
  class Node;
  
public:
  class Iter;
  class IterConst;

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

  void swap(LinkedList& other) {
    std::swap(head, other.head);
  }

  Iter begin() {
    return Iter {&head};
  }

  IterConst begin() const {
    return IterConst {&head};
  }

  Iter end() {
    auto traverse = &head;

    while (*traverse) {
      traverse = &(*traverse)->next;
    }

    return Iter {traverse};
  }

  IterConst end() const {
    auto traverse = &head;

    while (*traverse) {
      traverse = &(*traverse)->next;
    }

    return IterConst {traverse};
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

  std::size_t size() const {
    std::size_t size = 0;
    auto traverse = &head;

    while (*traverse) {
      traverse = &(*traverse)->next;
      size++;
    }

    return size;
  }

  LinkedList split_at(std::size_t index) {
    auto traverse = &head;
    LinkedList new_list;
    
    for (auto i = 0u; i < index; i++) {
      traverse = &(*traverse)->next;
    }

    std::swap(new_list.head, *traverse);
    return std::move(new_list);
  }
  
  class Iter {
  public:
    Iter(std::unique_ptr<Node>* ptr) : ptr {ptr} {}
    
    /* prefix */
    Iter& operator++() {
      ptr = &(*ptr)->next;
      return *this;
    }
    
    /* postfix */
    Iter operator++(int) {
      Iter temp {*this};
      operator++();
      return temp;
    }

    Type& operator*() {
      return (*ptr)->data;
    }

    bool operator==(const Iter& other) const {
      return ptr == other.ptr;
    }

    bool operator!=(const Iter& other) const {
      return !(*this == other);
    }

  private:
    std::unique_ptr<Node>* ptr = nullptr;
  };

  class IterConst {
  public:
    IterConst(std::unique_ptr<Node>* ptr) : ptr {ptr} {}

    /* prefix */
    IterConst& operator++() {
      ptr = &(*ptr)->next;
      return *this;
    }

    /* postfix */
    IterConst operator++(int) {
      IterConst temp {*this};
      operator++();
      return temp;
    }

    Type& operator*() const {
      return (*ptr)->data;
    }

    bool operator==(const IterConst& other) const {
      return ptr == other.ptr;
    }

    bool operator!=(const IterConst& other) const {
      return !(*this == other);
    }

  private:
    std::unique_ptr<Node> const* ptr = nullptr;
  };
  
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
