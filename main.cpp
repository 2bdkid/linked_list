#include "linked_list.hpp"

int main() {
  LinkedList<int> list;

  list.push_back(0);
  list.push_back(1);
  list.push_back(2);

  std::cout << list[0] << '\n';
  std::cout << list[1] << '\n';
  std::cout << list[2] << '\n';

  list.pop_front();
  list.pop_front();
  list.pop_front();

  list.push_front(3);
  list.push_front(2);
  list.push_front(1);

  std::cout << list[0] << '\n';
  std::cout << list[1] << '\n';
  std::cout << list[2] << '\n';
}
