#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <memory>
#include <cstddef>
#include <utility>

template<typename Type>
class LinkedList {
private:
  class Node {
  public:
    Node(const Type&);
    std::unique_ptr<Node> next = nullptr;
    Type data;
  };

  std::unique_ptr<Node> head = nullptr;
  
public:
  class Iter {
  public:
    Iter(std::unique_ptr<Node>*);
    Iter& operator++();
    Iter operator++(int);
    Type& operator*();
    bool operator==(const Iter&) const;
    bool operator!=(const Iter&) const;
  private:
    std::unique_ptr<Node>* ptr = nullptr;
  };

  class IterConst {
  public:
    IterConst(std::unique_ptr<Node>*);
    IterConst& operator++();
    IterConst operator++(int);
    Type& operator*() const;
    bool operator==(const IterConst&) const;
    bool operator!=(const IterConst&) const;
  private:
    std::unique_ptr<Node> const* ptr = nullptr;
  };
  
  LinkedList() = default;
  LinkedList(const LinkedList&);
  LinkedList(LinkedList&&);
  ~LinkedList();
  
  LinkedList& operator=(LinkedList);
  LinkedList& operator=(LinkedList&&);
  Type& operator[](const std::size_t);
  Type const& operator[](const std::size_t) const;
  Iter begin();
  IterConst begin() const;
  Iter end();
  IterConst end() const;

  void swap(LinkedList&);
  void push_back(const Type&);
  Type pop_back();
  void push_front(const Type&);
  Type pop_front();
  void insert_at(std::size_t, const Type&);
  void delete_at(std::size_t);
  std::size_t size() const;
  LinkedList split_at(std::size_t);
};

template<typename Type>
LinkedList<Type>::LinkedList(const LinkedList& other) {
  auto traverse = &other.head;
  auto new_node = &head;

  while (*traverse) {
    *new_node = std::make_unique<LinkedList<Type>::Node>((*traverse)->data);
    traverse = &(*traverse)->next;
    new_node = &(*new_node)->next;
  }
}

template<typename Type>
LinkedList<Type>& LinkedList<Type>::operator=(LinkedList other) {
  std::swap(head, other.head);
  return *this;
}

template<typename Type>
LinkedList<Type>::LinkedList(LinkedList&& other) {
  std::swap(head, other.head);
}

template<typename Type>
LinkedList<Type>& LinkedList<Type>::operator=(LinkedList&& other) {
  std::swap(head, other.head);
  return *this;
}

template<typename Type>
LinkedList<Type>::~LinkedList() {
  auto end = &head;

  while (*end) {
    *end = std::move((*end)->next);
  }
}

template<typename Type>
Type& LinkedList<Type>::operator[](const std::size_t index) {
  auto target = &head;

  for (auto i = 0u; i < index; i++) {
    target = &(*target)->next;
  }

  return (*target)->data;
}

template<typename Type>
Type const& LinkedList<Type>::operator[](const std::size_t index) const {
  auto target = &head;

  for (auto i = 0u; i < index; i++) {
    target = &(*target)->next;
  }

  return (*target)->data;
}

template<typename Type>
void LinkedList<Type>::swap(LinkedList& other) {
    std::swap(head, other.head);
}

template<typename Type>
typename LinkedList<Type>::Iter LinkedList<Type>::begin() {
    return Iter {&head};
  }

template<typename Type>
typename LinkedList<Type>::IterConst LinkedList<Type>::begin() const {
  return IterConst {&head};
}

template<typename Type>
typename LinkedList<Type>::Iter LinkedList<Type>::end() {
  auto traverse = &head;

  while (*traverse) {
    traverse = &(*traverse)->next;
  }

  return Iter {traverse};
}

template<typename Type>
typename LinkedList<Type>::IterConst LinkedList<Type>::end() const {
  auto traverse = &head;

  while (*traverse) {
    traverse = &(*traverse)->next;
  }

  return IterConst {traverse};
}

