#pragma once
#include "../../ft_containers.hpp"
#include "pair.hpp"

namespace ft {
  /*███╗   ██╗     ██████╗     ██████╗     ███████╗
    ████╗  ██║    ██╔═══██╗    ██╔══██╗    ██╔════╝
    ██╔██╗ ██║    ██║   ██║    ██║  ██║    █████╗  
    ██║╚██╗██║    ██║   ██║    ██║  ██║    ██╔══╝  
    ██║ ╚████║    ╚██████╔╝    ██████╔╝    ███████╗
    ╚═╝  ╚═══╝     ╚═════╝     ╚═════╝     ╚══════*/
    template <typename P>
    class Node {
        public:
        P               pair;
        int             height;
        Node*           left;
        Node*           right;
        Node*           parent;
        //Node*           nil;          
        // CONSTRUCTOR    
        Node(P p) : pair(p), height(1),/* nil(NULL),*/ left(NULL), right(NULL), parent(NULL) {}
    };
  /*██╗    ████████╗    ███████╗    ██████╗      █████╗     ████████╗     ██████╗     ██████╗ 
    ██║    ╚══██╔══╝    ██╔════╝    ██╔══██╗    ██╔══██╗    ╚══██╔══╝    ██╔═══██╗    ██╔══██╗
    ██║       ██║       █████╗      ██████╔╝    ███████║       ██║       ██║   ██║    ██████╔╝
    ██║       ██║       ██╔══╝      ██╔══██╗    ██╔══██║       ██║       ██║   ██║    ██╔══██╗
    ██║       ██║       ███████╗    ██║  ██║    ██║  ██║       ██║       ╚██████╔╝    ██║  ██║
    ╚═╝       ╚═╝       ╚══════╝    ╚═╝  ╚═╝    ╚═╝  ╚═╝       ╚═╝        ╚═════╝     ╚═╝  ╚═*/

    template <typename K, typename T, class Compare, class Alloc>
    class biterator {
        public :
        typedef std::bidirectional_iterator_tag     iterator_category;
        typedef std::ptrdiff_t                      difference_type;
        typedef ft::pair<K, T>                      value_type;
        typedef value_type*                         pointer;
        typedef value_type&                         reference;
        typedef Node<value_type>                    Node;

        Node*                               _node;

