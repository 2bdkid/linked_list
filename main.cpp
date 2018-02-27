#include <iostream>
#include "linked_list.hpp"

int main() {
  LinkedList<int> list;

  list.push_back(0);
  list.push_back(1);
  list.push_back(2);

  LinkedList<int> list2 = list;

  std::cout << list2[0] << '\n';
  std::cout << list2[1] << '\n';
  std::cout << list2[2] << '\n';

  std::cout << list2.size() << '\n';
}
