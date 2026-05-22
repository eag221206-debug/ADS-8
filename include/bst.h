// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <vector>
#include <utility>

template<typename T>
class BST {
 private:
    struct Node {
        T value;
        int count;
        Node* left;
        Node* right;
        explicit Node(const T& val) : value(val), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void destroy(Node* node) {
        if (node) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

    Node* addNode(Node* node, const T& value) {
        if (!node) return new Node(value);
        if (value == node->value) {
            node->count++;
        } else if (value < node->value) {
            node->left = addNode(node->left, value);
        } else {
            node->right = addNode(node->right, value);
        }
        return node;
    }

    int getDepth(Node* node) const {
        if (!node) return -1;
        int leftDepth = getDepth(node->left);
        int rightDepth = getDepth(node->right);
        return 1 + std::max(leftDepth, rightDepth);
    }

    void inOrderPairs(Node* node, std::vector<std::pair<T, int>>& vec) const {
        if (node) {
            inOrderPairs(node->left, vec);
            vec.push_back({node->value, node->count});
            inOrderPairs(node->right, vec);
        }
    }

 public:
    BST() : root(nullptr) {}
    ~BST() {
        destroy(root);
    }

    void add(const T& value) {
        root = addNode(root, value);
    }

    int search(const T& value) const {
        Node* current = root;
        while (current) {
            if (value == current->value) return current->count;
            if (value < current->value) current = current->left;
            else current = current->right;
        }
        return 0;
    }

    int depth() const {
        if (!root) return 0;
        return getDepth(root);
    }

    void getPairs(std::vector<std::pair<T, int>>& vec) const {
        inOrderPairs(root, vec);
    }
};

#endif  // INCLUDE_BST_H_
