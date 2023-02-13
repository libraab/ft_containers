#pragma once
#include "ft_containers.hpp"

// --> https://legacy.cplusplus.com/reference/map/map/
// --> https://en.cppreference.com/w/cpp/container/map

namespace ft
{
    template < class Key,                                     // map::key_type
           class T,                                       // map::mapped_type
           class Compare = std::less<Key>,                     // map::key_compare
           class Alloc = std::allocator<std::pair<const Key,T> >    // map::allocator_type
           > 
        // TO DO need to recode the pair 👆🏻 (ft::pair)
    class map
    {
    public:
    //========================================================================//
    //                 M E M B E R               T Y P E                      //
    //========================================================================//
    /*
    key_type	            Key
    mapped_type	            T
    value_type	            std::pair<const Key_type, mapped_type>
    key_compare	            Compare
    allocator_type	        Alloc
    reference	            ft::allocator_type::reference            
    size_type	Unsigned integer type (usually std::size_t)
    difference_type	Signed integer type (usually std::ptrdiff_t)
    const_reference	const value_type&
    iterator	(LegacyBidirectional) Iterator to value_type
    const_iterator	(LegacyBidirectional) Iterator to const value_type
    reverse_iterator	std::reverse_iterator<iterator>
    const_reverse_iterator	std::reverse_iterator<const_iterator>


    typedef pair<const Key, T> value_type;

    */

    //========================================================================//
    //                   M E M B E R              F U N C T I O N S           //
    //========================================================================//
    // --> https://en.cppreference.com/w/cpp/container/map/map
    //========================================================================//
    //       C O N S T R U C T O R S      &      D E S T R U C T O R          //
    //========================================================================//
    map();
    explicit map( const Compare& comp, const Allocator& alloc = Allocator() );
    template< class InputIt >
    map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator());
    map( const map& other );
    //-------------------------------------------------------------------------
    //empty
    explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
    //range
    template <class InputIterator> 
    map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
    //copy
    map (const map& x);
    ~map();
    //-------------------------------------------------------------------------
    map& operator= (const map& x);
    };
}



