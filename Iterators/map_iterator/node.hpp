#pragma once
#include "../../ft_containers.hpp"
#include "pair.hpp"

namespace ft {
/*███╗   ██╗     ██████╗     ██████╗     ███████╗
  ████╗  ██║    ██╔═══██╗    ██╔══██╗    ██╔════╝
  ██╔██╗ ██║    ██║   ██║    ██║  ██║    █████╗  
  ██║╚██╗██║    ██║   ██║    ██║  ██║    ██╔══╝  
  ██║ ╚████║    ╚██████╔╝    ██████╔╝    ███████╗
  ╚═╝  ╚═══╝     ╚═════╝     ╚═════╝     ╚══════*/
    template <typename K, typename T>
    class Node {
        typedef ft::pair<K, T>       type_value;

        type_value      val;
        int             height;
        Node*           left;
        Node*           right;
    
        // CONSTRUCTOR    
        Node(type_value v) : val(v), height(1), left(NULL), right(NULL) {}
        // Constructor for the nil leaf node
        Node() : val(), height(0), left(NULL), right(NULL) {}
    };
}