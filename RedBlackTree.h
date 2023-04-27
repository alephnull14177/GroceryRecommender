#include <string>
#include <iostream>
#include <vector>
#pragma once

// tracks color of nodes
enum Color {RED, BLACK};
template <typename T1, typename T2>

class RedBlackTree {
    // Nodes store key and vector of vals
    struct TreeNode {
        T1 key;
        std::vector<T2> vals;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;
        Color color;
        // default
        TreeNode() {
            left = right = parent = nullptr;
            color = BLACK;
        }
        TreeNode(T1& k, T2& v) {
            key = k;
            vals.push_back(v);
            left = right = parent = nullptr;
            color = RED;
        }
    };

private:
    TreeNode* root;
    int size;

    // iterative balance function - bottom up
    void Balance(TreeNode* node) {
        while (node->parent->color == RED) {
            TreeNode* parent = node->parent;
            TreeNode* grandparent = parent->parent;
            TreeNode* aunt = root;
            // parent is left of grandparent
            if (parent == grandparent->left) {
                // point aunt to grandparent right if it exists
                if (grandparent->right) {
                    aunt = grandparent->right;
                }
                // color swap
                if (aunt->color == RED) {
                    parent->color = BLACK;
                    aunt->color = BLACK;
                    grandparent->color = RED;
                    if (grandparent->key != root->key) {
                        node = grandparent;
                    }
                    else {
                        break;
                    }
                }
                // rotate
                else if (node == grandparent->left->right) {
                    RotateLeft(parent);
                }
                // color swaps + rotate
                else {
                    parent->color = BLACK;
                    grandparent->color = RED;
                    RotateRight(grandparent);
                    if (grandparent->key != root->key) {
                        node = grandparent;
                    } else {
                        break;
                    }
                }
            }
                // parent is right of grandparent
            else {
                // point aunt to grandparent left if it exists
                if (grandparent->left) {
                    aunt = grandparent->left;
                }
                // color swap
                if (aunt->color == RED) {
                    parent->color = BLACK;
                    aunt->color = BLACK;
                    grandparent->color = RED;
                    if (grandparent->key != root->key) {
                        node = grandparent;
                    }
                    else {
                        break;
                    }
                }
                // rotate
                else if (node == grandparent->right->left) {
                    RotateRight(parent);
                }
                // color swaps + rotate
                else {
                    parent->color = BLACK;
                    grandparent->color = RED;
                    RotateLeft(grandparent);
                    if (grandparent->key != root->key) {
                        node = grandparent;
                    }
                    else {
                        break;
                    }
                }
            }
        }
        // set root to black at end
        root->color = BLACK;
    }

    void RotateLeft(TreeNode* node) {
        // store right child
        TreeNode* right = node->right;
        // make right child the left child of right child
        node->right = right->left;

        // if right is now not null, update parent
        if (node->right) {
            node->right->parent = node;
        }

        // right's parent to be nodes parent
        right->parent = node->parent;

        // if node was root
        if (!node->parent) {
            root = right;
        }
        // update child pointer
        else if (node == node->parent->left) {
            node->parent->left = right;
        }
        else {
            node->parent->right = right;
        }

        // make node being rotated the left child of new right child
        right->left = node;
        node->parent = right;
    }
    void RotateRight(TreeNode* node) {
        // store left child
        TreeNode* left = node->left;
        // make left child the right child of left child
        node->left = left->right;

        // if left is now not null, update parent
        if (node->left) {
            node->left->parent = node;
        }

        // left's parent to be nodes parent
        left->parent = node->parent;

        // if node was root
        if (!node->parent) {
            root = left;
        }
        // update child pointer
        else if (node == node->parent->left) {
            node->parent->left = left;
        }
        else {
            node->parent->right = left;
        }

        // make node being rotated the right child of new left child
        left->right = node;
        node->parent = left;
    }

    void GetHelper(TreeNode* node, T1& key, std::vector<T2>& vals) {
        if (node) {
            // if space to insert
            if (node->key == key) {
                vals = node->vals;
                return;
            }
            // recurse left
            if (key < node->key) {
                GetHelper(node->left, key, vals);
            }
                // recurse right
            else {
                GetHelper(node->right, key, vals);
            }
        }
    }

