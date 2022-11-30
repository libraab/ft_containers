#pragma once
#include "../ft_containers.hpp"

//===================//
//     PROTOTYPES    //
//===================//

//===================//
// CLASS DEFINITIONS //
//===================//
namespace ft
{
    class vector
    {
        public:
            vector();
            vector(const vector&);
            virtual ~vector();
    };
}

/*
* Elements are stored continiously
* => they can be accessed through iterators but also using offsets to regular pointers to elements
* => A pointer to an element of a vector may be passed to any function that expects a pointer to an element of an array.
* The storage of the vector is handled automatically, being expanded and contracted as needed.
* More memory is allocated to handle future growth that's why vectors usually occupy more space than a static arrays 
* This, in order to avoid reallocation every time a new element is added.
* Reallocation is done only when the additional memory is not enough.
*/

// ❌ ✅
/* M E M B E R - T Y P E S 
    - value_type
    - allocator_type
    - reference
    - const_reference
    - pointer
    - const_pointer
    - iterator
    - const_iterator
    - reverse_iterator
    - const_reverse_iterator
    - difference_type
    - size_type

  M E M B E R - F U N C T I O N S
    - constructor
    - destructor
    - operateur=
    I T E R A T O R S
        - begin
        - end
        - rbegin
        - rend 
        - cbegin
        - cend
        - crbegin
        - crend
    C A P A C I T Y 
        - size
        - max_size
        - resize
        - capacity
        - empty
        - reserve
        - shrink_to_fit
    E L E M E N T - A C C E S S
        - operator[]
        - at
        - front
        - back
        - data
    M O D I F I E R S
        - assign
        - push_back
        - pop_back
        - insert
        - erase
        - swap
        - clear
        - emplace
        - emplace_back
    A L L O C A T O R <--------------???
        - get_allocator

N O N - M E M B E R - F U N C T I O N S
    - relational operators
    - swap
    Template specializations <--------------???
        - vector<bool>
*/