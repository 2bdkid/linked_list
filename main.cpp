#include <iostream>
#include "linked_list.hpp"

int main() {
  LinkedList<int> list;
  list.push_back(0);
  list.push_back(1);
  list.push_back(2);

  std::cout << list.pop_back() << '\n';
  std::cout << list.pop_back() << '\n';
  std::cout << list.pop_back() << '\n';
}
