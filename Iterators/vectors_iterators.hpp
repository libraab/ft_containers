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
        //======================================================================
        // A S S I G N E M E N T   O P E R A T O R
        // copy assignment
        reference operator=(const reference other)
        {
            // Guard self assignment 
            // (The canonical copy-assignment operator is expected to perform no action on self-assignment, and to return the lhs by reference)
            if (this == &other)
                return *this;
            // assume *this manages a reusable resource, such as a heap-allocated buffer mArray
            if (sizeof(_ptr) != sizeof(other))           // if resource in *this cannot be reused
            {
                delete[] _ptr;                           // release resource in *this of the current instance
                _ptr = nullptr;
                sizeof(_ptr) = 0;                       // preserve invariants in case next line throws (security)
                _ptr = new int[sizeof(other)];          // allocate resource in *this
                sizeof(_ptr) = sizeof(other);
            } 
            std::copy(other._ptr, other._ptr + sizeof(other), _ptr);
            return *this;
        }
        //---------------------------------------------------------------------
        // move assignment
        reference operator=(reference& other) noexcept
        {
            // Guard self assignment
            if (this == &other)
                return *this; // delete[]/size=0 would also be ok
        
            delete[] _ptr;                                  // release resource in *this
            _ptr = std::exchange(other._ptr, nullptr);      // leave other in valid state
            sizeof(_ptr) = std::exchange(sizeof(other), 0);
            return *this;
        }
        //---------------------------------------------------------------------
        // copy assignment (copy-and-swap idiom)
        reference value_type::operator=(value_type other) noexcept // call copy or move constructor to construct other
        {
            std::swap(sizeof(_ptr), sizeof(other)); // exchange resources between *this and other
            std::swap(_ptr, other._ptr);
            return *this;
        } // destructor of other is called to release the resources formerly managed by *this
        //======================================================================


        // --> https://en.cppreference.com/w/cpp/language/operators
        // I N C R E M E N T  &   D E C R E M E N T 
        iterator& operator++() { // prefix increment
            _ptr++; /* actual incrementation */
            return *this;
        }
        iterator operator++(int) { // postfix increment
            iterator old = *this;
            operator++();
            return old;
        }
        iterator* operator++() { // pointer increment
            pointer = pointer + sizeof(*pointer);
            // OR      (*_ptr)++;
            return *this;
        }
        //-------------------------------------------
        iterator& operator--() { // prefix decrement
            _ptr--;
            return *this;
        }
        iterator operator--(int) { // postfix decrement
            iterator old = *this;
            operator--();
            return old;
        }
        iterator* operator--() { // pointer decrement
            pointer = pointer - sizeof(*pointer);
            // OR      (*_ptr)--;
            return *this;
        }
        //======================================================================
        // B I N A R Y   A R I T H M E T I C   O P E R A T O R S
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
        // C O M P A R I S O N   O P ER A T O R 
        bool operator< (const iterator& lhs, const iterator& rhs) { return rhs > lhs; }
        bool operator> (const iterator& lhs, const iterator& rhs) { return rhs < lhs; }
        bool operator<=(const iterator& lhs, const iterator& rhs) { return !(lhs > rhs); }
        bool operator>=(const iterator& lhs, const iterator& rhs) { return !(lhs < rhs); }

        bool operator==(const iterator& lhs, const iterator& rhs) { return !(lhs != rhs); } 
        bool operator!=(const iterator& lhs, const iterator& rhs) { return !(lhs == rhs); }

        //======================================================================
        reference   operator*() const {return (*_ptr);}
        pointer     operator->() const {return (_ptr);}
        //reference   operator[](difference_type index) const {return (_ptr[index]);}
        reference           operator[](difference_type idx)       { return _ptr[idx]; }
        const reference     operator[](difference_type idx) const { return _ptr[idx]; }         
        }
    }; 
}

/*

X a;
X b(a);
b = a; ✅

a == b ✅
a != b ✅

*a ✅
a->m ✅

*a = t ✅

++a ✅
a++ ✅
*a++ ✅

--a ✅
a-- ✅
*a-- ✅

a + n ✅
n + a
a - n ✅
a - b

a < b ✅
a > b ✅
a <= b ✅
a >= b ✅

a += n ✅
a -= n ✅

a[n] ✅

*/