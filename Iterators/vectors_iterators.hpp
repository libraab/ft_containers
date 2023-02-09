#pragma once
#include <iostream>
#include <stddef.h>
#include "../ft_containers.hpp"

namespace ft
{
/*
██╗    ████████╗    ███████╗    ██████╗      █████╗     ████████╗     ██████╗     ██████╗ 
██║    ╚══██╔══╝    ██╔════╝    ██╔══██╗    ██╔══██╗    ╚══██╔══╝    ██╔═══██╗    ██╔══██╗
██║       ██║       █████╗      ██████╔╝    ███████║       ██║       ██║   ██║    ██████╔╝
██║       ██║       ██╔══╝      ██╔══██╗    ██╔══██║       ██║       ██║   ██║    ██╔══██╗
██║       ██║       ███████╗    ██║  ██║    ██║  ██║       ██║       ╚██████╔╝    ██║  ██║
╚═╝       ╚═╝       ╚══════╝    ╚═╝  ╚═╝    ╚═╝  ╚═╝       ╚═╝        ╚═════╝     ╚═╝  ╚═╝
                                                                                                           
    ████████╗    ██████╗      █████╗     ██╗    ████████╗    ███████╗                         
    ╚══██╔══╝    ██╔══██╗    ██╔══██╗    ██║    ╚══██╔══╝    ██╔════╝                         
       ██║       ██████╔╝    ███████║    ██║       ██║       ███████╗                         
       ██║       ██╔══██╗    ██╔══██║    ██║       ██║       ╚════██║                         
       ██║       ██║  ██║    ██║  ██║    ██║       ██║       ███████║                         
       ╚═╝       ╚═╝  ╚═╝    ╚═╝  ╚═╝    ╚═╝       ╚═╝       ╚══════╝ 
*/ 
    // generic definition ---> https://legacy.cplusplus.com/reference/iterator/iterator_traits/
    template <class Iterator> class iterator_traits {
        public:
        typedef typename 	Iterator::difference_type   difference_type;
        typedef typename	Iterator::value_type        value_type;
        typedef typename    Iterator::pointer	        pointer;
        typedef typename    Iterator::reference         reference;
        typedef typename    Iterator::iterator_category	iterator_category;
    };
    // T* specialisation ---> https://legacy.cplusplus.com/reference/iterator/iterator_traits/
    template <class T> class iterator_traits<T*> {
        public:
        typedef typename    ptrdiff_t                   difference_type; // --> https://legacy.cplusplus.com/reference/cstddef/ptrdiff_t/
        typedef typename    T                           value_type;
        typedef typename    T*                          pointer;
        typedef typename    T&                          reference;
        typedef typename    random_access_iterator_tag  iterator_category; // --> https://legacy.cplusplus.com/reference/iterator/RandomAccessIterator/
    };
    // const T* specialisation ---> https://legacy.cplusplus.com/reference/iterator/iterator_traits/
    template <class T> class iterator_traits<const T*> {
        public:
        typedef typename    ptrdiff_t                   difference_type;
        typedef typename    T                           value_type;
        typedef typename    T*                          pointer;
        typedef typename    T&                          reference;
        typedef typename    random_access_iterator_tag  iterator_category;
    };
/*
                ███╗   ███╗     █████╗     ██╗    ███╗   ██╗                                              
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
 ╚═╝       ╚═╝       ╚══════╝    ╚═╝  ╚═╝    ╚═╝  ╚═╝       ╚═╝        ╚═════╝     ╚═╝  ╚═╝
*/ 
    // general definition --> https://legacy.cplusplus.com/reference/iterator/iterator/
    template <class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
    class iterator {
        public: 
            typedef T         value_type;
            typedef Distance  difference_type;
            typedef Pointer   pointer;
            typedef Reference reference;
            typedef Category  iterator_category;
        
        protected:
            pointer _ptr;
        
