#pragma once
#include <iostream>
#include <stddef.h>
#include "../ft_containers.hpp"

namespace ft
{
/*██╗    ████████╗    ███████╗    ██████╗      █████╗     ████████╗     ██████╗     ██████╗ 
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
       ╚═╝       ╚═╝  ╚═╝    ╚═╝  ╚═╝    ╚═╝       ╚═╝       ╚══════*/ 

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
        typedef     ptrdiff_t                   difference_type; // --> https://legacy.cplusplus.com/reference/cstddef/ptrdiff_t/
        typedef     T                           value_type;
        typedef     T*                          pointer;
        typedef     T&                          reference;
        typedef     random_access_iterator_tag  iterator_category; // --> https://legacy.cplusplus.com/reference/iterator/RandomAccessIterator/
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

/*████████╗    ██╗   ██╗    ██████╗     ███████╗            ████████╗    ██████╗      █████╗     ██╗    ████████╗    ███████╗
  ╚══██╔══╝    ╚██╗ ██╔╝    ██╔══██╗    ██╔════╝            ╚══██╔══╝    ██╔══██╗    ██╔══██╗    ██║    ╚══██╔══╝    ██╔════╝
     ██║        ╚████╔╝     ██████╔╝    █████╗                 ██║       ██████╔╝    ███████║    ██║       ██║       ███████╗
     ██║         ╚██╔╝      ██╔═══╝     ██╔══╝                 ██║       ██╔══██╗    ██╔══██║    ██║       ██║       ╚════██║
     ██║          ██║       ██║         ███████╗               ██║       ██║  ██║    ██║  ██║    ██║       ██║       ███████║
     ╚═╝          ╚═╝       ╚═╝         ╚══════╝               ╚═╝       ╚═╝  ╚═╝    ╚═╝  ╚═╝    ╚═╝       ╚═╝       ╚══════*/
	
    //========================================================================//
    //                       E N A B L E       I F                            //
    //========================================================================//
    template <bool B, class T = void>
    struct enable_if {};

    template <class T>
    struct enable_if<true, T> {typedef T type;};
    //========================================================================//
    //                        I S     I N T E G R A L                         //
    //========================================================================//
    // --> https://cplusplus.com/reference/type_traits/is_integral/?kw=is_integral
    // main
    template <typename T>
    struct is_integral
    { static const bool value = false; };

    // specialisation
    template <>
    struct is_integral<bool>
    { static const bool value = true; };
    template <>
    struct is_integral<char>
    { static const bool value = true; };
    template <>
    struct is_integral<char16_t>
    { static const bool value = true; };
    template <>
    struct is_integral<char32_t>
    { static const bool value = true; };
    template <>
    struct is_integral<wchar_t>
    { static const bool value = true; };
    template <>
    struct is_integral<signed char>
    { static const bool value = true; };
    template <>
    struct is_integral<short int>
    { static const bool value = true; };
    template <>
    struct is_integral<int>
    { static const bool value = true; };
    template <>
    struct is_integral<long int>
    { static const bool value = true; };
    template <>
    struct is_integral<long long int>
    { static const bool value = true; };
    template <>
    struct is_integral<unsigned char>
    { static const bool value = true; };
    template <>
    struct is_integral<unsigned short int>
    { static const bool value = true; };
    template <>
    struct is_integral<unsigned int>
    { static const bool value = true; };
    template <>
    struct is_integral<unsigned long int>
    { static const bool value = true; };
    template <>
    struct is_integral<unsigned long long int>
    { static const bool value = true; };
    //========================================================================//
    //                              E Q U A L                                 //
    //========================================================================//
    // litteraly --> https://cplusplus.com/reference/algorithm/equal/
	template <class InputIterator1, class InputIterator2>
    bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
    {
        while (first1 != last1) {
            if (!(*first1 == *first2))   // or: if (!pred(*first1,*first2)), for version 2
                return false;
            ++first1; ++first2;
        }
        return true;
    }
    //========================================================================//
    //       L E X I C O G R A P H I C A L           C O M P A R E            //
    //========================================================================//
    // litteraly --> https://cplusplus.com/reference/algorithm/lexicographical_compare/
    template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1) {
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			++first1; ++first2;
		}
		return (first2 != last2);
	}
}