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
            //================================================================//
            //              M E M B E R            T Y P E                    //
            //================================================================//
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

            //================================================================//
            //             M E M B E R            F U N C T I O N S           //
            //================================================================//
            // C O N S T R U C T O R S ---> https://cplusplus.com/reference/vector/vector/vector/
            //------------------------------------------------------------------
            // default : contruct an empty container with no elements
            explicit vector(const allocator_type& alloc = allocator_type())
				: _dat(nullptr), _alloc(alloc), _capacity(0), _size(0) {}
            //------------------------------------------------------------------
            // fill constructor : constructs a container with n elments (each is copy of val)
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
            {assign(n, val);}
            //------------------------------------------------------------------
            // renge constructor : Constructs a container with as many elements as the range (from 1rst till last)
            template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {
                assign(first, last);
                _data = nullptr;
                _alloc = alloc;
                _capacity = 0;
                _size = 0;
            }
            //------------------------------------------------------------------
            // copy constructor 
            vector(const vector& x) : _alloc(allocator_type()), _capacity(0), _size(0), _data(nullptr)
            {assign(x.begin(), x.end());}
            //------------------------------------------------------------------
			// D E S T R U C T O R
			~vector() {
                clear();
                if (_capacity > 0) // --> ternaire
                    _alloc.deallocate(_data, _capacity);}
            //------------------------------------------------------------------
			vector& operator=(const vector& rhs)
			{
				if (this != &rhs)
					assign(rhs.begin(), rhs.end());
				return *this;
			}
            //==================================================================
            // M O D I F I E R S --> https://cplusplus.com/reference/vector/vector/assign/
            //==================================================================
            template <class InputIterator>
			// assign range
            void assign (InputIterator first, InputIterator last) { // typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type *enable = nullptr
				this->clear();
                while(first != last) {
                    push_back(*first); // push_back(*first++); ??
                    ++first; }
			}
            //------------------------------------------------------------------
			// assign fill
			void assign (size_type n, const value_type& val) {
				this->clear();
				for (size_type i = 0; i < n; i++)
					push_back(val);
			}
            //------------------------------------------------------------------
            void clear() {
                if (_size > 0) {
                    for (size_type i = 0; i < _size; i++)
                        _alloc.destroy(_data[i]);
                    _size = 0;
                }
            }
            //------------------------------------------------------------------
            void swap (vector& x) {

                allocator_type	tmpAlloc = this->_alloc;
                size_type		tmpCapacity = this->_capacity;
                size_type		tmpSize = this->_size;
                pointer			tmpData = this->_data;

                this->_alloc = x._alloc;
                this->_capacity = x._capacity; 
                this->_size = x._size;
                this->_data = x._data

                x._alloc = tmpAlloc;
                x._capacity = tmpCapacity; 
                x._size = tmpSize;
                x._data = tmpData;
            }
            //------------------------------------------------------------------
            void push_back (const value_type& val) {
                if (_capacity == _size)
                    empty() ? reserve(1) : reserve(_size * 2);
                _alloc.construct(_data + _size, val);
                _size++;
            }
            //------------------------------------------------------------------
            void pop_back() {
                if (_size > 0) {
                    _alloc.destroy(_data + (_size - 1));
                    _size--;
                }
            }
            //------------------------------------------------------------------
            iterator erase (iterator position) {
                if (this->empty())
                    return(this->end());
                difference_type pos = position.base() - this->_data.begin();
                std::memmove(this->_data.begin() + pos, this->_data.begin() + pos + 1, (this->_size - pos - 1) * sizeof(value_type));
                _allocator.destroy(this->_data.begin() + this->_size);
                this->_data.end()--;
                this->_size--;
                return (iterator(this->_data.begin() + pos));
            }
            //------------------------------------------------------------------
            iterator erase (iterator first, iterator last) {
                if (this->empty())
                    return(this->end());
                difference_type diff = last.base() - first.base();
                std::memmove(first.base(), last.base(), (this->_size - diff) * sizeof(value_type));
                for(size_type i = this->_size - diff; i < this->_size ; i++)
                    _allocator.destroy(this->_data.begin() + i);
                this->_size -= diff;
                this->_data.end() -= diff;
                return (last - diff)
            }
            //------------------------------------------------------------------
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