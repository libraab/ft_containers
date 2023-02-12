#pragma once
#include "../../ft_containers.hpp"
#include "iterator_traits.hpp"

namespace ft
{
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
    class random_access_iterator_tag
    {
    public:
        typedef typename iterator<random_access_iterator_tag, T>::value_type value_type;
        typedef typename iterator<random_access_iterator_tag, T>::difference_type difference_type;
        typedef typename iterator<random_access_iterator_tag, T>::pointer pointer;
        typedef typename iterator<random_access_iterator_tag, T>::reference reference;
        typedef typename iterator<random_access_iterator_tag, T>::iterator_category iterator_category;

    protected:
        pointer _ptr;

    public:
        //====================================================================//
        //        C O N S T R U C T O R S     &   D E S T R U C T O R         //
        //====================================================================//
        random_access_iterator_tag(pointer pointer)                             :_ptr(pointer) {}
        random_access_iterator_tag()                                            :_ptr(nullptr) {}
        random_access_iterator_tag(const random_access_iterator_tag<T> &copy)   :_ptr(copy._ptr) {}
        ~random_access_iterator_tag() {}

        operator random_access_iterator_tag<const value_type>() const // ---> lazem ?
        {
            return random_access_iterator_tag<const value_type>(_ptr);
        }

        pointer base() const { return _ptr; }
        //====================================================================//
        //          A S S I G N E M E N T   O P E R A T O R                   //
        //====================================================================//
        random_access_iterator_tag &operator=(const random_access_iterator_tag &rhs)
        {
            if (*this != rhs) // or (this != &rhs)
                this->_ptr = rhs._ptr;
            return *this;
        }
        //====================================================================//
        //              I N C R E M E N T  &   D E C R E M E N T              //
        //====================================================================//
        // --> https://en.cppreference.com/w/cpp/language/operators
        random_access_iterator_tag &operator++()
        {
            ++_ptr;
            return *this;
        }
        random_access_iterator_tag operator++(int)
        {
            random_access_iterator_tag temp(*this);
            ++_ptr;
            return temp;
        }
        random_access_iterator_tag &operator--()
        {
            --_ptr;
            return *this;
        }
        random_access_iterator_tag operator--(int)
        {
            random_access_iterator_tag temp(*this);
            --_ptr;
            return temp;
        }
        //====================================================================//
        //        B I N A R Y   A R I T H M E T I C   O P E R A T O R S       //
        //====================================================================//
        random_access_iterator_tag operator+(difference_type n) const { return (_ptr + n); }
        random_access_iterator_tag operator-(difference_type n) const { return (_ptr - n); }
        //====================================================================//
        //       D E R E F E R E N C E R I N G       O P E R A T O R S        //
        //====================================================================//
        reference operator*() const { return *_ptr; }
        pointer operator->() const { return &(*_ptr); }
        // subscript operator
        reference operator[](difference_type n) const { return *(_ptr + n); }
        //====================================================================//
        //  C O M P O U N D      A S S I G N M E N T      O P E R A T O R S   //
        //====================================================================//
        random_access_iterator_tag &operator+=(difference_type n)
        {
            _ptr += n;
            return *this;
        }
        random_access_iterator_tag &operator-=(difference_type n)
        {
            _ptr -= n;
            return *this;
        }
    };
    //========================================================================//
    // R A N D O M   A C C E S S    O P E R A T O R S    T E M P L A T E S    //
    //========================================================================//
    template <typename A>
    random_access_iterator_tag<A> operator+(typename random_access_iterator_tag<A>::difference_type n, const random_access_iterator_tag<A> &rhs)
    {
        return (rhs + n);
    }

    template <typename A, typename B>
    typename random_access_iterator_tag<A>::difference_type operator-(const random_access_iterator_tag<A> &lhs, const random_access_iterator_tag<B> &rhs)
    {
        return (lhs.base() - rhs.base());
    }
    //========================================================================//
    //             C O M P A R I S O N   O P E R A T O R S                    //
    //========================================================================//
    template <typename C, typename D> // same
    bool operator==(const random_access_iterator_tag<C> &lhs, const random_access_iterator_tag<D> &rhs)
    {
        return (lhs.base() == rhs.base());
    }
    template <typename C, typename D> // same
    bool operator!=(const random_access_iterator_tag<C> &lhs, const random_access_iterator_tag<D> &rhs)
    {
        return (!(lhs == rhs));
    }
    template <typename C, typename D> // reverse
    bool operator<(const random_access_iterator_tag<C> &lhs, const random_access_iterator_tag<D> &rhs)
    {
        return (lhs.base() < rhs.base());
    }
    template <typename C, typename D> // reverse
    bool operator>(const random_access_iterator_tag<C> &lhs, const random_access_iterator_tag<D> &rhs)
    {
        return (lhs.base() > rhs.base());
    }
    template <typename C, typename D> // reverse
    bool operator<=(const random_access_iterator_tag<C> &lhs, const random_access_iterator_tag<D> &rhs)
    {
        return (lhs.base() <= rhs.base());
    }
    template <typename C, typename D> // reverse
    bool operator>=(const random_access_iterator_tag<C> &lhs, const random_access_iterator_tag<D> &rhs)
    {
        return (lhs.base() >= rhs.base());
    }
}