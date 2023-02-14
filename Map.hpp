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
        // TO DO : recode the pair 👆🏻 (ft::pair)
    class map
    {
        public:
        //====================================================================//
        //                 M E M B E R           T Y P E                      //
        //====================================================================//
        typedef Key                                             key_type;
        typedef T                                               mapped_type;
        typedef std::pair<const Key_type, mapped_type>          value_type;
        typedef Compare                                         key_compare;
        typedef Alloc                                           allocator_type;
        typedef typename allocator_type::reference              reference;
        typedef typename allocator_type::const_reference        const_reference;
        typedef typename allocator_type::pointer                pointer; 
        typedef typename allocator_type::const_pointer          const_pointer; 	            
        typedef ft::map_iterator<value_type>                    iterator;
        typedef ft::map_iterator<const value_type>              const_iterator;
        typedef ft::reverse_iterator<iterator>                  reverse_iterator;	    
        typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;	
        typedef std::ptrdiff_t                                  difference_type;  
        typedef std::size_t                                     size_type;

        protected:
            key_compare     _comp;
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
            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
            {_comp = comp;
            allocator_type = alloc;}
            //range (4)
            template <class InputIterator> 
            map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
            {
                _comp = comp;
                allocator_type = alloc;
                // insert iterator into node 
            }
            //copy (1)
            map (const map& x);
            //destructor
            ~map();
            //-----------------------------------------------------------------
            // V A L U E _ C O M P A R E 
            // --> https://cplusplus.com/reference/map/map/value_comp/
            class value_compare
            {   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
                friend class map;
                protected:
                    Compare comp;
                    value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
                public:
                    typedef bool result_type;
                    typedef value_type first_argument_type;
                    typedef value_type second_argument_type;
                    bool operator() (const value_type& x, const value_type& y) const
                        return comp(x.first, y.first);
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
            iterator begin();
            const_iterator begin() const;
            //------------------------------------------------------------------
            iterator end();
            const_iterator end() const;
            //------------------------------------------------------------------
            reverse_iterator rbegin();
            const_reverse_iterator rbegin() const;
            //------------------------------------------------------------------
            reverse_iterator rend();
            const_reverse_iterator rend() const;
            //================================================================//
            //                           C A P A C I T Y                      //
            //================================================================//
            bool empty() const;
            size_type size() const;
            size_type max_size() const;
            //================================================================//
            //                  E L E M E N T         A C C E S               //
            //================================================================//
            mapped_type& operator[] (const key_type& k);
            //================================================================//
            //                      M O D I F I E R S                         //
            //================================================================//
            pair<iterator,bool> insert (const value_type& val);
            iterator insert (iterator position, const value_type& val);	
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last);
            //------------------------------------------------------------------
            void erase (iterator position);
            size_type erase (const key_type& k);
            void erase (iterator first, iterator last);
            //------------------------------------------------------------------
            void swap (map& x);
            void clear();
            //================================================================//
            //                           O B S E R V E R S                    //
            //================================================================//
            key_compare key_comp() const;
            value_compare value_comp() const;
            //================================================================//
            //                         O P E R A T I O N S                    //
            //================================================================//
            iterator find (const key_type& k);
            const_iterator find (const key_type& k) const;
            //------------------------------------------------------------------
            size_type count (const key_type& k) const;
            //------------------------------------------------------------------
            iterator lower_bound (const key_type& k);
            const_iterator lower_bound (const key_type& k) const;
            //------------------------------------------------------------------
            iterator upper_bound (const key_type& k);
            const_iterator upper_bound (const key_type& k) const;
            //------------------------------------------------------------------
            pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
            pair<iterator,iterator>             equal_range (const key_type& k);
            //================================================================//
            //                       A L L O C A T O R                        //
            //================================================================//
            allocator_type get_allocator() const;
    };
}