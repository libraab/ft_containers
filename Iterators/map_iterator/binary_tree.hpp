#pragma once
#include "../../ft_containers.hpp"
#include "node.hpp"

namespace ft {
    template<class T, class Key, class compare, class Alloc>
    class binary_tree {
        public:
        private:
    };
    //===============================================
    // --> https://cplusplus.com/reference/utility/pair/
    template <class T1, class T2>
    struct pair {
        // --> https://www.oreilly.com/library/view/c-in-a/059600298X/re854.html
        typedef T1 first_type;
        typedef T2 second_type;
        T1 first;
        T2 second;
        pair() : first(0), second(0) {} 
        pair(const T1& x, const T2& y) : first(x), second(0) {}
        template<typename U, typename V>
        pair(const pair<U, V> &p) : first(p.first), second(p.second) {}
    };
    //===============================================
    // --> https://cplusplus.com/reference/utility/make_pair/
    template <class T1,class T2>
    ft::pair<T1,T2> make_pair (T1 x, T2 y)
    { return ( pair<T1,T2>(x,y) ); }
}