        public: 
        //====================================================================//
        //        C O N S T R U C T O R S     &   D E S T R U C T O R         //
        //====================================================================//
        iterator(pointer _ptr)              : _ptr(ptr_t)       {return;}
        iterator()                          : _ptr(nullptr)     {return;}
        iterator(const iterator &copy)                          {*this = copy;}
        ~iterator() 
        //====================================================================//
        //          A S S I G N E M E N T   O P E R A T O R                   //
        //====================================================================//
        iterator &operator= (const iterator &rhs) {
            if (*this != rhs)
                this->_ptr = rhs._ptr;
            return (*this);
        }
        //====================================================================//
        //          C O N V E R S I O N     O P E R A T O R                   //
        //====================================================================//
        operator iterator<const T>() const { // convert the current instance from <T> to <const T>
            iterator<const T> tmp(this->_ptr); // necessary ?
            return (tmp);
        }
        //====================================================================//
        //              I N C R E M E N T  &   D E C R E M E N T              //
        //====================================================================//
        // --> https://en.cppreference.com/w/cpp/language/operators
        iterator& operator++() {        // prefix increment
            _ptr++;                     // same as this->_ptr++ but more concise
            return *this;
        }
        iterator operator++(int) {      // postfix increment
            iterator old = *this;
            ++(*this);
            return old;
        }
        iterator* operator++() {        // pointer increment
            _ptr = _ptr + sizeof(*_ptr);
            return *this;
        }
        iterator& operator--() {        // prefix decrement
            _ptr--;
            return *this;
        }
        iterator operator--(int) {      // postfix decrement
            iterator old = *this;
            --(*this);
            return old;
        }
        iterator* operator--() {        // pointer decrement
            _ptr = _ptr - sizeof(*_ptr);
            return *this;
        }
        //====================================================================//
        //        B I N A R Y   A R I T H M E T I C   O P E R A T O R S       //
        //====================================================================//
        iterator operator+ (difference_type rhs) const { // a + n 
            return (iterator(_ptr + rhs));
        }
        iterator operator- (difference_type rhs) const { // a - n 
            return (iterator(_ptr - rhs));
        }
        iterator& operator+= (difference_type& rhs) {
            *this = *this + rhs;
            return *this;
        }
        iterator& operator-= (difference_type rhs) {
            *this = *this - rhs;
            return *this;
        }
        //====================================================================//
        //         O V E R L O A D I N G     O P E R A T O R S                //   
        //====================================================================//
        reference   operator*() const                       {return (*this->_ptr);}
        pointer     operator->() const                      {return (this->_ptr);}
        reference   operator[](difference_type idx) const   {return (*(_ptr + idx));}

        // 👇🏻 to access the raw pointer that iterator is pointing to (direct access to the data) 👇🏻
        pointer     base() const                            {return (_ptr);}
    }; 
    //========================================================================//
    //           O P E R A T O R S        T E M P L A T E S                   //
    //========================================================================//
    // using class and tyoename as template parameters --> https://stackoverflow.com/questions/2023977/difference-of-keywords-typename-and-class-in-templates
    template <class T>
    std::ostream& operator<<(std::ostream& os, const ft::iterator<T>& rhs) {
        os << *rhs.base() ;
        return (os);
    }
    //--------------------------------------------------------------------------
    template <typename T> // n + a where a is object of iterator & n is value of its difference type
    iterator<T> operator+ (typename iterator<T>::difference_type lhs, const iterator<T> rhs) {
        return (lhs + rhs.base());
    }
    template <typename T> // n - a
    iterator<T> operator- (typename iterator<T>::difference_type lhs, const iterator<T> rhs) {
        return (lhs - rhs.base());
    }
    //--------------------------------------------------------------------------
    template <typename A, typename B> // a + b where a & b are object of iterator
    typename iterator<A>::difference_type operator+ (const iterator<A> lhs, const iterator<B> rhs) {
        return (lhs.base() + rhs.base());
    }
    template <typename A, typename B> // a - b 
    typename iterator<A>::difference_type operator- (const iterator<A> lhs, const iterator<B> rhs) {
        return (lhs.base() - rhs.base());
    }
    //========================================================================//
    //             C O M P A R I S O N   O P E R A T O R S                    //   
    //========================================================================//
    template <class A, class B>
    bool operator== (const iterator<A>& lhs, const iterator<B>& rhs) {return (lhs.base() == rhs.base());}

