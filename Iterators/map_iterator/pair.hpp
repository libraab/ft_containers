#pragma once
#include "../../ft_containers.hpp"

namespace ft {
    /*██████╗      █████╗     ██╗    ██████╗
      ██╔══██╗    ██╔══██╗    ██║    ██╔══██╗
      ██████╔╝    ███████║    ██║    ██████╔╝
      ██╔═══╝     ██╔══██║    ██║    ██╔══██╗
      ██║         ██║  ██║    ██║    ██║  ██║
      ╚═╝         ╚═╝  ╚═╝    ╚═╝    ╚═╝  ╚═*/
    // --> https://cplusplus.com/reference/utility/pair/
    template <typename T1, typename T2>
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
        //----------------------------------------------------------------------
        // added to official
        pair& operator=(const pair &x) {
            this->first = x.first;
            this->second = x.second;
            return *this;
        }
        // Comparison operators
        bool operator==(const pair<T1,T2>& rhs) const {
            return (first == rhs.first && second == rhs.second);
        }
        bool operator!=(const pair<T1,T2>& rhs) const {
            return !(*this == rhs);
        }
        bool operator<(const pair<T1,T2>& rhs) const {
            return (first < rhs.first || (!(rhs.first < first) && second < rhs.second));
        }
        bool operator>(const pair<T1,T2>& rhs) const {
            return (rhs < *this);
        }
        bool operator<=(const pair<T1,T2>& rhs) const {
            return !(rhs < *this);
        }
        bool operator>=(const pair<T1,T2>& rhs) const {
            return !(*this < rhs);
        }
    };

/*███╗   ███╗     █████╗     ██╗  ██╗    ███████╗            ██████╗      █████╗     ██╗    ██████╗
  ████╗ ████║    ██╔══██╗    ██║ ██╔╝    ██╔════╝            ██╔══██╗    ██╔══██╗    ██║    ██╔══██╗
  ██╔████╔██║    ███████║    █████╔╝     █████╗              ██████╔╝    ███████║    ██║    ██████╔╝
  ██║╚██╔╝██║    ██╔══██║    ██╔═██╗     ██╔══╝              ██╔═══╝     ██╔══██║    ██║    ██╔══██╗
  ██║ ╚═╝ ██║    ██║  ██║    ██║  ██╗    ███████╗            ██║         ██║  ██║    ██║    ██║  ██║
  ╚═╝     ╚═╝    ╚═╝  ╚═╝    ╚═╝  ╚═╝    ╚══════╝            ╚═╝         ╚═╝  ╚═╝    ╚═╝    ╚═╝  ╚═*/ 
    // --> https://cplusplus.com/reference/utility/make_pair/
    template <class T1,class T2>
    ft::pair<T1,T2>     make_pair(T1 x, T2 y)
    { return (pair<T1,T2>(x,y));}
}