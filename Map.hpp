#pragma once
#include "ft_containers.hpp"
#include "Iterators/map_iterator/AVL_tree.hpp"
//#include "Iterators/map_iterator/bidirectional_iterator.hpp"
#include "Iterators/map_iterator/pair.hpp"

// --> https://legacy.cplusplus.com/reference/map/map/
// --> https://en.cppreference.com/w/cpp/container/map

namespace ft
{
    template < class Key,                                               // map::key_type
           class T,                                                     // map::mapped_type
           class Compare = std::less<Key>,                              // map::key_compare
           class Alloc = std::allocator<ft::pair<const Key,T> >        // map::allocator_type
           > 
    class map
    {
        public:
        //====================================================================//
        //                 M E M B E R           T Y P E                      //
        //====================================================================//
        typedef Key                                             key_type;
        typedef T                                               mapped_type;
        typedef ft::pair<const Key, T>                          value_type;
        typedef Compare                                         key_compare;
        typedef Alloc                                           allocator_type;
        typedef typename allocator_type::reference              reference;
        typedef typename allocator_type::const_reference        const_reference;
        typedef typename allocator_type::pointer                pointer; 
        typedef typename allocator_type::const_pointer           const_pointer; 	            
        typedef ft::bidirectional_iterator_tag<value_type>       iterator;
        typedef ft::bidirectional_iterator_tag<const value_type> const_iterator;
        typedef ft::reverse_iterator<iterator>                  reverse_iterator;	    
        typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;	
        typedef std::ptrdiff_t                                  difference_type;  
        typedef std::size_t                                     size_type;
		typedef AVL_tree<T, Key, Compare, Alloc>              	BBST;

