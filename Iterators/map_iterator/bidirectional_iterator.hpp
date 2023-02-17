#pragma once
#include "../../ft_containers.hpp"
#include "node.hpp"

namespace ft {
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
    template <typename KeyType, typename ValueType>
    class bidirectional_iterator_tag {
        protected:
            Node* _node;
        public:
        //=========================================================//
        //   C O N S T R U C T O R S   &    D E S T R U C T O R    //
        //=========================================================//
        bidirectional_iterator_tag() : _node(NULL) {}
        bidirectional_iterator_tag(Node* n) : _node(n) {}
        bidirectional_iterator_tag(const iterator& cpy) : _node(cpy._node) {}
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
        // Prefix increment
        iterator& operator++() {
            if (_node == NULL)
                return *this;
            if (_node->right != NULL) {
                _node = _node->right;
                while (_node->left != NULL)
                    _node = _node->left;
            }
            else
                while (_node->parent != NULL && _node == _node->parent->right)
                    _node = _node->parent;
            return *this;
        }
        // Postfix increment
        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        // Prefix decrement operator
        iterator& operator--() {
            if (_node == NULL)
                return *this;
            if (_node->left != NULL) {
                _node = _node->left;
                while (_node->right != NULL) _node = _node->right;
            }
            else
                while (_node->parent != NULL && _node == _node->parent->left)
                    _node = _node->parent;
            return *this;
        }
        // Postfix decrement operator
        iterator operator--(int) {
            iterator tmp(*this);
            --(*this);
            return tmp;
        }
        //=========================================================//
        //        C O M P A R A I S O N         O P E R A T O R    //
        //=========================================================//
        // Equality operator
        bool operator==(const iterator& other) const {
            return _node == other._node;
        }
        // Inequality operator
        bool operator!=(const iterator& other) const {
            return _node != other._node;
        }
        // Dereference operator
        std::pair<const KeyType, ValueType>& operator*() const {
            return std::make_pair(_node->key, _node->value);
        }
        // Arrow operator
        std::pair<const KeyType, ValueType>* operator->() const {
            return &(operator*());
        }
    };
}