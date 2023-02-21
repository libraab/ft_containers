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
        //Node*           nil;          
        // CONSTRUCTOR    
        Node(P p) : pair(p), height(1),/* nil(NULL),*/ left(NULL), right(NULL) {}
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
        typedef Node<K>  Node;
        typedef ft::pair<K, T>  value_type;
        typedef Alloc       allocator_type;

        Node*               _current_node;
        Node*               _root;
        allocator_type      _alloc;
        //====================================================================//
        //      C O N S T R U C T O R S       &      D E S T R U C T O R      //
        //====================================================================//
        AVL_tree() :            _current_node(NULL), _root(NULL), _alloc(allocator_type()) {}
        AVL_tree(Node &n) :     _current_node(n), _root(n), _alloc(allocator_type()) {}
        ~AVL_tree() {clear(_root);}
        //====================================================================//
        int get_height(Node* node) {
            if (node == NULL)
                return 0;
            return node->height;
        }
        //====================================================================//
        int get_size() {
            if (_root == NULL)
                return 0;
            return (1 + _root->left.size() + _root->right.size());
            // adds 1 for each recursive call to count the current node that the function is operating on
        }
        //====================================================================//
        int get_balance_factor(Node* node) {
            if (node == NULL)
                return 0;
            return get_height(node->left) - get_height(node->right);
        }
        //====================================================================//
        Node* get_parent(Node* root, int key) {
            Node* previous = NULL;
            Node* current = root;

            while (current != NULL) {
                if (current->first >= key) {
                    current = current->left;
                } else {
                    previous = current;
                    current = current->right;
                }
            }
            return previous;
        }
        //====================================================================//
        Node* get_root() {return _root;}
        //====================================================================//
        void update_height(Node* node) {
            int left_height = get_height(node->left);
            int right_height = get_height(node->right);
            // --> https://www.youtube.com/watch?v=vRwi_UcZGjU
            node->height = std::max(left_height, right_height) + 1;
        }
        //====================================================================//
        Node* rotate_right(Node* node) {
            // not possible if the left node is null
            Node* new_root = node->left;
            Node* new_right = new_root->right;
            new_root->right = node;
            node->left = new_right;
            update_height(node);
            update_height(new_root);
            return new_root;
        }
        //====================================================================//
        Node* rotate_left(Node* node) {
            // not possible if the right node is null
            Node* new_root = node->right;
            Node* new_left = new_root->left;
            new_root->left = node;
            node->right = new_left;
            update_height(node);
            update_height(new_root);
            return new_root;
        }
        //====================================================================//
        // Inserts a new node with the given value `val` into an AVL tree rooted at `node`
        Node* insert_node(Node* cur, const value_type& new_node) {
            // If the current _root is null, create a new node with the given value and return it
            if (cur == NULL)
                return new Node(new_node); // which _root is new_node
            // Insert the new node in the left or right subtree depending on its value
            if (new_node->first < cur->first)
                cur->left = insert_node(cur->left, new_node);
            else
                cur->right = insert_node(cur->right, new_node);
            update_height(cur);
            int balance_factor = get_balance_factor(cur);
            // if the balance is more than 1 => left heavy => rotate right
            if (balance_factor > 1 && cur->first < cur->left->first)
                return rotate_right(cur);
            // If the new node is in the right subtree of the left child of the current node, perform a left-right double rotation
            if (balance_factor > 1 && cur->first > cur->left->first) {
                cur->left = rotate_left(cur->left);
                return rotate_right(cur);
            }
            // if the balance is more than 1 => right heavy => rotate left
            if (balance_factor < -1 && cur->first > cur->right->first)
                return rotate_left(cur);
            // If the new node is in the left subtree of the right child of the current node, perform a right-left double rotation
            if (balance_factor < -1 && cur->first < cur->right->first) {
                cur->right = rotate_right(cur->right);
                return rotate_left(cur);
            }
            return cur;
        }
        //====================================================================//
        Node* delete_node(Node* node, int val) {
            if (node == NULL)
                return node;
            if (val < node->val) // move to the left subtree
                node->left = delete_node(node->left, val);
            else if (val > node->val) // move to the right subtree
                node->right = delete_node(node->right, val);
            else { // if found 
                if (node->left == NULL && node->right == NULL) { // if no children => delete the node
                    delete node;
                    node = NULL;
                } else if (node->left == NULL) { // if one child => move it to the node 
                    Node* temp = node;
                    node = node->right; 
                    delete temp; 
                } else if (node->right == NULL) {
                    Node* temp = node;
                    node = node->left;
                    delete temp;
                } else { // if it has 2 children
                    Node* temp = find_min(node->right);
                    node->val = temp->val;
                    node->right = delete_node(node->right, temp->val);
                }
            }
            if (node == NULL)
                return node;
            update_height(node);
            // re equilibrage
            int balance_factor = get_balance_factor(node);
            if (balance_factor > 1) { // if left-heavy
                if (get_balance_factor(node->left) >= 0) // if left is also heavy
                    return rotate_right(node);
                else {
                    node->left = rotate_left(node->left); // else double rotation
                    return rotate_right(node);
                }
            }
            if (balance_factor < -1) { // if right-heavy
                if (get_balance_factor(node->right) <= 0)// if right heavy too
                    return rotate_left(node);
                else {
                    node->right = rotate_right(node->right);
                    return rotate_left(node);
                }
            }
            return node;
        }
        //====================================================================//
        Node* find_min() {
            Node* n = _root;
            while (n->left != NULL)
                n = n->left;
            return n;
        }
        //====================================================================//
        Node* find_max() {
            Node* n = _root;
            while (n->right != NULL)
                n = n->right;
            return n;
        }
        //====================================================================//
        bool contains_key(Node* curr, const value_type& node) { 
            if (curr == NULL)
                return false; // no doublon
            if (curr.pair->first == node->first)
                return true; // Key doublon ⛔️ 
            if (node->first < curr->first)
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

        typedef Node<K> Node;
        typedef AVL_tree<K, T, Compare, Alloc>      AVL_tree;

        Node*                 _node;
        AVL_tree*             _tree;

        biterator(Node* n, AVL_tree* t) : _node(n), _tree(t) {}

        bool operator==(const biterator& other) const 
        {return _node == other._node && _tree == other._tree;}

        bool operator!=(const biterator& other) const 
        {return !(*this == other);}

        reference operator*() const
        {return ft::make_pair(_node->first, _node->second);}

        pointer operator->() const
        {return &ft::make_pair(_node->first, _node->second);}

        biterator& operator++() {
            if (_node->right) {
                // Find the leftmost node in the right subtree
                _node = _node->right;
                while (_node->left)
                    _node = _node->left;
            } else {
                // Go up the tree until we find a node whose left child we haven't visited yet
                Node* parent = _node->parent;
                while (parent && _node == parent->right) {
                    _node = parent;
                    parent = parent->parent;
                }
                _node = parent;
            }
            return *this;
        }

        biterator operator++(int) {
            biterator tmp(*this);
            ++(*this);
            return tmp;
        }

        biterator& operator--() {
            if (_node == nullptr) {
                // The tree is empty, so return the end iterator
                _node = _tree->max_node(_tree->_root);
            } else if (_node->left) {
                // Find the rightmost node in the left subtree
                _node = _node->left;
                while (_node->right)
                    _node = _node->right;
            } else {
                // Go up the tree until we find a node whose right child we haven't visited yet
                Node* parent = _node->parent;
                while (parent && _node == parent->left) {
                    _node = parent;
                    parent = parent->parent;
                }
                _node = parent;
            }
            return *this;
        }

        biterator operator--(int) {
            biterator tmp(*this);
            --(*this);
            return tmp;
        }
    };
}