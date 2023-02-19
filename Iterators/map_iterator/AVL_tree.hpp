#pragma once
#include "../../ft_containers.hpp"
#include "pair.hpp"

namespace {
template<typename Key, typename T>
class AVL_tree {
public:
    class Node {
    public:
        Key key;
        T value;
        Node *left;
        Node *right;
        Node *parent;
        int height;
        Node(const Key& k, const T& v)
            : key(k), value(v), left(nullptr), right(nullptr), parent(nullptr), height(1) {}
    };
//============================================================================//
    class iterator {
    public:
        typedef ft::bidirectional_iterator_tag   iterator_category;
        typedef std::ptrdiff_t difference_type;
        typedef ft::pair<const Key, T>  value_type;
        typedef value_type* pointer;
        typedef value_type& reference;

        Node* node;
        AVL_tree* tree;

        iterator(Node* n, AVL_tree* t) : node(n), tree(t) {}

        bool operator==(const iterator& other) const {
            return node == other.node && tree == other.tree;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

        reference operator*() const {
            return std::make_pair(node->key, node->value);
        }

        pointer operator->() const {
            return &std::make_pair(node->key, node->value);
        }

        iterator& operator++() {
            if (node->right) {
                // Find the leftmost node in the right subtree
                node = node->right;
                while (node->left)
                    node = node->left;
            } else {
                // Go up the tree until we find a node whose left child we haven't visited yet
                Node* parent = node->parent;
                while (parent && node == parent->right) {
                    node = parent;
                    parent = parent->parent;
                }
                node = parent;
            }
            return *this;
        }

        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        iterator& operator--() {
            if (node == nullptr) {
                // The tree is empty, so return the end iterator
                node = tree->max_node(tree->_root);
            } else if (node->left) {
                // Find the rightmost node in the left subtree
                node = node->left;
                while (node->right)
                    node = node->right;
            } else {
                // Go up the tree until we find a node whose right child we haven't visited yet
                Node* parent = node->parent;
                while (parent && node == parent->left) {
                    node = parent;
                    parent = parent->parent;
                }
                node = parent;
            }
            return *this;
        }

        iterator operator--(int) {
            iterator tmp(*this);
            --(*this);
            return tmp;
        }
    };
//============================================================================//
    Node* _node;
    Node* _root;
        //====================================================================//
        //       C O N S T R U C T O R S      &      D E S T R U C T O R      //
        //====================================================================//
    AVL_tree() :            _node(NULL), _root(NULL) {}
    AVL_tree(Node &n) :     _node(n), _root(n) {}
    // AVL_tree(Node &cpy) :   _node(cpy._node) {}
    ~AVL_tree() {destroy(_root);}
        //===========================================================//
        int get_height(Node* node) {
            if (node == NULL)
                return 0;
            return node->height;
        }
        //===========================================================//
        int get_size() {
            if (_root == NULL)
                return 0;
            return (1 + size(_root->left) + size(_root->right));
            // adds 1 for each recursive call to count the current node that the function is operating on
        }
        //===========================================================//
        int get_balance_factor(Node* node) {
            if (node == NULL)
                return 0;
            return get_height(node->left) - get_height(node->right);
        }
        //===========================================================//
        void update_height(Node* node) {
            int left_height = get_height(node->left);
            int right_height = get_height(node->right);
            // --> https://www.youtube.com/watch?v=vRwi_UcZGjU
            node->height = std::max(left_height, right_height) + 1;
        }
        //===========================================================//
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
        //===========================================================//
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
        //===========================================================//
        // Inserts a new node with the given value `val` into an AVL tree rooted at `node`
        Node* insert_node(Node* node, int val) {
            // If the current node is null, create a new node with the given value and return it
            if (node == NULL) 
                return new Node(val);
            // Insert the new node in the left or right subtree depending on its value
            if (val < node->val)
                node->left = insert_node(node->left, val);
            else
                node->right = insert_node(node->right, val);
            update_height(node);
            int balance_factor = get_balance_factor(node);
            // if the balance is more than 1 => left heavy => rotate right
            if (balance_factor > 1 && val < node->left->val)
                return rotate_right(node);
            // If the new node is in the right subtree of the left child of the current node, perform a left-right double rotation
            if (balance_factor > 1 && val > node->left->val) {
                node->left = rotate_left(node->left);
                return rotate_right(node);
            }
            // if the balance is more than 1 => right heavy => rotate left
            if (balance_factor < -1 && val > node->right->val)
                return rotate_left(node);
            // If the new node is in the left subtree of the right child of the current node, perform a right-left double rotation
            if (balance_factor < -1 && val < node->right->val) {
                node->right = rotate_right(node->right);
                return rotate_left(node);
            }
            return node;
        }
        //===========================================================//
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
        Node* find_min(Node* node) {
            while (node->left != NULL)
                node = node->left;
            return node;
        }
        //====================================================================//
        bool tree_contains_val(Node* node, int val) {
            if (node == NULL)
                return false;
            if (node->val == val)
                return true;
            if (val < node->val)
                return tree_contains_val(node->left, val);
            else 
                return tree_contains_val(node->right, val);
        }
        //====================================================================//
        Node* search(Node* root, int val) {
            if (root == NULL || root->val == val)
                return root;
            if (val < root->val)
                return search(root->left, val);
            else
                return search(root->right, val);
        }
    };
}