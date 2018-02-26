#include "linked_list.hpp"

int main() {
  LinkedList<int> list;

  list.push_back(0);
  list.push_back(1);
  list.push_back(2);

  std::cout << list[0] << '\n';
  std::cout << list[1] << '\n';
  std::cout << list[2] << '\n';  
}