        biterator() :                       _node(NULL) {}
        biterator(Node* n) :                _node(n) {}
        biterator(biterator const & x) :    _node(x._node) {}
        ~biterator() {};
        //--------------------------------------------------------------------//
        // Assignment operator
        biterator & operator=(biterator const & rhs) {
            if (this != &rhs) {
                this->_node = rhs._node;
            }
            return (*this);
        }
        //--------------------------------------------------------------------//
        // Comparison operators
        bool operator==(biterator const & rhs) const { return (this->_node == rhs._node); }
        bool operator!=(biterator const & rhs) const { return (this->_node != rhs._node); }
        //--------------------------------------------------------------------//
        // Dereference operators
        reference operator*() const { return (this->_node->pair); }
        pointer operator->() const { return &(this->_node->pair); }
        //--------------------------------------------------------------------//
        // reference operator*() const {return (*(operator->()));}
        // pointer operator->() const {return (ft::pair<K, T> *)(&this->_node->pair);}
        //--------------------------------------------------------------------//
        // Increment/decrement operators
        biterator & operator++() {
            if (_node->right != NULL) {
                _node = _node->right;
                // Find the leftmost node in the right subtree
                while (_node->left != NULL)
                    _node = _node->left;
            } else {
                // Go up the tree until we find a node whose left child we haven't visited yet
                Node *tmp = _node->parent;
                while (_node == tmp->right) {
                    _node = tmp;
                    tmp = tmp->parent;
                }
                if (_node->right != tmp)
                    _node = tmp;
            }
            return *this;
        }
        //--------------------------------------------------------------------//
        biterator operator++(int) {
            biterator tmp(*this);
            operator++();
            return (tmp);
        }
        //--------------------------------------------------------------------//
        biterator & operator--() {
            if (_node->left != NULL) {
                _node = _node->left;
                // Find the rightmost node in the left subtree
                while (_node->right != NULL)
                    _node = _node->right;
            } else {
                // Go up the tree until we find a node whose left child we haven't visited yet
                Node *tmp = _node->parent;
                while (_node == tmp->left) {
                    _node = tmp;
                    tmp = tmp->parent;
                }
                _node = tmp;
            }
            return (*this);
        }
        //--------------------------------------------------------------------//
        biterator operator--(int) {
            biterator tmp(*this);
            operator--();
            return tmp;
        }
        //--------------------------------------------------------------------//
    };
   /*█████╗     ██╗   ██╗    ██╗                 ████████╗    ██████╗     ███████╗    ███████╗    
    ██╔══██╗    ██║   ██║    ██║                 ╚══██╔══╝    ██╔══██╗    ██╔════╝    ██╔════╝    
    ███████║    ██║   ██║    ██║                    ██║       ██████╔╝    █████╗      █████╗      
    ██╔══██║    ╚██╗ ██╔╝    ██║                    ██║       ██╔══██╗    ██╔══╝      ██╔══╝      
    ██║  ██║     ╚████╔╝     ███████╗               ██║       ██║  ██║    ███████╗    ███████╗    
    ╚═╝  ╚═╝      ╚═══╝      ╚══════╝               ╚═╝       ╚═╝  ╚═╝    ╚══════╝    ╚══════*/
    template <class K, class T, class Compare, class Alloc>
    class AVL_tree {
        public:
        typedef ft::pair<K, T>                                  value_type;
        typedef Node<value_type>                                Node;
        typedef Alloc                                           allocator_type;
        typedef ft::biterator<K, T, Compare, Alloc>             iterator;
        typedef ft::biterator<const K, T, Compare, Alloc>       const_iterator;
        typedef K                                               key_type;

