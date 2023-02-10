#pragma once
#include "../ft_containers.hpp"
#include "vector.hpp"

namespace ft
{
  // --> https://cplusplus.com/reference/stack/stack/
    template<class T, class container = std::vector<T> >
    class stack
    {
      public:
    //========================================================================//
    //                    M E M B E R          T Y P E S                      //
    //========================================================================//
        typedef T           value_type;
        typedef container   container_type;
    //========================================================================//
    //                        C O N S T R U C T O R                           //
    //========================================================================//
    // --> https://cplusplus.com/reference/stack/stack/stack/
    explicit stack (const container_type& ctnr = container_type()) { _ctnr(ctnr)}
    //========================================================================//
    //             R E L A T I O N A L          O P E R A T O R S             //
    //========================================================================//
    // --> https://cplusplus.com/reference/stack/stack/operators/
    template <class T, class Container>
    friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {return (lhs._ctnr == rhs._ctnr);}
    
    template <class T, class Container>
    friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {return (lhs._ctnr != rhs._ctnr);}

    template <class T, class Container>
    friend bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {return (lhs._ctnr < rhs._ctnr);}

    template <class T, class Container> 
    friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {return (lhs._ctnr <= rhs._ctnr);}

    template <class T, class Container> 
    friend bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {return (lhs._ctnr > rhs._ctnr);}

    template <class T, class Container> 
    friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {return (lhs._ctnr >= rhs._ctnr);}
    //========================================================================//
    //                    M E M B E R    F U N C T I O N S                    //
    //========================================================================//
    bool empty() const {retur}
    size_t size() const;
    value_type& top();const value_type& top() const;
    void push (const value_type& val);

    template <class... Args> void emplace (Args&&... args);
    void pop();
    void swap (stack& x) noexcept(/*see below*/);

    //--------------------------------------------------------------------------
      protected:
        container_type      _ctnr;
  };
}
// ❌ ✅
/* M E M B E R - T Y P E S
    - value_type ❌
    - container_type ❌
    - size_type ❌
   M E M B E R - F U N C T I O N S
    - Constructor ❌
    - empty ❌
    - size ❌
    - top ❌
    - push ❌
    - emplace ❌
    - pop ❌
    - swap ❌
  N O N - M E M B E R - F U N C T I O N 
    - relational operators ❌
    - swap (stack) ❌
*/