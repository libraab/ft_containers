#pragma once
#include "../../ft_containers.hpp"

namespace ft {
    template<class T, class Key, class compare, class Alloc>
    class AVL_tree {
        private:
        //====================================//
        //               N O D E              //
        //====================================//
            struct Node {
                int val;
                int height;
                Node* left;
                Node* right;
                
                Node(int v) {
                    val = v;
                    height = 1;
                    left = NULL;
                    right = NULL; } };
        //===========================================================//
        int get_height(Node* node) {
            if (node == NULL) {
                return 0;
            }
            return node->height; }
        //===========================================================//
        int get_balance_factor(Node* node) {
            if (node == NULL) {
                return 0;
            }
            return get_height(node->left) - get_height(node->right);
        }
        //===========================================================//
        void update_height(Node* node) {
            int left_height = get_height(node->left);
            int right_height = get_height(node->right);
            // --> https://www.youtube.com/watch?v=vRwi_UcZGjU
            node->height = max(left_height, right_height) + 1; }
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
            Node* newLeft = new_root->left;
            new_root->left = node;
            node->right = new_left;
            update_height(node);
            update_height(new_root);
            return new_root;
        }
        //===========================================================//
        // Inserts a new node with the given value `val` into an AVL tree rooted at `node`
        Node* insert_node(Node* node, int val) {
            if (node == NULL) {
                // If the current node is null, create a new node with the given value and return it
                return new Node(val); }
            // Insert the new node in the left or right subtree depending on its value
            if (val < node->val) {
                node->left = insert_node(node->left, val);
            } else {
                node->right = insert_node(node->right, val);
            }
            update_height(node);
            int balance_factor = get_balance_factor(node);
            // if the balance is more than 1 => left heavy => rotate right
            if (balance_factor > 1 && val < node->left->val) {
                return rotate_right(node);
            }
            // If the new node is in the right subtree of the left child of the current node, perform a left-right double rotation
            if (balance_factor > 1 && val > node->left->val) {
                node->left = rotate_left(node->left);
                return rotate_right(node);
            }
            // if the balance is more than 1 => right heavy => rotate left
            if (balance_factor < -1 && val > node->right->val) {
                return rotate_left(node);
            }
            // If the new node is in the left subtree of the right child of the current node, perform a right-left double rotation
            if (balance_factor < -1 && val < node->right->val) {
                node->right = rotate_right(node->right);
                return rotate_left(node);
            }
            return node;
        }
        //===========================================================//
        Node* delete_node(Node* node, int val) {
            if (node == NULL) {return node;}
            if (val < node->val) { // move to the left subtree
                node->left = delete_node(node->left, val);
            } else if (val > node->val) { // move to the right subtree
                node->right = delete_node(node->right, val);
            } else { // if found 
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
            if (node == NULL) {return node;}
            update_height(node);
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
                return node;
            }
        }
        //====================================================================//
        Node* find_min(Node* node) {
            while (node->left != NULL) {
                node = node->left;
            }
            return node;
        }
    };
    //========================================================================//
    // --> https://cplusplus.com/reference/utility/pair/
    template <class T1, class T2>
    struct pair {
        // --> https://www.oreilly.com/library/view/c-in-a/059600298X/re854.html
        typedef T1 first_type;
        typedef T2 second_type;
        T1 first;
        T2 second;
        pair() : first(0), second(0) {} 
        pair(const T1& x, const T2& y) : first(x), second(0) {}
        template<typename U, typename V>
        pair(const pair<U, V> &p) : first(p.first), second(p.second) {}
    };
    //========================================================================//
    // --> https://cplusplus.com/reference/utility/make_pair/
    template <class T1,class T2>
    ft::pair<T1,T2> make_pair (T1 x, T2 y)
    { return ( pair<T1,T2>(x,y) ); }