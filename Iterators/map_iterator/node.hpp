#pragma once
#include "../../ft_containers.hpp"

namespace ft {
    template<class Key, class T>
    class node {
        typedef ft::pair<key_type, T>       type_value;
        type_value      value;
        node            *right;
        node            *left;
        node            *parent;
    };
}

