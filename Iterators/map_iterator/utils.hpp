#pragma once
#include "../../ft_containers.hpp"

namespace ft {
    // --> https://cplusplus.com/reference/utility/pair/
    template <class T1, class T2>
    struct pair {
        // --> https://www.oreilly.com/library/view/c-in-a/059600298X/re854.html
        typedef T1 first_type;
        typedef T2 second_type;
        T1 first;
        T2 second;
        pair() : first(T1()), second(T2()) {} // rarely used
        pair(const T1& x, const T2& y) : first(x), second(y) {}
        template<typename U, typename V>
        pair(const pair<U, V> &p) : first(p.first), second(p.second) {}
        //-----------------------------------------
        // added to official
        pair& operator=(const pair &x) {
            this->first = x.first;
            this->second = x.second;
            return *this;
        }
    };
    //========================================================================//
    // --> https://cplusplus.com/reference/utility/make_pair/
    template <class T1,class T2>
    ft::pair<T1,T2>     make_pair(T1 x, T2 y) {
        return (pair<T1,T2>(x,y));
    }
    struct Node {
    typedef ft::pair<key_type, T>       type_value;
    type_value      val;
    int             height;
    Node*           left;
    Node*           right;
    
    Node(int v) { // TO DO initiate empty pointer of node (ask Dan) 
        val = v;
        height = 1;
        left = NULL;
        right = NULL; } };
}