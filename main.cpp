#include <iostream>
#include "linked_list.hpp"

int main() {
  LinkedList<int> list;

  list.push_back(0);
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  auto list2 = list.split_at(2);
  std::cout << list2[0] << '\n';
  std::cout << list2[1] << '\n';
}
