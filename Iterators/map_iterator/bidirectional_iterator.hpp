#pragma once
#include "../../ft_containers.hpp"
#include "node.hpp"

namespace ft {
        template <typename T>
        class Node ;
/*██████╗     ██╗    ██████╗     ██╗    ██████╗     ███████╗     ██████╗    ████████╗    ██╗     ██████╗     ███╗   ██╗     █████╗     ██╗
  ██╔══██╗    ██║    ██╔══██╗    ██║    ██╔══██╗    ██╔════╝    ██╔════╝    ╚══██╔══╝    ██║    ██╔═══██╗    ████╗  ██║    ██╔══██╗    ██║
  ██████╔╝    ██║    ██║  ██║    ██║    ██████╔╝    █████╗      ██║            ██║       ██║    ██║   ██║    ██╔██╗ ██║    ███████║    ██║
  ██╔══██╗    ██║    ██║  ██║    ██║    ██╔══██╗    ██╔══╝      ██║            ██║       ██║    ██║   ██║    ██║╚██╗██║    ██╔══██║    ██║
  ██████╔╝    ██║    ██████╔╝    ██║    ██║  ██║    ███████╗    ╚██████╗       ██║       ██║    ╚██████╔╝    ██║ ╚████║    ██║  ██║    ███████╗
  ╚═════╝     ╚═╝    ╚═════╝     ╚═╝    ╚═╝  ╚═╝    ╚══════╝     ╚═════╝       ╚═╝       ╚═╝     ╚═════╝     ╚═╝  ╚═══╝    ╚═╝  ╚═╝    ╚══════╝
                    ██╗    ████████╗    ███████╗    ██████╗      █████╗     ████████╗     ██████╗     ██████╗
                    ██║    ╚══██╔══╝    ██╔════╝    ██╔══██╗    ██╔══██╗    ╚══██╔══╝    ██╔═══██╗    ██╔══██╗
                    ██║       ██║       █████╗      ██████╔╝    ███████║       ██║       ██║   ██║    ██████╔╝
                    ██║       ██║       ██╔══╝      ██╔══██╗    ██╔══██║       ██║       ██║   ██║    ██╔══██╗
                    ██║       ██║       ███████╗    ██║  ██║    ██║  ██║       ██║       ╚██████╔╝    ██║  ██║
                    ╚═╝       ╚═╝       ╚══════╝    ╚═╝  ╚═╝    ╚═╝  ╚═╝       ╚═╝        ╚═════╝     ╚═╝  ╚═*/
    // --> https://en.cppreference.com/w/cpp/iterator/bidirectional_iterator
    // --> https://cplusplus.com/reference/iterator/BidirectionalIterator/?kw=bidirectional+iterator
    template <class B>
    class bidirectional_iterator_tag {

        private :
			typedef bidirectional_iterator	        iterator;
	
            Node*               _root;
            Node*               _node;
            Node*               _prev_node;
            ft::stack<Node*>    _node_stack;
            ft::stack<Node*>    _prev_node_stack;
            //------------------------------------------------------------------
            void pushLeft(Node *n) {
                while (n) {
                    _node_stack.push(n);
                    n = n->left;
                }
            }
            //------------------------------------------------------------------
            void findPredecessor() {
                if (_node->left != nullptr) {
                    _prev_node = node->left;
                    while (_prev_node->right != nullptr)
                        _prev_node = _prev_node->right;
                } else {
                    _prev_node = nullptr;
                    Node *cur = _root;
                    while (cur != _node) {
                        if (cur->key < node->key) {
                            _prev_node = cur;
                            cur = cur->right;
                        } else
                            cur = cur->left;
                    }
                }
            }
            //------------------------------------------------------------------
            void findSuccessor() {
                if (_node->right != nullptr) {
                    _prev_node = _node->right;
                    while (_prev_node->left != nullptr)
                        _prev_node = _prev_node->left;
                } else {
                    prevNode = nullptr;
                    Node *cur = root;
                    while (cur != node) {
                        if (cur->key > node->key) {
                            prevNode = cur;
                            cur = cur->left;
                        } else
                            cur = cur->right;
                    }
                }
            }
        public:
        //=========================================================//
        //   C O N S T R U C T O R S   &    D E S T R U C T O R    //
        //=========================================================//
        bidirectional_iterator_tag() : _node(nullptr), _prev_node(nullptr) {}
        bidirectional_iterator_tag(Node *n) : _node(n), _prev_node(nullptr) {pushLeft(n);}
        bidirectional_iterator_tag(const bidirectional_iterator_tag &other) { 
            _node = other._node;
            _prev_node = other._prev_node;
            _node_stack = other._node_stack;
            _prev_node_stack = other._prev_node_stack;
        }
        ~bidirectional_iterator_tag() {}
        //=========================================================//
        //        A S S I G N M E N T           O P E R A T O R    //
        //=========================================================//
        iterator& operator=(const iterator& other) {
            _node = other._node;
            return *this;
        }
        //=========================================================//
        //   I N C R E M E N T       &         D E C R E M E N T   //
        //=========================================================//
        Iterator& operator++() { // prefix increment
            if (_node_stack.empty()) {
                _node = nullptr;
                return *this;
            }
            _node = _node_stack.top();
            _node_stack.pop();
            _prev_node = _node;
            _prev_node_stack.push(_node);
            pushLeft(_node->right);
            return *this;
        }
        Iterator operator++(int) { // postfix increment
            Iterator tmp(*this);
            operator++();
            return tmp;
        }
        Iterator& operator--() { // prefix decrement
            if (_prev_node_stack.empty()) {
                _node = nullptr;
                return *this;
            }
            _prev_node = _prev_node_stack.top();
            _prev_node_stack.pop();
            _node = _prev_node;
            pushLeft(_node->left);
            return *this;
        }
        Iterator operator--(int) { // postfix decrement
            Iterator tmp(*this);
            operator--();
            return tmp;
        }
        //=========================================================//
        //        C O M P A R A I S O N         O P E R A T O R    //
        //=========================================================//
        // Equality operator
        bool operator==(const iterator& other) const {
            return (_node == other._node);
        }
        // Inequality operator
        bool operator!=(const iterator& other) const {
            return (!(_node == other._node));
        }
        // Dereference operator
        ft::pair<const key_type, value_type>& operator*() const {
            return (ft::make_pair(_node->key, _node->value));
        }
        // Arrow operator
        ft::pair<const key_type, value_type>* operator->() const {
            return &(operator*());
        }
    };
}