        Node*               _root;
        size_t              _size;
        allocator_type      _alloc;
        //====================================================================//
        //      C O N S T R U C T O R S       &      D E S T R U C T O R      //
        //====================================================================//
        AVL_tree() :            _root(NULL), _size(0), _alloc(allocator_type()) {}
        AVL_tree(Node &n) :     _root(n), _size(0), _alloc(allocator_type()) {}
        ~AVL_tree() {clear(_root);}
        //====================================================================//
        int get_height(Node* node) {
            if (node == NULL)
                return 0;
            return node->height;
        }
        //====================================================================//
        int get_size() const {return _size;}
        //====================================================================//
        int get_balance_factor(Node* node) {
            if (node == NULL)
                return 0;
            return get_height(node->left) - get_height(node->right);
        }
        //====================================================================//
        Node* get_root() {return _root;}
        //====================================================================//
        allocator_type get_allocator() {return _alloc;}
        //====================================================================//
        void update_height(Node* node) {
            int left_height = get_height(node->left);
            int right_height = get_height(node->right);
            // --> https://www.youtube.com/watch?v=vRwi_UcZGjU
            node->height = std::max(left_height, right_height) + 1;
        }
        //====================================================================//
        Node* rotate_right(Node* cur) {
         if (cur->left == NULL)
                return cur;

            // std::cout << "before left" << std::endl;
            // print_tree();

            Node* new_root = cur->left;
            cur->left = new_root->right;
            if (cur->left != NULL)
                cur->left->parent = cur;
            new_root->right = cur;
            new_root->parent = cur->parent;
            cur->parent = new_root;

            if (new_root->parent == NULL)
                _root = new_root;
            else if (new_root->parent->right == cur)
                new_root->parent->right = new_root;
            else 
                new_root->parent->left = new_root;
            update_height(cur);
            update_height(new_root);

            // std::cout << "after" << std::endl;
            // std::cout << "(" << cur->pair.first << ")" << std::endl;
            // print_tree();

            return new_root;
        }
        //====================================================================//
        Node* rotate_left(Node* cur) {
            if (cur->right == NULL)
                return cur;

            // std::cout << "before left" << std::endl;
            // print_tree();

            Node* new_root = cur->right;
            cur->right = new_root->left;
            if (cur->right != NULL)
                cur->right->parent = cur;
            new_root->left = cur;
            new_root->parent = cur->parent;
            cur->parent = new_root;

            if (new_root->parent == NULL)
                _root = new_root;
            else if (new_root->parent->left == cur)
                new_root->parent->left = new_root;
            else 
                new_root->parent->right = new_root;
            update_height(cur);
            update_height(new_root);

            // print_tree();

            return new_root;
        }
        void print_tree() {print_tree(_root);}
        void print_tree(Node* node, std::string indent = "", bool right = false) {
             
            if (node != nullptr) {
                std::cout << indent;
                if (right)
                {
                    std::cout << "R----";
                    indent += "   ";
                }
                else
                {
                    std::cout << "L----";
                    indent += "|  ";
                }
                std::cout << node->pair.first << std::endl;
                print_tree(node->left, indent, false);
                print_tree(node->right, indent, true);
            }
            // else
            //     std::cout << "|                    empty                       |" << std::endl;
        }
        //====================================================================//
        // Inserts a new node with the given value `val` into an AVL tree rooted at `node`
        Node* insert_node(Node* cur, const value_type& new_node, Node* root) {
            // If the current _root is null, create a new node with the given value and return it
            // std::cout << "* inserting (" << new_node.first << ")" << std::endl;
            // std::cout << "" << std::endl;               
            if (cur == NULL) {
                Node* x = new Node(new_node); // which _root is new_node
                if (_size == 0) {
                // std::cout << "new tree created" << std::endl;
                    _root = x;
                }
                // else
                //     std::cout << "new node created" << std::endl;
                _size++;
                return (x);
            }
            // std::cout << "adding " << new_node.first <<" to existant tree" << std::endl;
            // Insert the new node in the left or right subtree depending on its value
            if (new_node.first < cur->pair.first) {
                // std::cout << "(" << new_node.first << ")" << "is less than" << "(" << cur->pair.first << ")" << std::endl;
                // std::cout << "going left" << std::endl;
                cur->left = insert_node(cur->left, new_node, root);
                cur->left->parent = cur; // new parent
            }
            else {
                // std::cout << "(" << new_node.first << ")" << "is more than" << "(" << cur->pair.first << ")" << std::endl;
                // std::cout << "going right" << std::endl;
                cur->right = insert_node(cur->right, new_node, root);
                cur->right->parent = cur; // new parent
            }
            update_height(cur);
            // std::cout << "height update --> (" << cur->pair.first << ")-->" << cur->height << std::endl;
            int balance_factor = get_balance_factor(cur);
            // std::cout << "balance now --->(" << cur->pair.first << ") " << balance_factor << std::endl;

            // if the balance is more than 1 => left heavy => rotate right
            if (balance_factor > 1 && cur->pair.first < cur->left->pair.first) {
                // std::cout << "left heavy" << std::endl;
                // std::cout << "(" << cur->pair.first << ")" << "is less than" << "(" << cur->left->pair.second << ")" << std::endl;
                return rotate_right(cur);
            }
            // If the new node is in the right subtree of the left child of the current node, perform a left-right double rotation
            if (balance_factor > 1 && cur->pair.first > cur->left->pair.first) {
                // std::cout << "left heavy" << std::endl;
                // std::cout << "(" << cur->pair.first << ")" << "is more than" << "(" << cur->left->pair.first << ")" << std::endl;
                cur->left = rotate_left(cur->left);
                return rotate_right(cur);
            }
            // if the balance is more than 1 => right heavy => rotate left
            if (balance_factor < -1 && cur->pair.first < cur->right->pair.first) {
                // std::cout << "right heavy" << std::endl;
                // std::cout << "(" << cur->pair.first << ")" << "is less than" << "(" << cur->right->pair.first << ")" << std::endl;
                return rotate_left(cur);
            }
            // If the new node is in the left subtree of the right child of the current node, perform a right-left double rotation
            if (balance_factor < -1 && cur->pair.first > cur->right->pair.first ) {
                // std::cout << "right heavy" << std::endl;
                // std::cout << "(" << cur->pair.first << ")" << "is more than" << "(" << cur->right->pair.first << ")" << std::endl;
                cur->right = rotate_right(cur->right);
                return rotate_left(cur);
            }
            // std::cout << "returning " << cur->pair.first << std::endl;

            return cur;
        }
        //====================================================================//
        bool delete_node(Node* cur, Node* to_delete, Node* root) {
            if (cur == NULL)
                return false;
            if (to_delete->pair.first < cur->pair.first)  // move to the left subtree
                return (delete_node(cur->left, to_delete, root));
            else if (to_delete->pair.first > cur->pair.first) // move to the right subtree
                return (delete_node(cur->right, to_delete, root));
            else { // found the node to delete
                if (cur->left == nullptr || cur->right == nullptr) { // node has at most one child (or nothing)
                    Node* child = cur->left != nullptr ? cur->left : cur->right;
                    if (child != nullptr)
                        child->parent = cur->parent;
                    if (cur == root)
                        root = child;
                    else if (cur == cur->parent->left)
                        cur->parent->left = child;
                    else
                        cur->parent->right = child;
                    delete cur;
                    return true;
                }
                else { // node has two children
                    Node* successor = cur->right;
                    while (successor->left != NULL)
                        successor = successor->left;
                    cur->pair = successor->pair;
                    return delete_node(cur->right, successor, root);
                }
            }
            // re equilibrage
            update_height(cur);
            int balance = get_balance(cur);
            if (balance > 1 && get_balance(cur->left) >= 0) { // left-left case
                return rotate_right(cur, root);
            }
            if (balance > 1 && get_balance(cur->left) < 0) { // left-right case
                rotate_left(cur->left, root);
                return rotate_right(cur, root);
            }
            if (balance < -1 && get_balance(cur->right) <= 0) { // right-right case
                return rotate_left(cur, root);
            }
            if (balance < -1 && get_balance(cur->right) > 0) { // right-left case
                rotate_right(cur->right, root);
                return rotate_left(cur, root);
            }
            return true;
        }
        //====================================================================//
        Node* begin() {
            Node* n = _root;
            if (_root == NULL)
                return NULL;
            while (n->left != NULL)
                n = n->left;
            return n;
        }
        //--------------------------------------------------------------------//
        ft::Node<ft::pair<const K, T> > * begin() const {
            Node* n = _root;
            if (_root == NULL)
                return NULL;
            while (n->left != NULL)
                n = n->left;
            return (ft::Node<ft::pair<const K, T> > *)n;
        }
        //====================================================================//
        Node* end() {
            Node* n = _root;
            if (_root == NULL)
                return NULL;
            while (n->right != NULL)
                n = n->right;
            return n;
        }
        //--------------------------------------------------------------------//
        ft::Node<ft::pair<const K, T> > * end() const{
            Node* n = _root;
            if (_root == NULL)
                return NULL;
            while (n->right != NULL)
                n = n->right;
            return (ft::Node<ft::pair<const K, T> > *)n;
        }
        //====================================================================//
        iterator rbegin() {
            Node* current = _root;
            while (current && current->right)
                current = current->right;
            return iterator(current);
        }
        //--------------------------------------------------------------------//
        const_iterator rbegin() const {
            Node* current = _root;
            while (current && current->right)
                current = current->right;
            return const_iterator(current);
        }
        //====================================================================//
        iterator rend() {return iterator(NULL);}
        //--------------------------------------------------------------------//
        iterator rend() const {return const_iterator(NULL);}
        //====================================================================//
        std::size_t max_size() const {return (_alloc.max_size());}
        //====================================================================//
        void swap(AVL_tree& other) {
            std::swap(_root, other._root);
            std::swap(get_size(), other.get_size());
            std::swap(_alloc, other._alloc);
        }
        //====================================================================//
        bool contains_key(Node* curr, const value_type& node) { 
            if (curr == NULL)
                return false; // no doublon
            if (curr->pair.first == node.first)
                return true; // Key doublon ⛔️ 
            if (node.first < curr->pair.first)
                return contains_key(curr->left, node);
            else 
                return contains_key(curr->right, node);
        }
        //====================================================================//
        Node* search(Node* root, int val) {
            Node* n = root;
            if (n == NULL)
                return false;
            if (n->second == val)
                return true;
            while ((n && n->left) || (n && n->right)) {
                if (!tree_contains_val(n->left, val))
                    return (tree_contains_val(n->right, val));
            }
        }
        //====================================================================//
        void clear(Node* node) {
                if (node != nullptr) {
                    clear(node->left);
                    clear(node->right);
                    delete node;
                }
        }
        void clear() {
            clear(_root);
            _root = nullptr;
        }
        //====================================================================//
        iterator find(const key_type& k) {
            Node* curr = _root;
            // Traverse the tree until we find the key or reach a null node
            while (curr != nullptr) {
                if (k == curr->pair.first)
                    return iterator(curr);
                else if (k < curr->pair.first)
                    curr = curr->left;
                else
                    curr = curr->right;
            }
            return this->end();
        }
        //====================================================================//
        const_iterator find(const key_type& k) const {
            Node* curr = _root;
            // Traverse the tree until we find the key or reach a null node
            while (curr != nullptr) {
                if (k == curr->pair.first)
                    return (ft::Node<ft::pair<const K, T> > *)curr;
                else if (k < curr->pair.first)
                    curr = curr->left;
                else
                    curr = curr->right;
            }
            return (ft::Node<ft::pair<const K, T> > *)end();
        }
        //====================================================================//
        iterator lower_bound(const key_type& k) {
            Node* current = _root;
            Node* lower = nullptr;

            while (current) {
                if (current->pair.first < k)
                    current = current->right;
                else {
                    lower = current;
                    current = current->left;
                }
            }
            if (!lower)
                return end();
            return iterator(lower);
        }
        //--------------------------------------------------------------------//
        const_iterator lower_bound(const key_type& k) const {
            Node* current = _root;
            Node* lower = nullptr;

            while (current) {
                if (current->pair.first < k)
                    current = current->right;
                else {
                    lower = current;
                    current = current->left;
                }
            }
            if (!lower)
                return end();
            return (ft::Node<ft::pair<const K, T> > *)lower;
        }
        //====================================================================//
        iterator upper_bound(const key_type& k) {
            Node* current = _root;
            Node* upper = nullptr;

            while (current) {
                if (current->pair.first <= k)
                    current = current->right;
                else {
                    upper = current;
                    current = current->left;
                }
            }
            if (!upper)
                return end();
            return iterator(upper);
        }
        //--------------------------------------------------------------------//
        const_iterator upper_bound(const key_type& k) const {
            Node* current = _root;
            Node* upper = nullptr;

            while (current) {
                if (current->pair.first <= k)
                    current = current->right;
                else {
                    upper = current;
                    current = current->left;
                }
            }
            if (!upper)
                return end();
            return (ft::Node<ft::pair<const K, T> > *)upper;
        }
        //====================================================================//
        pair<iterator, iterator>   equal_range (const key_type& k) {
            iterator lower = find(k);
            iterator upper = lower;

            if (lower != end() && lower->first == k) {
                // If we found the key, move upper to the next node with a different key.
                ++upper;
                while (upper != end() && upper->first == k) {
                ++upper;
                }
            }
            return ft::make_pair(lower, upper);
        }
        //--------------------------------------------------------------------//
        pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
            const_iterator lower = find(k);
            const_iterator upper = lower;

            if (lower != end() && lower->first == k) {
                // If we found the key, move upper to the next node with a different key.
                ++upper;
                while (upper != end() && upper->first == k) {
                ++upper;
                }
            }
            return ft::make_pair(lower, upper);
        }
    };
}