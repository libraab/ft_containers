#pragma once
#include <iostream>
#include "../ft_containers.hpp"

namespace ft
{
    // generic definition ---> https://legacy.cplusplus.com/reference/iterator/iterator_traits/
    template <class Iterator> class iterator_traits {
        public:
        typedef typename 	Iterator::difference_type   difference_type;
        typedef typename	Iterator::value_type        value_type;
        typedef typename    Iterator::pointer	        pointer;
        typedef typename    Iterator::reference         reference;
        typedef typename    Iterator::iterator_category	iterator_category;
    };
    //=====================================================================================================================================
    // T* specialisation ---> https://legacy.cplusplus.com/reference/iterator/iterator_traits/
    template <class T> class iterator_traits<T*> {
        public:
        typedef typename    ptrdiff_t                   difference_type; // --> https://legacy.cplusplus.com/reference/cstddef/ptrdiff_t/
        typedef typename    T                           value_type;
        typedef typename    T*                          pointer;
        typedef typename    T&                          reference;
        typedef typename    random_access_iterator_tag  iterator_category; // --> https://legacy.cplusplus.com/reference/iterator/RandomAccessIterator/
    };
    //=====================================================================================================================================
    // const T* specialisation ---> https://legacy.cplusplus.com/reference/iterator/iterator_traits/
    template <class T> class iterator_traits<const T*> {
        public:
        typedef typename    ptrdiff_t                   difference_type;
        typedef typename    T                           value_type;
        typedef typename    T*                          pointer;
        typedef typename    T&                          reference;
        typedef typename    random_access_iterator_tag  iterator_category;
    };
    //=====================================================================================================================================
    template <class T> class random_access_iterator iterator : public iterator_traits{ // --> https://legacy.cplusplus.com/reference/iterator/RandomAccessIterator/
        public: 
        typedef typename    ptrdiff_t                   difference_type; // --> https://legacy.cplusplus.com/reference/iterator/iterator/
        typedef typename    T                           value_type;
        typedef typename    T*                          pointer;
        typedef typename    T&                          reference;
        typedef typename    random_access_iterator_tag  iterator_category;

        protected:
            pointer _ptr;

        public: 
        // --> https://en.cppreference.com/w/cpp/language/operators
        //======================================================================
        // Increment and decrement
        iterator& operator++() { // prefix increment
            _ptr++;
            return *this;
        }
        iterator operator++(int) { // postfix increment
            iterator old = *this;
            operator++();
            return old;
        }
        iterator& operator--() { // prefix decrement
            _ptr--;
            return *this;
        }
        iterator operator--(int) { // postfix decrement
            iterator old = *this;
            operator--();
            return old;
        }
        //======================================================================
        // Binary arithmetic operators
        iterator& operator+=(const iterator& rhs) {
            _ptr = _ptr + rhs;
            return *this;
        }
        iterator& operator-=(difference_type rhs) {
            _ptr = _ptr - rhs;
            return *this;
        }
        iterator operator+(difference_type rhs) const {
            return (iterator(_ptr + rhs));
        }
        iterator operator-(difference_type rhs) const {
            return (iterator(_ptr - rhs));
        }
        //======================================================================
        // comparison op
        bool operator< (const iterator& lhs, const iterator& rhs) { /* do actual comparison */ }
        bool operator> (const iterator& lhs, const iterator& rhs) { return rhs < lhs; }
        bool operator<=(const iterator& lhs, const iterator& rhs) { return !(lhs > rhs); }
        bool operator>=(const iterator& lhs, const iterator& rhs) { return !(lhs < rhs); }

        bool operator==(const iterator& lhs, const iterator& rhs) { return !(lhs != rhs); }
        bool operator!=(const iterator& lhs, const iterator& rhs) { return !(lhs == rhs); }

        bool operator==(const iterator& lhs, const iterator& rhs) { return cmp(lhs,rhs) == 0; }
        bool operator!=(const iterator& lhs, const iterator& rhs) { return cmp(lhs,rhs) != 0; }
        bool operator< (const iterator& lhs, const iterator& rhs) { return cmp(lhs,rhs) <  0; }
        bool operator> (const iterator& lhs, const iterator& rhs) { return cmp(lhs,rhs) >  0; }
        bool operator<=(const iterator& lhs, const iterator& rhs) { return cmp(lhs,rhs) <= 0; }
        bool operator>=(const iterator& lhs, const iterator& rhs) { return cmp(lhs,rhs) >= 0; }
        //======================================================================
        reference	operator*() const {return (*_ptr);}
        pointer		operator->() const {return (_ptr);}
        reference	operator[](difference_type index) const {return (_ptr[index]);}
    }; 
}