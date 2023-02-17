template <typename KeyType, typename ValueType>
class map_iterator {
private:
    // Internal node struct for storing map nodes
    struct Node {
        KeyType key;
        ValueType value;
        Node* left;
        Node* right;
        Node* parent;
    };
    
    // Private iterator struct for iterating through the map
    struct iterator {
        Node* node;
        
        // Default constructor for iterator
        iterator() : node(NULL) {}
        
        // Constructor for iterator
        iterator(Node* n) : node(n) {}
        
        // Copy constructor for iterator
        iterator(const iterator& other) : node(other.node) {}
        
        // Assignment operator for iterator
        iterator& operator=(const iterator& other) {
            node = other.node;
            return *this;
        }
        
        // Prefix increment operator
        iterator& operator++() {
            if (node == NULL) return *this;
            if (node->right != NULL) {
                node = node->right;
                while (node->left != NULL) node = node->left;
            } else {
                while (node->parent != NULL && node == node->parent->right) node = node->parent;
                node = node->parent;
            }
            return *this;
        }
        
        // Postfix increment operator
        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        
        // Prefix decrement operator
        iterator& operator--() {
            if (node == NULL) return *this;
            if (node->left != NULL) {
                node = node->left;
                while (node->right != NULL) node = node->right;
            } else {
                while (node->parent != NULL && node == node->parent->left) node = node->parent;
                node = node->parent;
            }
            return *this;
        }
        
        // Postfix decrement operator
        iterator operator--(int) {
            iterator tmp(*this);
            --(*this);
            return tmp;
        }
        
        // Equality operator
        bool operator==(const iterator& other) const {
            return node == other.node;
        }
        
        // Inequality operator
        bool operator!=(const iterator& other) const {
            return node != other.node;
        }
        
        // Dereference operator
        std::pair<const KeyType, ValueType>& operator*() const {
            return std::make_pair(node->key, node->value);
        }
        
        // Arrow operator
        std::pair<const KeyType, ValueType>* operator->() const {
            return &(operator*());
        }
    };
    
public:
    // Public typedef for iterator
    typedef iterator const_iterator; 
    // Iterator begin function
    iterator begin() {
        if (root == NULL) return iterator(NULL);
        Node* n = root;
        while (n->left != NULL) n = n->left;
        return iterator(n);
    }
    // Iterator end function
    iterator end() {
        return iterator(NULL);
    }
};