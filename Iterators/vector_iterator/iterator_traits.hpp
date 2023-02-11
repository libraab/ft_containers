#pragma once
#include <cstddef>
#include "../../ft_containers.hpp"

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
    class random_access_iterator_tag {};
    // general definition --> https://legacy.cplusplus.com/reference/iterator/iterator/
    template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
    class iterator {
        public: 
            typedef T         value_type;
            typedef Distance  difference_type;
            typedef Pointer   pointer;
            typedef Reference reference;
            typedef Category iterator_category;
    };
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
        typedef     ptrdiff_t                   difference_type;
        typedef     T                           value_type;
        typedef     T*                          pointer;
        typedef     T&                          reference;
        typedef     random_access_iterator_tag  iterator_category;
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
    class reverse_iterator 
    {
        public:
            typedef Iterator                                                    iterator_type;
            typedef typename iterator_traits<Iterator>::difference_type         difference_type;
            typedef typename iterator_traits<Iterator>::value_type              value_type;
            typedef typename iterator_traits<Iterator>::pointer                 pointer;
            typedef typename iterator_traits<Iterator>::reference               reference;
            typedef typename iterator_traits<Iterator>::iterator_category       iterator_category;
        
        private:
            iterator_type   _it;
        
        public:
        //====================================================================//
        //        C O N S T R U C T O R S     &   D E S T R U C T O R         //
        //====================================================================//
        reverse_iterator(void)                                  :_it(iterator_type()) {}
        explicit reverse_iterator(iterator_type it)             :_it(it) {}
        // 👆🏻 explicit = used for only direct initioalisation, no implicit conversion
        template <class Rev>
        reverse_iterator(const reverse_iterator<Rev>& it)  :_it(_it.base()) {}
        // no destructor needed cause it doesn't own any resources that need to be cleaned up
        // (no dynamically allocated memory, nofile handles, no sockets ...)
        //====================================================================//
        //          A S S I G N E M E N T   O P E R A T O R                   //
        //====================================================================//
        template <class A>
        reverse_iterator &operator= (const reverse_iterator<A>& rhs) { // same thing as general iterator l65
            if (*this != rhs)
                this->_it = rhs._it;
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

  /*██████╗      █████╗     ███╗   ██╗    ██████╗      ██████╗     ███╗   ███╗                
    ██╔══██╗    ██╔══██╗    ████╗  ██║    ██╔══██╗    ██╔═══██╗    ████╗ ████║                
    ██████╔╝    ███████║    ██╔██╗ ██║    ██║  ██║    ██║   ██║    ██╔████╔██║                
    ██╔══██╗    ██╔══██║    ██║╚██╗██║    ██║  ██║    ██║   ██║    ██║╚██╔╝██║                
    ██║  ██║    ██║  ██║    ██║ ╚████║    ██████╔╝    ╚██████╔╝    ██║ ╚═╝ ██║                
    ╚═╝  ╚═╝    ╚═╝  ╚═╝    ╚═╝  ╚═══╝    ╚═════╝      ╚═════╝     ╚═╝     ╚═╝                
                                                                                            
             █████╗      ██████╗    ███████╗    ███████╗    ███████╗                                  
            ██╔══██╗    ██╔════╝    ██╔════╝    ██╔════╝    ██╔════╝                                  
            ███████║    ██║         █████╗      ███████╗    ███████╗                                  
            ██╔══██║    ██║         ██╔══╝      ╚════██║    ╚════██║                                  
            ██║  ██║    ╚██████╗    ███████╗    ███████║    ███████║                                  
            ╚═╝  ╚═╝     ╚═════╝    ╚══════╝    ╚══════╝    ╚══════╝                                  
                                                                                            
    ██╗    ████████╗    ███████╗    ██████╗      █████╗     ████████╗     ██████╗     ██████╗ 
    ██║    ╚══██╔══╝    ██╔════╝    ██╔══██╗    ██╔══██╗    ╚══██╔══╝    ██╔═══██╗    ██╔══██╗
    ██║       ██║       █████╗      ██████╔╝    ███████║       ██║       ██║   ██║    ██████╔╝
    ██║       ██║       ██╔══╝      ██╔══██╗    ██╔══██║       ██║       ██║   ██║    ██╔══██╗
    ██║       ██║       ███████╗    ██║  ██║    ██║  ██║       ██║       ╚██████╔╝    ██║  ██║
    ╚═╝       ╚═╝       ╚══════╝    ╚═╝  ╚═╝    ╚═╝  ╚═╝       ╚═╝        ╚═════╝     ╚═╝  ╚═*/ 

    // general definition --> https://legacy.cplusplus.com/reference/iterator/iterator/
    template <typename T>
    class random_access_iterator : public iterator<random_access_iterator_tag, T> {
        public: 
        	typedef typename iterator<random_access_iterator_tag, T>::value_type        value_type;
			typedef typename iterator<random_access_iterator_tag, T>::difference_type   difference_type;
			typedef typename iterator<random_access_iterator_tag, T>::pointer           pointer;
			typedef typename iterator<random_access_iterator_tag, T>::reference         reference;
			typedef typename iterator<random_access_iterator_tag, T>::Category          iterator_category;
        
        protected:
            pointer _ptr;

        public: 
        //====================================================================//
        //        C O N S T R U C T O R S     &   D E S T R U C T O R         //
        //====================================================================//
        random_access_iterator(pointer pointer)                         :_ptr(pointer)      {}
        random_access_iterator()                                        :_ptr(nullptr)      {}
        random_access_iterator(const random_access_iterator<T>& copy)   :_ptr(copy._ptr)    {}
        ~random_access_iterator() {}

        operator random_access_iterator<const value_type>() const  // ---> lazem ?
		{return random_access_iterator<const value_type>(_ptr);}

        pointer base() const    {return _ptr;}
        //====================================================================//
        //          A S S I G N E M E N T   O P E R A T O R                   //
        //====================================================================//
        random_access_iterator& operator= (const random_access_iterator& rhs) {
            if (*this != rhs) // or (this != &rhs)
                this->_ptr = rhs._ptr;
            return *this;
		}
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
        random_access_iterator operator+(difference_type n)const    {return (_ptr + n);}
		random_access_iterator operator-(difference_type n)const    {return (_ptr - n);}
        //====================================================================//
        //       D E R E F E R E N C E R I N G       O P E R A T O R S        //   
        //====================================================================//
        reference operator*() const                             { return *_ptr; }
        pointer operator->() const                              { return &(*_ptr); }
        // subscript operator
        reference operator[](difference_type n) const           { return *(_ptr + n); }
        //====================================================================//
        //  C O M P O U N D      A S S I G N M E N T      O P E R A T O R S   //   
        //====================================================================//
        random_access_iterator& operator+=(difference_type n) { _ptr += n; return *this; }
        random_access_iterator& operator-=(difference_type n) { _ptr -= n; return *this; }        
    };
    //========================================================================//
    // R A N D O M   A C C E S S    O P E R A T O R S    T E M P L A T E S    //
    //========================================================================//
    template <typename A>
	random_access_iterator<A> operator+ (typename random_access_iterator<A>::difference_type n, const random_access_iterator<A>& rhs) {
		return (rhs + n);
	}

	template <typename A, typename B>
	typename random_access_iterator<A>::difference_type operator-(const random_access_iterator<A>& lhs, const random_access_iterator<B>& rhs) {
		return (rhs.base() - lhs.base());
	}
    //========================================================================//
    //             C O M P A R I S O N   O P E R A T O R S                    //   
    //========================================================================//
    template <typename C, typename D> // same
    bool operator== (const random_access_iterator<C>& lhs, const random_access_iterator<D>& rhs) {
        return (lhs.base() == rhs.base());}
    template <typename C, typename D> // same
    bool operator!= (const random_access_iterator<C>& lhs, const random_access_iterator<D>& rhs) {
        return (lhs.base() != rhs.base());}
    template <typename C, typename D> // reverse
    bool operator< (const random_access_iterator<C>& lhs, const random_access_iterator<D>& rhs) {
        return (lhs.base() > rhs.base());}
    template <typename C, typename D> // reverse
    bool operator> (const random_access_iterator<C>& lhs, const random_access_iterator<D>& rhs) {
        return (lhs.base() < rhs.base());}
    template <typename C, typename D> // reverse
    bool operator<= (const random_access_iterator<C>& lhs, const random_access_iterator<D>& rhs) {
        return (lhs.base() >= rhs.base());}
    template <typename C, typename D> // reverse
    bool operator>= (const random_access_iterator<C>& lhs, const random_access_iterator<D>& rhs) {
        return (lhs.base() <= rhs.base());}
}