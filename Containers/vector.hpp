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
            // ---> https://cplusplus.com/reference/vector/vector/vector/

            C O N S T R U C T O R S 
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
            template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {
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
            //                      M O D I F I E R S                         //
            //==================================================================
            // -> https://cplusplus.com/reference/vector/vector/assign/
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
            iterator erase (iterator position)
            { empty() ? return end() : return (erase(position, position + 1)); }
            //------------------------------------------------------------------
            iterator erase (iterator first, iterator last) {
                if (this->empty())
                    return(this->end());
                iterator start = this->begin();
                iterator x = first; // to return it later
                difference_type diff = last - first;
                while (start != first)
                    start++;
                for (; first != last; first++)
                    _alloc.destroy(&(*first));
                while (start + diff != end()) {
                    _alloc.construct(&(*start), *(start + diff));
                    start++;
                }
                while (diff-- > 0)
                    pop_back();
                return (x);
            }
            //------------------------------------------------------------------
            // insert one element
            iterator insert (iterator position, const value_type& val) {
                insert(position, 1, val);
                return (iterator(&this->_data[ft::distance(this->begin(), position)]));
            }
            //------------------------------------------------------------------
            // insert fill
            void insert (iterator position, size_type n, const value_type& val) {
                vector tmp(position, end()); // create new vector
                this->_size -= ft::distance(position, end());
                while (n) {
                    push_back(val); // already a ref
                    n--;
                }
                iterator tmpStart = tmp.begin();
                while (tmpStart != tmp.ebd()) {
                    push_back(*tmpStart);
                    tmpStart++;
                }
            }
            //------------------------------------------------------------------
            template <class InputIterator>
            // insert a range of elements
            void insert (iterator position, InputIterator first, InputIterator last) {
                vector tmp(position, end());
                this->_size -= ft::distance(position, end());
                while (first != last) {
                    push_back(*first);
                    first++;
                }
                iterator tmpStart = tmp.begin();
                while (tmpStart != tmp.ebd()) {
                    push_back(*tmpStart);
                    tmpStart++;
                }
            }
            //================================================================//
            //                E L E M E N T          A C C E S S              //
            //================================================================//
            // Returns a ref to the elt at pos n in the vector container
            reference operator[] (size_type n) {return (_data[n]);}
            const_reference operator[] (size_type n) const {return (_data[n]);}
            reference at (size_type n) {size() <= n ? throw (std::out_of_range("vector")) : return _data[n];}
            const_reference at (size_type n) const {size() <= n ? throw (std::out_of_range("vector")) : return _data[n];}
            //------------------------------------------------------------------
            // Returns a ref to the 1rst elt in the vector
            reference front() {return (*begin());}
            const_reference front() const {return (*begin());}
            //------------------------------------------------------------------
            // Returns a ref to the last elt in the vector
            reference back() {return(*(end() - 1));}
            const_reference back() const {return(*(end() - 1));}
            //================================================================//
            //                        C A P A C I T Y                         //
            //================================================================//
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