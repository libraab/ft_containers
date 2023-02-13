#include <iostream>
#include <map>
#include "ft_containers.hpp"

int main()
{
    ft::map<int, std::string> test_map;

    test_map[1] = "one";
    test_map[2] = "two";
    test_map[3] = "three";

    std::cout << "Size of the map: " << test_map.size() << std::endl;
    std::cout << "Value at key 1: " << test_map[1] << std::endl;
    std::cout << "Value at key 2: " << test_map[2] << std::endl;
    std::cout << "Value at key 3: " << test_map[3] << std::endl;

    return 0;
}