    template <class A, class B>
    bool operator!= (const iterator<A>& lhs, const iterator<B>& rhs) {return (lhs.base() != rhs.base());}

    template <class A, class B>
    bool operator< (const iterator<A>& lhs, const iterator<B>& rhs) {return (lhs.base() < rhs.base());}

    template <class A, class B>
    bool operator> (const iterator<A>& lhs, const iterator<B>& rhs) {return (lhs.base() > rhs.base());}

    template <class A, class B>
    bool operator<= (const iterator<A>& lhs, const iterator<B>& rhs) {return (lhs.base() <= rhs.base());}

    template <class A, class B>
    bool operator>= (const iterator<A>& lhs, const iterator<B>& rhs) {return (lhs.base() >= rhs.base());}

/*
 ██████╗     ███████╗    ██╗   ██╗    ███████╗    ██████╗     ███████╗    ███████╗                                     
 ██╔══██╗    ██╔════╝    ██║   ██║    ██╔════╝    ██╔══██╗    ██╔════╝    ██╔════╝                                     
 ██████╔╝    █████╗      ██║   ██║    █████╗      ██████╔╝    ███████╗    █████╗                                       
 ██╔══██╗    ██╔══╝      ╚██╗ ██╔╝    ██╔══╝      ██╔══██╗    ╚════██║    ██╔══╝                                       
 ██║  ██║    ███████╗     ╚████╔╝     ███████╗    ██║  ██║    ███████║    ███████╗                                     
 ╚═╝  ╚═╝    ╚══════╝      ╚═══╝      ╚══════╝    ╚═╝  ╚═╝    ╚══════╝    ╚══════╝                                     
                                                                                                                       
██╗    ████████╗    ███████╗    ██████╗      █████╗     ████████╗     ██████╗     ██████╗     ███████╗
██║    ╚══██╔══╝    ██╔════╝    ██╔══██╗    ██╔══██╗    ╚══██╔══╝    ██╔═══██╗    ██╔══██╗    ██╔════╝
██║       ██║       █████╗      ██████╔╝    ███████║       ██║       ██║   ██║    ██████╔╝    ███████╗
██║       ██║       ██╔══╝      ██╔══██╗    ██╔══██║       ██║       ██║   ██║    ██╔══██╗    ╚════██║
██║       ██║       ███████╗    ██║  ██║    ██║  ██║       ██║       ╚██████╔╝    ██║  ██║    ███████║
╚═╝       ╚═╝       ╚══════╝    ╚═╝  ╚═╝    ╚═╝  ╚═╝       ╚═╝        ╚═════╝     ╚═╝  ╚═╝    ╚══════╝
*/

    template <class Iterator>
    class reverse_iterator : public iterator_traits<T> {
        public:
            typedef Iterator                                                    iterator_type;

            typedef typename ft::iterator_traits<Iterator>::difference_type     difference_type;
            typedef typename ft::iterator_traits<Iterator>::value_type          value_type;
            typedef typename ft::iterator_traits<Iterator>::pointer             pointer;
            typedef typename ft::iterator_traits<Iterator>::reference           reference;
            typedef typename ft::iterator_traits<Iterator>::iterator_category   iterator_category;
        
        private:
            iterator_type   _it;
        
