#pragma once
#include <iostream>
#include "../ft_containers.hpp"
#include "../iterators/vectors_iterators.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
    class vector
    {
        private:

			allocator_type	_alloc;
			size_type		_capacity;
			size_type		_size;
            pointer			_data;
            // pointer         _begin;
            // pointer         _end;

        public:
            //=========================================//
            // -------- M E M B E R   T Y P E ---------//
            //=========================================//
            typedef T	                                                        value_type;
            typedef Alloc	                                                    allocator_type;
            typedef value_type&	                                                reference;
            typedef const value_type&                                           const_reference;
            typedef typename allocator_type::pointer	                        pointer;
            typedef typename allocator_type::const_pointer	                    const_pointer;
            typedef size_t                                                      size_type;
            typedef std::ptrdiff_t	                                            difference_type;
            typedef ft::iterator<value_type>                                    iterator;
            typedef ft::iterator<const value_type>                              const_iterator;
            typedef	ft::reverse_iterator<value_type>                            reverse_iterator;
            typedef	ft::reverse_iterator<const value_type>                      const_reverse_iterator;

            //=========================================//
            // ----- M E M B E R   F U N C TI O N -----//
            //=========================================//

            // C O N S T R U C T O R S ---> https://cplusplus.com/reference/vector/vector/vector/
            // default
            explicit vector (const allocator_type& alloc = allocator_type()) {
                _data = NULL;
                _alloc(alloc), _capacity(0), _size(0) {}
            }
            // fill
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {
                assign(n, val);
            }
            // range
            template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {
                assign(first, last);
                _data = NULL;
                _alloc = alloc;
                _capacity = 0;
                _size = 0;
            }
            // copy
			vector(vector const & x){
                _data = NULL;
                _capacity = 0;
                _size = 0;
                *this = x;
            }
            vector& operator= (const vector& x) {
                
            }
            //------------------------------------------------------------------
			vector	& operator=(vector const & x)
			{
				if (this != &x)
					assign(x.begin(), x.end());
				return (*this);
			}
            //------------------------------------------------------------------
			// D E S T R U C T O R
			~vector() { clear(); _alloc.deallocate(_data, _capacity); }


            //------------------------------------------------------------------
            // ------M O D I F I E R S--------// --> https://cplusplus.com/reference/vector/vector/assign/
			// assign range
            template <class InputIterator>  void assign (InputIterator first, InputIterator last) {
				size_type	n = 0;
				n = ft::distance(first, last);
				clear();
				reserve(n);
				_size = n;
				for (size_type i = 0; i < _size; i++)
					_alloc.construct((_data + i), *first++);
			}
			// assign fill
			void assign (size_type n, const value_type& val) {
				clear();
				reserve(n);
				_size = n;
				for (size_type i = 0; i < _size; i++)
					_alloc.construct((_data + i), val);
			}

            void clear() {
                for (size_type i = 0; i < _size; i++)
                    _alloc.destroy(_data[i]);
                _size = 0;
            }

            void swap (vector& x) {
                pointer temp_data;
                temp_data = x._data;
                x._alloc = _alloc;
                x._data = _data;
                _alloc = temp_data.alloc;
                _data = temp_data._data;
            }

            void push_back (const value_type& val) {
                _size++;
                _data[_size] = val;
            }

            void pop_back() {
                _alloc.destroy(_data[_size]);
                _size--;
            }
            //------------------------------------------------------------------------------------------------------------
            //  FAIRE ITERATOR FIRST POUR CES FCT
            //------------------------------------------------------------------------------------------------------------
            iterator erase (iterator position) {
                // do iterator first
                _alloc.destroy(position);
                // decaller tt a la gauche apres 
                _size--;
            }
            
            iterator erase (iterator first, iterator last) {
                    // do iterator first
            }
            // insert one element
            iterator insert (iterator position, const value_type& val) {

            }
            // insert fill
            void insert (iterator position, size_type n, const value_type& val) {

            }
            // insert a range of elements
            template <class InputIterator>    void insert (iterator position, InputIterator first, InputIterator last) {

            }
            //=========================================================//
            //                E L E M E N T   A C C E S S              //
            //=========================================================//
            reference operator[] (size_type n) {
            }
            const_reference operator[] (size_type n) const {
            }
            reference at (size_type n) {
            }
            const_reference at (size_type n) const {
            }
            reference front() {
            }
            const_reference front() const {
            }
            reference back() {
            }
            const_reference back() const {
            }
            //=========================================================//
            //                      C A P A C I T Y                    //
            //=========================================================//
            size_type size() const {
            }
            size_type max_size() const {
            }
            void resize (size_type n, value_type val = value_type()) {
            }
            size_type capacity() const {
            }
            bool empty() const {
            }
            void reserve (size_type n) {
            }
    };

}

// ❌ ✅
/* M E M B E R - T Y P E S 
    - value_type ✅
    - allocator_type ✅
    - reference ✅
    - const_reference ✅
    - pointer ✅
    - const_pointer ✅
    - iterator ❌
    - const_iterator ❌
    - reverse_iterator ❌
    - const_reverse_iterator ❌
    - difference_type ❌
    - size_type ✅

  M E M B E R - F U N C T I O N S
    - constructor (x 4) ✅
    - destructor ✅
    - operateur= ❌
    I T E R A T O R S // renvoi un iteratir
        - begin ❌
        - end ❌
        - rbegin ❌
        - rend ❌
    C A P A C I T Y 
        - size ❌
        - max_size ❌
        - resize ❌
        - capacity ❌
        - empty ❌
        - reserve ❌
    E L E M E N T - A C C E S S
        - operator[] ❌
        - at ❌
        - front ❌
        - back ❌
    M O D I F I E R S
        - assign ✅
        - push_back ✅
        - pop_back ✅
        - insert ❌
        - erase ❌
        - swap ✅
        - clear ✅


    A L L O C A T O R <--------------???
        - get_allocator ❌

N O N - M E M B E R - F U N C T I O N S
    - relational operators ❌
    - swap ❌
    Template specializations <--------------???
        - vector<bool> ❌

/*
* Elements are stored continiously
* => they can be accessed through iterators but also using offsets to regular pointers to elements
* => A pointer to an element of a vector may be passed to any function that expects a pointer to an element of an array.
* The storage of the vector is handled automatically, being expanded and contracted as needed.
* More memory is allocated to handle future growth that's why vectors usually occupy more space than a static arrays 
* This, in order to avoid reallocation every time a new element is added.
* Reallocation is done only when the additional memory is not enough.
*/