        protected:
            key_compare     _comp;
            allocator_type  _alloc;
            size_type       _size;
            BBST            _tree;
            Node *root;
        //====================================================================//
        //                   M E M B E R          F U N C T I O N S           //
        //====================================================================//
        // --> https://en.cppreference.com/w/cpp/container/map/map
        //====================================================================//
        //       C O N S T R U C T O R S      &      D E S T R U C T O R      //
        //====================================================================//
        public:
            // --> https://legacy.cplusplus.com/reference/map/map/map/
            //empty (2)
            explicit map (const key_compare& comp = key_comp(), const allocator_type& alloc = allocator_type())
            {_comp = comp;
            _alloc = alloc;}
            //range (4)
            template <class InputIterator> 
            map (InputIterator first, InputIterator last, const key_compare& comp = key_comp(), const allocator_type& alloc = allocator_type())
            {
                _comp = comp;
                _alloc = alloc;
                this->insert(first, last); 
            }
            //copy (1)
            map (const map& cpy) {
                _comp = cpy._comp;
                _alloc = cpy._alloc;


                if (*this != cpy){
					this->_key_compare = x.key_comp();
					this->_allocator = x.get_allocator();
					this->_tree = x._tree;
					this->_size = x.size();
				}
            }
            //destructor
            ~map() { }
            //-----------------------------------------------------------------
            // V A L U E _ C O M P A R E 
            // --> https://cplusplus.com/reference/map/map/value_comp/
            // basically it compares the keys (first arg) of a pair, the same as key_comp who takes 2 keys instead of 2 pairs
            // --> https://cplusplus.com/reference/map/map/key_comp/
            class value_compare : public std::binary_function<value_type,value_type,bool> // 👇🏻 
            {   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
                friend class map;
                protected:
                    Compare comp;
                    value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
                public:
                    typedef bool result_type; // useless
                    typedef value_type first_argument_type; // useless
                    typedef value_type second_argument_type; // useless
                    bool operator() (const value_type& x, const value_type& y) const // takes 2 value_type (pairs)
                        {return comp(x.first, y.first);}
                    //added to official
                    // bool operator() (const value_type& x, const key_type& y) const // take value_type & key_type
                    //     return comp(x.first, y);
                    // bool operator() (const value_type& x, const value_type& y) const // takes key_type & value_type
                    //     return comp(x, y.first);
            };
            //------------------------------------------------------------------
            map& operator= (const map& x) {
                clear();
                insert(x.begin(), x.end());
                return *this;
            }
            //================================================================//
            //                      I T E R A T O R S                         //
            //================================================================//
            // --> wwhttps://en.cppreference.com/w/cpp/iterator/begin
            iterator begin()                {return (_tree.begin());}
            const_iterator begin() const    {return (_tree.begin());}
            //------------------------------------------------------------------
            iterator end()                  {return (_tree.end());}
            const_iterator end() const      {return (_tree.end());}
            //------------------------------------------------------------------
            reverse_iterator rbegin()               {return (_tree.rbegin());}
            const_reverse_iterator rbegin() const   {return (_tree.rbegin());}
            //------------------------------------------------------------------
            reverse_iterator rend()                 {return (_tree.rend());}
            const_reverse_iterator rend() const     {return (_tree.rend());}
            //================================================================//
            //                           C A P A C I T Y                      //
            //================================================================//
            bool empty() const          {return (_tree.get_size() == 0);}
            size_type size() const      {return (_tree.get_size());}
            //size_type max_size() const  {return (_tree.max_size());}
            size_type max_size() const  {return (allocator_type.max_size());}
            //================================================================//
            //                  E L E M E N T         A C C E S               //
            //================================================================//
            mapped_type& operator[] (const key_type& k) {
                //return(this->_tree.insert(k, mapped_type()).first->second);
                ft::pair<iterator, bool> op = insert(ft::make_pair(k, mapped_type()));
				return (op.first->second);
            }
            //================================================================//
            //                      M O D I F I E R S                         //
            //================================================================//
            pair<iterator,bool> insert (const value_type& val) {
                return (_tree.insert_node(val.first, val.second));
            }
            iterator insert (iterator position, const value_type& val) {
                ft::pair<iterator,bool> ret = _tree.insert_node(val.first, val.second, position.base());
				return (ret.first);
            }
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last) {
                while (first != last){
					_tree.insert_node(first->first, first->second);
					first++;
				}
            }
            //------------------------------------------------------------------
            void erase (iterator position)              {_tree.delete_node(position);}
            size_type erase (const key_type& k)         {return (_tree.delete_node(k));}
            void erase (iterator first, iterator last)  {
                while (first != last)
				delete_node(first++);
            }
            //------------------------------------------------------------------
            void swap (map& x)  {_tree.swap(x._tree);}
            void clear()        {_tree.clear();}
            //================================================================//
            //                           O B S E R V E R S                    //
            //================================================================//
            key_compare key_comp() const                {return (_key_comp);}
            value_compare value_comp() const            {return (_value_comp);}
            //================================================================//
            //                         O P E R A T I O N S                    //
            //================================================================//
            iterator find (const key_type& k)                       {return (_tree.find(k));}
            const_iterator find (const key_type& k) const           {return (_tree.find(k));}
            //------------------------------------------------------------------
            size_type count (const key_type& k) const               {return (_tree.count(k));}
            //------------------------------------------------------------------
            iterator lower_bound (const key_type& k)                {return (_tree.lower_bound(k));}
            const_iterator lower_bound (const key_type& k) const    {return (_tree.lower_bound(k));}
            //------------------------------------------------------------------
            iterator upper_bound (const key_type& k)                {return (_tree.upper_bound(k));}
            const_iterator upper_bound (const key_type& k) const    {return (_tree.upper_bound(k));}
            //------------------------------------------------------------------
            pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
                return (_tree.equal_range(k));}
            pair<iterator,iterator>             equal_range (const key_type& k) {
                return (_tree.equal_range(k));}
            //================================================================//
            //                       A L L O C A T O R                        //
            //================================================================//
            allocator_type get_allocator() const                    {return (_tree.get_allocator());}
    };
    //========================================================================//
    //         N O N         M E M B E R       O V E R L O A D I N G S        //
    //========================================================================//
	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
        return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));}
	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
        return (!(lhs == rhs));}
	template <class Key, class T, class Compare, class Alloc>
	bool operator< (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));}
	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		return (!(rhs < lhs));}
	template <class Key, class T, class Compare, class Alloc>
	bool operator> (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		return (rhs < lhs);}
	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		return (!(lhs < rhs));}
	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs) {
		lhs.swap(rhs);}
}
