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
        // CONSTRUCTOR    
        Node(P p) : pair(p), height(1), left(NULL), right(NULL), parent(NULL) {}
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
        Compare                             _comp;
        bool                _start;
        bool                _end;
        Node*               _save;

        biterator(Compare comp = Compare()) :                       _node(NULL), _comp(comp), _start(false), _end(false) {}
        biterator(Node* n, Compare comp = Compare()) :              _node(n), _comp(comp), _start(false), _end(false) {}
        biterator(biterator const & x) :                            _node(x._node), _comp(x._comp), _start(x._start), _end(x._end), _save(x._save) {}
        ~biterator() {};
        //--------------------------------------------------------------------//
        // // Assignment operator
        // biterator & operator=(biterator const & rhs) {
        //     if (this != &rhs) {
        //         this->_node = rhs._node;
        //     }
        //     return (*this);
        // }
        //--------------------------------------------------------------------//
        // Comparison operators
        bool operator==(biterator const & rhs) const { return (this->_node == rhs._node); }
        bool operator!=(biterator const & rhs) const { return (this->_node != rhs._node); }
        //--------------------------------------------------------------------//
        // Dereference operators
        reference operator*() const { return (this->_node->pair); }
        pointer operator->() const { return &(this->_node->pair); }
        //--------------------------------------------------------------------//
        // Node* get_next(Node* a) {
        //     Node* cur = a;
        //     if (cur->right != NULL) {
        //         cur = cur->right;
        //         // Find the leftmost node in the right subtree
        //         while (cur->left != NULL)
        //             cur = cur->left;
        //     } else {
        //         // Go up the tree until we find a node whose left child we haven't visited yet
        //         Node *tmp = cur;
        //         while (tmp->parent != NULL) 
        //             tmp = tmp->parent;
        //         K key = cur->pair.first;
        //         while (tmp->left && _comp(key, tmp->left->pair.first)) 
        //             tmp = tmp->left;
        //         if (_comp(key, tmp->pair.first) && key != tmp->pair.first) {
        //             cur = tmp;
        //             return cur;
        //         }
        //         if (tmp->right)
        //             tmp = tmp->right;
        //         while (tmp->right && _comp(tmp->right->pair.first, key))
        //             tmp = tmp->right;
        //         while (tmp->left && _comp(key, tmp->left->pair.first))
        //             tmp = tmp->left;
        //         if (key == tmp->pair.first)
        //             cur =  NULL;
        //         else if (_comp(key, tmp->pair.first))
        //             cur = tmp;
        //         else
        //             cur = NULL;
        //     }
        //     return cur;
        // }
        Node* next(Node *begin, Node* search) {
            if (begin == NULL)
                return NULL;
            // std::cout << "ENTRER: " << i << std::endl;
            Node* tmp = NULL;
            if (_comp(search->pair.first, begin->pair.first)) {
                tmp = begin;
            }
            // std::cout << "WESH" << std::endl;
            Node* left = next(begin->left, search);
            Node* right = next(begin->right, search);
            // std::cout << "WESH2" << std::endl;
            if (left && _comp(search->pair.first, left->pair.first)) {
                if ((tmp && _comp(left->pair.first, tmp->pair.first)) || tmp == NULL) {
                    tmp = left;
                }
            }
            if (right && _comp(search->pair.first, right->pair.first)) {
                if ((tmp && _comp(right->pair.first, tmp->pair.first)) || tmp == NULL) {
                    tmp = right;
                }
            }
            return (tmp);
        }

        Node* get_next(Node* a) {
            Node* tmp = a;
            while (tmp->parent != NULL)
                tmp = tmp->parent;
            return next(tmp, a);
        }

        Node* get_prev(Node* a) {
            Node* cur = a;
            if (cur && cur->left != NULL) {
                cur = cur->left;
                // Find the rightmost node in the left subtree
                while (cur->right != NULL)
                    cur = cur->right;
            } else if (cur) {
                // Go up the tree until we find a node whose left child we haven't visited yet
                Node *tmp = cur->parent;
                while (tmp && cur == tmp->left) {
                    cur = tmp;
                    tmp = tmp->parent;
                }
                cur = tmp;
            }
            return cur;
        }
        // Increment/decrement operators
        biterator & operator++() {
            if (_start == true) { // did a -- before and am on null currently, next value is save
                _node = _save;
                _start = false;
                return *this;
            }
            if (_end == true) {
                _node = NULL;
                return *this;
            }
            Node* next = get_next(_node);
            if (next == NULL) {
                _save = _node;
                _end = true;
            }
            _node = next;
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
            if (_end == true) { // did a ++ before and am on null currently, next value is save
                _node = _save;
                _end = false;
                return *this;
            }
            if (_start == true) {
                _node = NULL;
                return *this;
            }
            Node* next = get_prev(_node);
            if (next == NULL) {
                _save = _node;
                _start = true;
            }
            _node = next;
            return *this;
        }
        //--------------------------------------------------------------------//
        biterator operator--(int) {
            biterator tmp(*this);
            operator--();
            return tmp;}
    };
