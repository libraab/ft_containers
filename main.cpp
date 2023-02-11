#include "vector.hpp"
#include <iostream>

int main()
{
    ft::vector<int> v;
    for (int i = 0; i < 400; i++)
        v.push_back(i);

    ft::vector::iterator it;
    for (it = v.begin(); it != v.end(); it++)
        std::cout << *it << std::endl;
    ft::vector::reverse_iterator rit;
    for (rit = v.rbegin(); rit != v.rend(); rit++)
        std::cout << *rit << std::endl;

}