template<typename Type>
void LinkedList<Type>::push_back(const Type& data) {
  auto end = &head;

  while (*end) {
    end = &(*end)->next;
  }

  *end = std::make_unique<Node>(data);
}

template<typename Type>
Type LinkedList<Type>::pop_back() {
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

template<typename Type>
void LinkedList<Type>::push_front(const Type& data) {
  auto new_head = std::make_unique<Node>(data);
  new_head->next = std::move(head);
  head = std::move(new_head);
}

template<typename Type>
Type LinkedList<Type>::pop_front() {
  const Type data = head->data;
  head = std::move(head->next);
  return data;
}

template<typename Type>
void LinkedList<Type>::insert_at(std::size_t index, const Type& data) {
  auto target = &head;

  for (auto i = 0u; i < index; i++) {
    target = &(*target)->next;
  }

  auto new_node = std::make_unique<Node>(data);
  new_node->next = std::move(*target);
  *target = std::move(new_node);
}

template<typename Type>
void LinkedList<Type>::delete_at(std::size_t index) {
  auto target = &head;
  auto previous = &head;
    
  for (auto i = 0u; i <= index; i++) {
    previous = target;
    target = &(*target)->next;
  }

  *previous = std::move(*target);
}

template<typename Type>
std::size_t LinkedList<Type>::size() const {
  std::size_t size = 0;
  auto traverse = &head;

  while (*traverse) {
    traverse = &(*traverse)->next;
    size++;
  }

  return size;
}

template<typename Type>
LinkedList<Type> LinkedList<Type>::split_at(std::size_t index) {
  auto traverse = &head;
  LinkedList new_list;
    
  for (auto i = 0u; i < index; i++) {
    traverse = &(*traverse)->next;
  }

  std::swap(new_list.head, *traverse);
  return new_list;
}

template<typename Type>
LinkedList<Type>::Iter::Iter(std::unique_ptr<LinkedList<Type>::Node>* ptr) : ptr {ptr} {}

template<typename Type>
typename LinkedList<Type>::Iter& LinkedList<Type>::Iter::operator++() {
  ptr = &(*ptr)->next;
  return *this;
}

template<typename Type>
typename LinkedList<Type>::Iter LinkedList<Type>::Iter::operator++(int) {
  Iter temp {*this};
  operator++();
  return temp;
}

template<typename Type>
Type& LinkedList<Type>::Iter::operator*() {
  return (*ptr)->data;
}

template<typename Type>
bool LinkedList<Type>::Iter::operator==(const LinkedList<Type>::Iter& other) const {
  return ptr == other.ptr;
}

template<typename Type>
bool LinkedList<Type>::Iter::operator!=(const LinkedList<Type>::Iter& other) const {
  return !(*this == other);
}

template<typename Type>
LinkedList<Type>::IterConst::IterConst(std::unique_ptr<LinkedList<Type>::Node>* ptr) : ptr {ptr} {}

template<typename Type>
typename LinkedList<Type>::IterConst& LinkedList<Type>::IterConst::operator++() {
  ptr = &(*ptr)->next;
  return *this;
}

template<typename Type>
typename LinkedList<Type>::IterConst LinkedList<Type>::IterConst::operator++(int) {
  IterConst temp {*this};
  operator++();
  return temp;
}

template<typename Type>
Type& LinkedList<Type>::IterConst::operator*() const {
  return (*ptr)->data;
}

template<typename Type>
bool LinkedList<Type>::IterConst::operator==(const LinkedList<Type>::IterConst& other) const {
  return ptr == other.ptr;
}

template<typename Type>
bool LinkedList<Type>::IterConst::operator!=(const LinkedList<Type>::IterConst& other) const {
  return !(*this == other);
}

template<typename Type>
LinkedList<Type>::Node::Node(const Type& data) : data {data} {}

#endif
