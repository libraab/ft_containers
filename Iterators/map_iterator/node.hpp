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
    template <typename T>
    class Node {
        typedef ft::pair<key_type, T>       type_value;

        type_value      val;
        int             height;
        Node*           left;
        Node*           right;
    
        // CONSTRUCTOR    
        Node(type_value v) : val(v), height(1), left(NULL), right(NULL) {}
        // TO DO initiate empty pointer of node (ask Dan) 
    };
}