//==========================================================================//
//                      C O N S T                                           //
//==========================================================================//
    template <typename K, typename T, class Compare, class Alloc>
    class const_biterator {
        public :
        typedef std::bidirectional_iterator_tag             iterator_category;
        typedef std::ptrdiff_t                              difference_type;
        typedef ft::pair<K, T>                        value_type;
        typedef value_type const *                           pointer;
        typedef value_type const &                           reference;
        typedef Node<value_type>                      Node;

        Node*                               _node;
        Compare                             _comp;
        bool                _start;
        bool                _end;
        Node*               _save;

        const_biterator(Compare comp = Compare()) :             _node(NULL), _comp(comp), _start(false), _end(false) {}
        const_biterator(Node* n, Compare comp = Compare()) :    _node(n), _comp(comp), _start(false), _end(false) {}
        const_biterator(const_biterator const& x) {
            _node = x._node;
            _comp = x._comp;
            _start = x._start;
            _end = x._end;
            _save = x._save;
        }
        const_biterator(biterator<K,T,Compare,Alloc> x) {
            _node = x._node;
            _comp = x._comp;
            _start = x._start;
            _end = x._end;
            _save = x._save;
        }
        ~const_biterator() { };
        //--------------------------------------------------------------------//
        // Comparison operators
        bool operator==(const_biterator const & rhs) const { return (this->_node == rhs._node); }
        bool operator!=(const_biterator const & rhs) const { return (this->_node != rhs._node); }
        //--------------------------------------------------------------------//
        // Dereference operators
        reference operator*() const { return (this->_node->pair); }
        pointer operator->() const { return &(this->_node->pair); }
        //--------------------------------------------------------------------//
        Node* next(Node *begin, Node* search) {
            if (begin == NULL)
                return NULL;
            // std::cout << "ENTRER: " << i << std::endl;
            Node* tmp = NULL;
            if (_comp(search->pair.first, begin->pair.first)) {
                tmp = begin;
            }
            // std::cout << "WESH" << std::endl;
            Node* left = next(begin->left, search);
            Node* right = next(begin->right, search);
            // std::cout << "WESH2" << std::endl;
            if (left && _comp(search->pair.first, left->pair.first)) {
                if ((tmp && _comp(left->pair.first, tmp->pair.first)) || tmp == NULL) {
                    tmp = left;
                }
            }
            if (right && _comp(search->pair.first, right->pair.first)) {
                if ((tmp && _comp(right->pair.first, tmp->pair.first)) || tmp == NULL) {
                    tmp = right;
                }
            }
            return (tmp);
        }

        Node* get_next(Node* a) {
            Node* tmp = a;
            while (tmp->parent != NULL)
                tmp = tmp->parent;
            return next(tmp, a);
        }

        Node* get_prev(Node* a) {
            // std::cout << "start get prev" << std::endl;
            Node* cur = a;
            if (cur && cur->left != NULL) {
            // std::cout << "first if" << std::endl;
                cur = cur->left;
                // Find the rightmost node in the left subtree
                while (cur->right != NULL)
                    cur = cur->right;
            } else if (cur) {
            // std::cout << "in else" << std::endl;
                // Go up the tree until we find a node whose left child we haven't visited yet
                Node *tmp = cur->parent;
                while (tmp && cur == tmp->left) {
                    cur = tmp;
                    tmp = tmp->parent;
                }
                cur = tmp;
            }
            // std::cout << "end get prev" << std::endl;
            return cur;
        }
        // Increment/decrement operators
        const_biterator & operator++() {
            // std::cout << "const_it -- start ++" << std::endl;
            if (_start == true) { // did a -- before and am on null currently, next value is save
                _node = _save;
                _start = false;
            // std::cout << "const_it -- start ++ start is false" << std::endl;
                return *this;
            }
            if (_end == true) {
                _node = NULL;
            // std::cout << "const_it -- start ++ end true second if" << std::endl;
                return *this;
            }
            Node* next = get_next(_node);
            if (next == NULL) {
                _save = _node;
                _end = true;
            // std::cout << "const_it -- start ++ end tree third if" << std::endl;
            }
            // std::cout << "const_it -- start ++ before return " << _start << " " <<_end << std::endl;
            _node = next;
            return *this;
        }
        //--------------------------------------------------------------------//
        const_biterator operator++(int) {
            const_biterator tmp(*this);
            operator++();
            return (tmp);
        }
        //--------------------------------------------------------------------//
        const_biterator & operator--() {
            if (_end == true) { // did a ++ before and am on null currently, next value is save
                _node = _save;
                _end = false;
                return *this;
            }
            if (_start == true) {
                _node = NULL;
        //    std::cout << "after line 319 --" << std::endl;
                return *this;
            }
            // std::cout << "arrive here" << std::endl;
         
            // if (_node != NULL)
            //     // std::cout << "NODE IS not NULLLLLL" << std::endl;
            // else
                // std::cout << "NODE IS NULLLLLL" << std::endl;
            Node* next = get_prev(_node);
            // std::cout << "after get prev" << std::endl;
            if (next == NULL) {
                _save = _node;
                _start = true;
            }
            _node = next;
        //    std::cout << "after line 328 --" << std::endl;
            return *this;
        }
        //--------------------------------------------------------------------//
        const_biterator operator--(int) {
            const_biterator tmp(*this);
            operator--();
            return tmp;
        }
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
        typedef ft::const_biterator<K, T, Compare, Alloc>       const_iterator;
        typedef K                                               key_type;

        Node*               _root;
        size_t              _size;
        allocator_type      _alloc;
        Compare             _comp;
        //====================================================================//
        //      C O N S T R U C T O R S       &      D E S T R U C T O R      //
        //====================================================================//
        AVL_tree(Compare comp = Compare()) :            _root(NULL), _size(0), _alloc(allocator_type()), _comp(comp) {}
        AVL_tree(Node &n, Compare comp = Compare()) :     _root(n), _size(0), _alloc(allocator_type()), _comp(comp) {}
        ~AVL_tree() {clear();}
        // //====================================================================//
        // // Helper function to recursively copy a node and its children
        // Node* copy_node(const Node* node) {
        //     if (node == NULL)
        //         return NULL;
        //     Node* new_node = new Node(node->value);
        //     new_node->height = node->height;
        //     new_node->left = copy_node(node->left);
        //     new_node->right = copy_node(node->right);
        //     return new_node;
        // }
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
        allocator_type get_allocator() const {return _alloc;}
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
        //====================================================================//
        void print_tree() const {print_tree(_root);}
        void print_tree(Node* node, std::string indent = "", bool right = false) const {
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
                std::cout << node->pair.first << "(" << node->pair.second << ")" << std::endl;
                print_tree(node->left, indent, false);
                print_tree(node->right, indent, true);
            }
        }
        const_iterator begin() const {
            Node* n = _root;
            if (_root == NULL)
                return (NULL);
            while (n->left != NULL)
                n = n->left;
            return const_iterator(n);
        }
        //====================================================================//
        // Inserts a new node with the given value `val` into an AVL tree rooted at `node`
        Node* insert_node(Node* cur, const value_type& new_node) {
            // std::cout << "" << std::endl;               
            if (cur == NULL) { // arriving at null node
                Node* x = new Node(new_node); // creating the new node on it
                _size++;
                return (x); // return this node (recursively)
            }
            // Insert the new node in the left or right subtree depending on its value

            if (_comp(new_node.first, cur->pair.first)) {
                // std::cout << "(" << new_node.first << ")" << "is less than" << "(" << cur->pair.first << ")" << std::endl;
                // std::cout << "going left" << std::endl;
                cur->left = insert_node(cur->left, new_node);
                cur->left->parent = cur; // new parent
            }
            else {
                // std::cout << "(" << new_node.first << ")" << "is more than" << "(" << cur->pair.first << ")" << std::endl;
                // std::cout << "going right" << std::endl;
                cur->right = insert_node(cur->right, new_node);
                cur->right->parent = cur; // new parent
            }
            update_height(cur);
            // std::cout << "height update --> (" << cur->pair.first << ")-->" << cur->height << std::endl;
            int balance_factor = get_balance_factor(cur);
            // std::cout << "balance now --->(" << cur->pair.first << ") " << balance_factor << std::endl;

            // if the balance is more than 1 => left heavy => rotate right
            if (balance_factor > 1 && (_comp(cur->pair.first, cur->left->pair.first))) {
                // std::cout << "left heavy" << std::endl;
                // std::cout << "(" << cur->pair.first << ")" << "is less than" << "(" << cur->left->pair.second << ")" << std::endl;
                return rotate_right(cur);
            }
            // If the new node is in the right subtree of the left child of the current node, perform a left-right double rotation
            if (balance_factor > 1 && (_comp(cur->pair.first, cur->left->pair.first))) {
                // std::cout << "left heavy" << std::endl;
                // std::cout << "(" << cur->pair.first << ")" << "is more than" << "(" << cur->left->pair.first << ")" << std::endl;
                cur->left = rotate_left(cur->left);
                return rotate_right(cur);
            }
            // if the balance is more than 1 => right heavy => rotate left
            if (balance_factor < -1 && (_comp(cur->pair.first, cur->right->pair.first))) {
                // std::cout << "right heavy" << std::endl;
                // std::cout << "(" << cur->pair.first << ")" << "is less than" << "(" << cur->right->pair.first << ")" << std::endl;
                return rotate_left(cur);
            }
            // If the new node is in the left subtree of the right child of the current node, perform a right-left double rotation
            if (balance_factor < -1 && (_comp(cur->pair.first, cur->right->pair.first))) {
                // std::cout << "right heavy" << std::endl;
                // std::cout << "(" << cur->pair.first << ")" << "is more than" << "(" << cur->right->pair.first << ")" << std::endl;
                cur->right = rotate_right(cur->right);
                return rotate_left(cur);
            }
            // print_tree();
            return cur;
        }
        //====================================================================//
        void insert_real_node(Node* node) {
            if (node == NULL)
                return;
            K key = node->pair.first;
            Node* tmp = _root;
            while (1) {
                if (_comp(key, tmp->pair.first)) {
                    if (tmp->left == NULL) {
                        tmp->left = node;
                        tmp->left->parent = tmp; 
                        return;
                    }
                    tmp = tmp->left;
                }
                else {
                    if (tmp->right == NULL) {
                        tmp->right = node;
                        tmp->right->parent = tmp;
                        return;
                    }
                    tmp = tmp->right;
                }
            }
            if (node->parent)
                equilibrium(node->parent);
            return;
        }
        //====================================================================//
        Node* insert(const value_type& new_node) {
            Node* x;
            if (get_root() == NULL) { // no existing tree 
                x = new Node(new_node); // creating first node of the tree
                _root = x; // which _root is itself
                _size++; 
            }
            else { // existing tree
                insert_node(get_root(), new_node);
                x = find_node(new_node.first);
            }
            // print_tree();
            return x;
        }
        //====================================================================//
        void equilibrium(Node* cur) {
            while (cur) {
                update_height(cur);
                int balance = get_balance_factor(cur);
                if (balance > 1 && get_balance_factor(cur->left) >= 0) { // left-left case
                    rotate_right(cur);
                }
                else if (balance > 1 && get_balance_factor(cur->left) < 0) { // left-right case
                    rotate_left(cur->left);
                    rotate_right(cur);
                }
                else if (balance < -1 && get_balance_factor(cur->right) <= 0) { // right-right case
                    rotate_left(cur);
                }
                else if (balance < -1 && get_balance_factor(cur->right) > 0) { // right-left case
                    rotate_right(cur->right);
                    rotate_left(cur);
                }
                cur = cur->parent; // to go up 
            }
            // When you delete a node from an AVL tree,
            // you must balance the tree starting from the parent of the deleted node
            //and work your way up the tree until you reach the root. 
        }
        //====================================================================//
        bool delete_node(iterator to_delete) {
            // std::cout << "about to delete -> " << to_delete._node->pair.first << std::endl;
            // print_tree();
            if (!to_delete._node || _size == 0)
                return false;
            
            // std::cout << "root is " << _root->pair.first << _root->pair.second << std::endl;
            // std::cout << "to delete is " << to_delete._node->pair.first << to_delete._node->pair.second << std::endl;
            // print_tree();
            Node *p = to_delete._node->parent; // if p == NULL that means it's the root
            Node *l = to_delete._node->left;
            Node *r = to_delete._node->right;
            // case 1 : delete root
            if (!p || to_delete._node == _root) { // it has no parent -> it's the root
                if (!r && !l) { // case 1a : root has no children
                    _root = NULL;
                }
                else if (r && l) { // case 1b : root has 2 children
                    l->parent = NULL; 
                    _root = l; // left becomes root
                    insert_real_node(r);
                    equilibrium(_root);
                }
                else { // case 1c : root has just one child
                    if (l) {
                        l->parent = NULL;
                        _root = l; // left becomes root
                    }
                    else {
                        r->parent = NULL;
                        _root = r; // right becomes root
                    }
                }
            } // case 2 : node is not root so it has parent
            else { // need to know if he's left or right
                if (to_delete._node == p->left)
                    p->left = NULL;
                else
                    p->right = NULL;
                if (l)
                    insert_real_node(l);
                if (r)
                    insert_real_node(r);
                equilibrium(p);

            }
            delete to_delete._node;
            to_delete._node = NULL;
            _size--;
            // std::cout << "element is deleted " << std::endl;
            // print_tree();
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
        const_iterator end() const{
            Node* n = _root;
            if (_root == NULL)
                return NULL;
            while (n->right != NULL)
                n = n->right;
            
            return const_iterator(n);
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
            std::swap(_size, other._size);
            std::swap(_alloc, other._alloc);
        }
        //====================================================================//
        bool contains_key(Node* curr, const value_type& node) { 
            if (curr == NULL)
                return false; // no doublon
            if (curr->pair.first == node.first)
                return true; // Key doublon ⛔️ 
            if (_comp(node.first, curr->pair.first))
                return contains_key(curr->left, node);
            else 
                return contains_key(curr->right, node);
        }
        bool contains_key(iterator curr, const value_type& node) {
            if (curr._node->pair.first == node.first)
                return true;
            return false;}
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
            if (node != NULL) {
                clear(node->left);
                clear(node->right);
                delete node;
                _size--;
                node = NULL;
            }
        }
        void clear() {
            clear(_root);
            _root = NULL;
        }
        //====================================================================//
        iterator find(const key_type& k) {
            Node* curr = _root;
            // Traverse the tree until we find the key or reach a null node
            while (curr != nullptr) {
                if (k == curr->pair.first)
                    return iterator(curr);
                else if (_comp(k, curr->pair.first))
                    curr = curr->left;
                else
                    curr = curr->right;
            }
            return iterator(NULL);
        }
        //====================================================================//
        const_iterator find(const key_type& k) const {
            Node* curr = _root;
            // Traverse the tree until we find the key or reach a null node
            while (curr != nullptr) {
                if (k == curr->pair.first)
                    return (ft::Node<ft::pair<K, T> > *)curr;
                else if (_comp(k, curr->pair.first))
                    curr = curr->left;
                else
                    curr = curr->right;
            }
            return const_iterator(end());
        }
        //====================================================================//
        Node* find_node(const key_type& k) const {
            Node* current = _root;
            while (current != nullptr) {
                if (_comp(k, current->pair.first))
                    current = current->left;
                else if (_comp(current->pair.first, k))
                    current = current->right;
                else
                    return current;
            }
            return nullptr;
        }
        //====================================================================//
        iterator lower_bound(const key_type& k) {
            Node* current = _root;
            Node* lower = nullptr;

            while (current) {
                if (_comp(current->pair.first, k))
                    current = current->right;
                else {
                    lower = current;
                    current = current->left;
                }
            }
            if (!lower) {
                iterator x = end();
                x++;
                return x;
            }
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
            if (!lower) {
                const_iterator x = end();
                x++;
                return x;
            }
            return (ft::Node<ft::pair<K, T> > *)lower;
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
            if (!upper) {
                iterator x = end();
                x++;
                return x;
            }
            return iterator(upper);
        }
        //--------------------------------------------------------------------//
        const_iterator upper_bound(const key_type& k) const {
            Node* current = _root;
            Node* upper = nullptr;

            while (current) {
                if (_comp(k, current->pair.first)) {
                    upper = current;
                    current = current->left;
                }
                else
                    current = current->right;
            }
            if (!upper) {
                const_iterator x = end();
                x++;
                return x;
            }
            return (ft::Node<ft::pair<K, T> > *)upper;
        }
        //====================================================================//
        pair<iterator, iterator>   equal_range (const key_type& k) {
return (ft::make_pair(lower_bound(k), upper_bound(k)));
        }
        //--------------------------------------------------------------------//
        pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
            return (ft::make_pair(lower_bound(k), upper_bound(k)));}
    };
}