        public:
        //====================================================================//
        //        C O N S T R U C T O R S     &   D E S T R U C T O R         //
        //====================================================================//
        reverse_iterator (void)                     : _it(0)      {return;}
        explicit reverse_iterator (Iterator i)      : _it(i - 1)  {return;}
        // 👆🏻 explicit = used for only direct initioalisation, no implicit conversion
        // no destructor needed cause it doesn't own any resources that need to be cleaned up (no dynamically allocated memory, nofile handles, no sockets ...)
        //====================================================================//
        //          A S S I G N E M E N T   O P E R A T O R                   //
        //====================================================================//
        reverse_iterator &operator= (const reverse_iterator &rhs) { // same thing as general iterator l65
            if (*this != rhs)
                this->_it = rhs._it;
            return (*this);
        }
        //====================================================================//
        //              I N C R E M E N T  &   D E C R E M E N T              //
        //====================================================================//
        reverse_iterator& operator++() {       
            _it--;               
            return *this;
        }
        reverse_iterator& operator--() { 
            _it++;
            return *this;
        }
        reverse_iterator operator++(int) {     
            reverse_iterator old = *this;
            ++(*this);
            return old;
        }
        reverse_iterator operator--(int) {   
            reverse_iterator old = *this;
            --(*this);
            return old;
        }
        //====================================================================//
        //        B I N A R Y   A R I T H M E T I C   O P E R A T O R S       //
        //====================================================================//
        reverse_iterator operator+ (difference_type rhs) const { // a + n 
            return (reverse_iterator(base() - rhs));
        }
        reverse_iterator operator- (difference_type rhs) const { // a - n 
            return (reverse_iterator(base() + rhs));
        }
        reverse_iterator& operator+= (difference_type rhs) {
            *this = *this - rhs;
            return *this;
        }
        reverse_iterator& operator-= (difference_type rhs) {
            *this = *this + rhs;
            return *this;
        }
        //====================================================================//
        //         O V E R L O A D I N G     O P E R A T O R S                //   
        //====================================================================//
        reference   operator*() const                       {return (*this->_it);}
        pointer     operator->() const                      {return (_it.operator->());}
        reference   operator[](difference_type idx) const   {return (*(_it - idx));}

        // 👇🏻 to access the raw pointer that iterator is pointing to (direct access to the data) for the templates👇🏻
        iterator_type     base() const                      {return (_it + 1);}
    
        template <class A> // <--- ??
        reverse_iterator (const reverse_iterator<A>& i) : _iterator(i.base() - 1) {return;}
    };
    //========================================================================//
    //     R E V E R S E   O P E R A T O R S    T E M P L A T E S             //
    //========================================================================//
    template <class T> 
    reverse_iterator<T> operator+ (const reverse_iterator<T>& lhs, typename reverse_iterator<T>::difference_type rhs) {
        return (reverse_iterator<T> (lhs.base() - rhs));
    }
    template <class T> 
    reverse_iterator<T> operator- (const reverse_iterator<T>& lhs, typename reverse_iterator<T>::difference_type rhs) {
        return (reverse_iterator<T> (lhs.base() + rhs));
    }
    //--------------------------------------------------------------------------
    template <typename A, typename B> // same
    typename reverse_iterator<A>::difference_type operator+ (const reverse_iterator<A>& lhs, const reverse_iterator<B>& rhs) {
        return (lhs.base() + rhs.base());
    }
    template <typename A, typename B> 
    typename reverse_iterator<A>::difference_type operator- (const reverse_iterator<A>& lhs, const reverse_iterator<B>& rhs) {
        return (lhs.base() - rhs.base()); // same
    }
    //========================================================================//
    //             C O M P A R I S O N   O P E R A T O R S                    //   
    //========================================================================//
    template <class A, class B> // same
    bool operator== (const reverse_iterator<A>& lhs, const reverse_iterator<B>& rhs) {
        return (lhs.base() == rhs.base());}

    template <class A, class B> // same
    bool operator!= (const reverse_iterator<A>& lhs, const reverse_iterator<B>& rhs) {
        return (lhs.base() != rhs.base());}
    //--------------------------------------------------------------------------
    template <class A, class B> // reverse
    bool operator< (const reverse_iterator<A>& lhs, const reverse_iterator<B>& rhs) {
        return (lhs.base() > rhs.base());}

    template <class A, class B> // reverse
    bool operator> (const reverse_iterator<A>& lhs, const reverse_iterator<B>& rhs) {
        return (lhs.base() < rhs.base());}

    template <class A, class B> // reverse
    bool operator<= (const reverse_iterator<A>& lhs, const reverse_iterator<B>& rhs) {
        return (lhs.base() >= rhs.base());}

    template <class A, class B> // reverse
    bool operator>= (const reverse_iterator<A>& lhs, const reverse_iterator<B>& rhs) {
        return (lhs.base() <= rhs.base());}
}