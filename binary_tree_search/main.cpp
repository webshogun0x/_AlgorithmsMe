#include <iostream>
#include <memory>
#include <vector>
#include <optional>
#include <algorithm>

template<typename T>
class BinarySearchTree {
private:
    struct Node {
        T value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        
        explicit Node(const T& val) : value(val), left(nullptr), right(nullptr) {}
    };
    
    std::unique_ptr<Node> root;
    
    // Helper for inserting value recursively
    void insertRecursive(std::unique_ptr<Node>& node, const T& value) {
        if (!node) {
            node = std::make_unique<Node>(value);
            return;
        }
        
        if (value < node->value) {
            insertRecursive(node->left, value);
        } else if (value > node->value) {
            insertRecursive(node->right, value);
        }
        // Equal values are ignored (no duplicates)    
    }
    
    // Helper for in-order traversal
    void inOrderTraversalRecursive(const Node* node, std::vector<T>& result) const {
        if (!node) return;
        
        inOrderTraversalRecursive(node->left.get(), result);
        result.push_back(node->value);
        inOrderTraversalRecursive(node->right.get(), result);
    }
    
    // Helper to find minimum value node
    Node* findMin(Node* node) const {
        if (!node) return nullptr;
        
        while (node->left) {
            node = node->left.get();
        }
        return node;
    }
    
    // Helper for removing a value
    std::unique_ptr<Node> removeRecursive(std::unique_ptr<Node> node, const T& value) {
        if (!node) return nullptr;
        
        if (value < node->value) {
            node->left = removeRecursive(std::move(node->left), value);
        } else if (value > node->value) {
            node->right = removeRecursive(std::move(node->right), value);
        } else {
            // Case 1: No children or only one child
            if (!node->left) {
                return std::move(node->right);
            } else if (!node->right) {
                return std::move(node->left);
            }
            
            // Case 2: Two children
            // Find the inorder successor (smallest value in right subtree)
            Node* successor = findMin(node->right.get());
            node->value = successor->value;
            
            // Delete the successor
            node->right = removeRecursive(std::move(node->right), successor->value);
        }
        
        return std::move(node);
    }
    
    // Helper for finding a value
    bool containsRecursive(const Node* node, const T& value) const {
        if (!node) return false;
        
        if (value == node->value) {
            return true;
        } else if (value < node->value) {
            return containsRecursive(node->left.get(), value);
        } else {
            return containsRecursive(node->right.get(), value);
        }
    }
    
public:
    BinarySearchTree() : root(nullptr) {}
    
    // Insert a value into the BST
    void insert(const T& value) {
        insertRecursive(root, value);
    }
    
    // Check if a value exists in the BST
    bool contains(const T& value) const {
        return containsRecursive(root.get(), value);
    }
    
    // Remove a value from the BST
    void remove(const T& value) {
        root = removeRecursive(std::move(root), value);
    }
    
    // Return all values in sorted order
    std::vector<T> inOrderTraversal() const {
        std::vector<T> result;
        inOrderTraversalRecursive(root.get(), result);
        return result;
    }
    
    // Optional: get the minimum value
    std::optional<T> min() const {
        Node* minNode = findMin(root.get());
        if (minNode) {
            return minNode->value;
        }
        return std::nullopt;
    }
    
    // Check if the tree is empty
    bool isEmpty() const {
        return root == nullptr;
    }
};

// Example usage
int main() {
    BinarySearchTree<int> bst;
    
    // Insert values
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    for (int val : values) {
        bst.insert(val);
    }
    
    // Display in-order traversal
    std::cout << "In-order traversal: ";
    auto sorted = bst.inOrderTraversal();
    for (const auto& val : sorted) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Test search
    std::cout << "Contains 40: " << (bst.contains(40) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 100: " << (bst.contains(100) ? "Yes" : "No") << std::endl;
    
    // Find minimum
    if (auto minVal = bst.min()) {
        std::cout << "Minimum value: " << *minVal << std::endl;
    }
    
    // Test removal
    bst.remove(20);  // Remove leaf node
    std::cout << "After removing 20: ";
    for (const auto& val : bst.inOrderTraversal()) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    bst.remove(30);  // Remove node with one child
    std::cout << "After removing 30: ";
    for (const auto& val : bst.inOrderTraversal()) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    bst.remove(50);  // Remove root node
    std::cout << "After removing 50: ";
    for (const auto& val : bst.inOrderTraversal()) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    return 0;
}