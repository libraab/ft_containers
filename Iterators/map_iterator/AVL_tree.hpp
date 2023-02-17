#pragma once
#include "../../ft_containers.hpp"
//#include "pair.hpp"
#include "node.hpp"

namespace ft {
    template<class T, class Key, class compare, class Alloc>
    class AVL_tree {
        protected:     
            Node node;
        //====================================================================//
        //       C O N S T R U C T O R S      &      D E S T R U C T O R      //
        //====================================================================//
        public:
            AVL_tree() : node(NULL) {}
            AVL_tree(node &n) : node(n) {}
            AVL_tree(node &cpy) : node(cpy.node) {}
            ~AVL_tree() {}
        //===========================================================//
        int get_height(Node* node) {
            if (node == NULL)
                return 0;
            return node->height;
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
                return node;
            }
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