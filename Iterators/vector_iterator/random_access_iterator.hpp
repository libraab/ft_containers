#pragma once
#include "../../ft_containers.hpp"
#include "iterator_traits.hpp"

              /*███╗   ███╗     █████╗     ██╗    ███╗   ██╗                                              
                ████╗ ████║    ██╔══██╗    ██║    ████╗  ██║                                              
                ██╔████╔██║    ███████║    ██║    ██╔██╗ ██║                                              
                ██║╚██╔╝██║    ██╔══██║    ██║    ██║╚██╗██║                                              
                ██║ ╚═╝ ██║    ██║  ██║    ██║    ██║ ╚████║                                              
                ╚═╝     ╚═╝    ╚═╝  ╚═╝    ╚═╝    ╚═╝  ╚═══╝                                              
                                                                                           
 ██╗    ████████╗    ███████╗    ██████╗      █████╗     ████████╗     ██████╗     ██████╗ 
 ██║    ╚══██╔══╝    ██╔════╝    ██╔══██╗    ██╔══██╗    ╚══██╔══╝    ██╔═══██╗    ██╔══██╗
 ██║       ██║       █████╗      ██████╔╝    ███████║       ██║       ██║   ██║    ██████╔╝
 ██║       ██║       ██╔══╝      ██╔══██╗    ██╔══██║       ██║       ██║   ██║    ██╔══██╗
 ██║       ██║       ███████╗    ██║  ██║    ██║  ██║       ██║       ╚██████╔╝    ██║  ██║
 ╚═╝       ╚═╝       ╚══════╝    ╚═╝  ╚═╝    ╚═╝  ╚═╝       ╚═╝        ╚═════╝     ╚═╝  ╚═*/ 
namespace ft
{
    // general definition --> https://legacy.cplusplus.com/reference/iterator/iterator/
    template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
    class iterator {
        public: 
            typedef T               value_type;
            typedef Distance        difference_type;
            typedef Pointer         pointer;
            typedef Reference       reference;
            typedef Category        iterator_category;
        
        protected:
            pointer _ptr;

        public: 
        //====================================================================//
        //        C O N S T R U C T O R S     &   D E S T R U C T O R         //
        //====================================================================//
        iterator(pointer pointer)           : _ptr(pointer)     {return;}
        iterator()                          : _ptr(nullptr)     {return;}
        iterator(const iterator &copy)                          {*this = copy;}
        ~iterator();
        //====================================================================//
        //              I N C R E M E N T  &   D E C R E M E N T              //
        //====================================================================//
        // --> https://en.cppreference.com/w/cpp/language/operators
        random_access_iterator& operator++()        { ++_ptr; return *this; }
        random_access_iterator operator++(int)      { random_access_iterator temp(*this); ++_ptr; return temp; }
        random_access_iterator& operator--()        { --_ptr; return *this; }
        random_access_iterator operator--(int)      { random_access_iterator temp(*this); --_ptr; return temp; }
        //====================================================================//
        //        B I N A R Y   A R I T H M E T I C   O P E R A T O R S       //
        //====================================================================//
        random_access_iterator operator+(difference_type n) const                               { return random_access_iterator(_ptr + n); }
        random_access_iterator operator+(difference_type n, const random_access_iterator& it)   { return _ptr + n; }
        random_access_iterator operator-(difference_type n) const                               { return random_access_iterator(_ptr - n); }
        difference_type operator-(const random_access_iterator& rhs) const                      { return _ptr - rhs._ptr; }
        //====================================================================//
        //         O V E R L O A D I N G     O P E R A T O R S                //   
        //====================================================================//
        reference operator*() const                             { return *_ptr; }
        pointer operator->() const                              { return &(*_ptr); }
        // subscript operator
        reference operator[](difference_type n) const           { return *(it + n); }
        //====================================================================//
        //             C O M P A R I S O N   O P E R A T O R S                //   
        //====================================================================//
        bool operator==(const random_access_iterator_tag& rhs) const { return _ptr == rhs._ptr; }
        bool operator!=(const random_access_iterator_tag& rhs) const { return _ptr != rhs._ptr; }
        bool operator<(const random_access_iterator_tag& rhs) const { return _ptr < rhs._ptr; }
        bool operator>(const random_access_iterator_tag& rhs) const { return _ptr > rhs._ptr; }
        bool operator<=(const random_access_iterator_tag& rhs) const { return _ptr <= rhs._ptr; }
        bool operator>=(const random_access_iterator_tag& rhs) const { return _ptr >= rhs._ptr; }
        //====================================================================//
        //  C O M P O U N D      A S S I G N M E N T      O P E R A T O R S   //   
        //====================================================================//
        random_access_iterator& operator+=(difference_type n) { _ptr += n; return *this; }
        random_access_iterator& operator-=(difference_type n) { _ptr -= n; return *this; }        
    };
}