    bool printHelper(TreeNode* node) {
        // return false immediately if tree is empty
        if (node == nullptr) {
            return false;
        }
        // L
        printHelper(node->left);
        // N
        std::cout << node->key << ": ";
        for (int i = 0; i < node->vals.size(); ++i) {
            std::cout << node->vals[i] << " ";
        }
        std::cout << std::endl;
        // R
        printHelper(node->right);
        return true;
    }

    void findHelper(TreeNode* node, T1& key, bool& found) {
        // recurse back if dead end
        if (node == nullptr) {
            return;
        }
        // set found to be true if key is equal
        if (node->key == key) {
            found = true;
            return;
        }

        // branch left
        if (node->key > key) {
            findHelper(node->left, key, found);
        }
        // branch right
        else {
            findHelper(node->right, key, found);
        }
    }

    // creates vector of keys - for iteration
    void GetKeysHelper(TreeNode* node, std::vector<T1>& keys) {
        // return if hits dead end
        if (node == nullptr) {
            return;
        }

        // L
        GetKeysHelper(node->left, keys);
        // N
        keys.push_back(node->key);
        // R
        GetKeysHelper(node->right, keys);
    }

    // postorder traversal to delete only leaf nodes
    // no need to make one child and tro children delete functions
    void clearHelper(TreeNode* node) {
        // return if dead end
        if (node == nullptr) {
            return;
        }
        // L
        clearHelper(node->left);
        // R
        clearHelper(node->right);
        // N
        delete node;
        // decrement size - tracks if tree is truly being cleared
        --size;
    }

    void ClearValsHelper(TreeNode* node, T1& key) {
        if (node == nullptr) {
            return;
        }
        if (node->key == key) {
            node->vals.clear();
            return;
        }

        ClearValsHelper(node->left, key);
        ClearValsHelper(node->right, key);
    }

public:
    // default constructor
    RedBlackTree() {
        root = nullptr;
        size = 0;
    }

    // iterative insert function
    void Insert(T1 key, T2 val) {
        // when tree is empty
        if (root == nullptr) {
            root = new TreeNode(key, val);
            root->color = BLACK;
        }
        // normal insertion
        else {
            // start at root
            TreeNode* iterator = root;
            // for tracking if new key added
            bool newInsert = true;
            TreeNode* node = new TreeNode(key, val);

            while (iterator) {
                // append vector
                if (iterator->key == key) {
                    iterator->vals.push_back(val);
                    newInsert = false;
                    // delete new memory allocated above - not used
                    delete node;
                    // decrement size to counteract increment size down below
                    --size;
                    break;
                }
                    // left branch
                else if (iterator->key > key) {
                    // if finds place to put key
                    if (!iterator->left) {
                        iterator->left = node;
                        node->parent = iterator;
                        break;
                    } else {
                        // update iterator
                        iterator = iterator->left;
                    }
                }
                    // right branch
                else {
                    // if finds place to put key
                    if (!iterator->right) {
                        iterator->right = node;
                        node->parent = iterator;
                        break;
                    } else {
                        // update iterator
                        iterator = iterator->right;
                    }
                }
            }
            // only balances if a new key was added
            if (newInsert) {
                Balance(node);
            }
        }
        // increment size
        ++size;
    }

    // returns size
    int GetSize() {
        return size;
    }

    // gets values associated with key
    std::vector<T2> Get(T1 key) {
        std::vector<T2> vals;
        GetHelper(root, key, vals);
        return vals;
    }

    // gets vector of all keys in tree - for iteration
    std::vector<T1> GetKeys() {
        std::vector<T1> keys;
        GetKeysHelper(root, keys);
        return keys;
    }

    // recursively searches for element - returns true if found
    bool find(T1 key) {
        bool found = false;
        findHelper(root, key, found);
        return found;
    }

    // print each key with all associated vals
    bool print() {
        return printHelper(root);
    }

    // for reusing same data structure (since allocating new memory takes lots of space)
    void clear() {
        clearHelper(root);
    }

    // deletes vals associated with a key - useful in calculateRecommendations function
    void ClearVals(T1 key) {
        ClearValsHelper(root, key);
    }

};