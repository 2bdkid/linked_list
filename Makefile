all: linked_list

linked_list: main.cpp linked_list.hpp
	g++ -std=c++17 -Wall -o linked_list main.cpp

clean:
	rm -f linked_list *~
