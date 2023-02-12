#pragma once
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
    // general definition --> https://legacy.cplusplus.com/reference/iterator/iterator/
    template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference = T &>
    class iterator
    {
    public:
        typedef T value_type;
        typedef Distance difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef Category iterator_category;
    };
    // generic definition ---> https://legacy.cplusplus.com/reference/iterator/iterator_traits/
    template <class Iterator>
    class iterator_traits
    {
    public:
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::iterator_category iterator_category;
    };
    // T* specialisation ---> https://legacy.cplusplus.com/reference/iterator/iterator_traits/
    template <class T>
    class iterator_traits<T *>
    {
    public:
        typedef ptrdiff_t difference_type; // --> https://legacy.cplusplus.com/reference/cstddef/ptrdiff_t/
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef std::random_access_iterator_tag iterator_category; // --> https://legacy.cplusplus.com/reference/iterator/RandomAccessIterator/
    };
    // const T* specialisation ---> https://legacy.cplusplus.com/reference/iterator/iterator_traits/
    template <class T>
    class iterator_traits<const T *>
    {
    public:
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef std::random_access_iterator_tag iterator_category;
    };
    template<class InputIterator>
    ptrdiff_t distance(InputIterator first, InputIterator last) {
        ptrdiff_t size = 0;
        while (first != last) {
            first++;
            size++;
        }
        return (size);
    };
}