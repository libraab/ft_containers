#pragma once
#include "../../ft_containers.hpp"
#include "iterator_traits.hpp"

namespace ft
{
/*██████╗     ███████╗    ██╗   ██╗    ███████╗    ██████╗     ███████╗    ███████╗                                     
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
╚═╝       ╚═╝       ╚══════╝    ╚═╝  ╚═╝    ╚═╝  ╚═╝       ╚═╝        ╚═════╝     ╚═╝  ╚═╝    ╚══════*/
    template <class Iterator>
    class reverse_iterator 
    {
        public:
            typedef Iterator                                                    iterator_type;
            typedef typename ft::iterator_traits<Iterator>::difference_type         difference_type;
            typedef typename ft::iterator_traits<Iterator>::value_type              value_type;
            typedef typename iterator_traits<Iterator>::pointer                 pointer;
            typedef typename iterator_traits<Iterator>::reference               reference;
            typedef typename iterator_traits<Iterator>::iterator_category       iterator_category;
        
        private:
            iterator_type   _it;
        
        public:
        //====================================================================//
        //        C O N S T R U C T O R S     &   D E S T R U C T O R         //
        //====================================================================//
        reverse_iterator()                                  :_it(iterator_type()) {}
        explicit reverse_iterator(iterator_type it)          :_it(it) {}
        // 👆🏻 explicit = used for only direct initioalisation, no implicit conversion
        template <class Rev>
        reverse_iterator(const reverse_iterator<Rev>& it)  :_it(it.base()) {}
        // no destructor needed cause it doesn't own any resources that need to be cleaned up
        // (no dynamically allocated memory, nofile handles, no sockets ...)
        //====================================================================//
        //          A S S I G N E M E N T   O P E R A T O R                   //
        //====================================================================//
        template <class A>
        reverse_iterator &operator= (const reverse_iterator<A>& rhs) { // same thing as general iterator l65
            if (*this != rhs)
                _it = rhs.base();
            return *this;
        }
        // 👇🏻 to access the raw pointer that iterator is pointing to (direct access to the data) for the templates👇🏻
        iterator_type     base() const                      {return _it;}
        //====================================================================//
        //              I N C R E M E N T  &   D E C R E M E N T              //
        //====================================================================//
        reverse_iterator& operator++() {       
            _it--;               
            return *this;}
        reverse_iterator& operator--() { 
            _it++;
            return *this;}
        reverse_iterator operator++(int) {     
            reverse_iterator old = *this;
            ++(*this);
            return old;}
        reverse_iterator operator--(int) {   
            reverse_iterator old = *this;
            --(*this);
            return old;}
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
        //       D E R E F E R E N C E R I N G       O P E R A T O R S        //   
        //====================================================================//
        reference   operator*() const                       {return *_it;}
        pointer     operator->() const                      { return &(*_it); }
        // subscript operator
        reference   operator[](difference_type n) const   {return (*(_it - n));}
    };
    //========================================================================//
    //     R E V E R S E   O P E R A T O R S    T E M P L A T E S             //
    //========================================================================//
    template <class T>
	reverse_iterator<T> operator+ (typename reverse_iterator<T>::difference_type n, const reverse_iterator<T>& rhs) {
		return (rhs + n);
	}

	template <class A, class B>
	typename reverse_iterator<A>::difference_type operator-(const reverse_iterator<A>& lhs, const reverse_iterator<B>& rhs) {
		return (rhs.base() - lhs.base());
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