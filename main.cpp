#include "ft_containers.hpp"
#include <string>
#include "map.hpp"

int main()
{
    ft::map<int, std::string> test_map;

    // test_map.insert(ft::pair<int, std::string> (1, "one"));
    // std::cout << test_map[1] << std::endl;
    test_map[1] = "one";
    test_map[2] = "two";
    test_map[3] = "three";

    std::cout << "Size of the map: " << test_map.size() << std::endl;
    std::cout << "Value at key 1: " << test_map[1] << std::endl;
    std::cout << "Value at key 2: " << test_map[2] << std::endl;
    std::cout << "Value at key 3: " << test_map[3] << std::endl;

    return 0;
}