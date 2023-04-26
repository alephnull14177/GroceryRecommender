#include <string>
#include <iostream>
#include <vector>
#pragma once

enum Color {RED, BLACK};
template <typename T1, typename T2>

class RedBlackTree {
    struct TreeNode {
        T1 key;
        std::vector<T2> vals;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;
        Color color;
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

    void Balance(TreeNode* node) {
        while (node->parent->color == RED) {
            TreeNode* parent = node->parent;
            TreeNode* grandparent = parent->parent;
            TreeNode* aunt = root;
            if (parent == grandparent->left) {
                if (grandparent->right) {
                    aunt = grandparent->right;
                }
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
                else if (node == grandparent->left->right) {
                    RotateLeft(parent);
                }
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
            else {
                if (grandparent->left) {
                    aunt = grandparent->left;
                }
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
                else if (node == grandparent->right->left) {
                    //FInodeME
                    RotateRight(parent);
                }
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
        root->color = BLACK;
    }

    void RotateLeft(TreeNode* node) {
        TreeNode* right = node->right;
        node->right = right->left;

        if (node->right)
            node->right->parent = node;

        right->parent = node->parent;

        if (!node->parent)
            root = right;
        else if (node == node->parent->left)
            node->parent->left = right;
        else
            node->parent->right = right;

        right->left = node;
        node->parent = right;
    }
    void RotateRight(TreeNode* node) {
        TreeNode* left = node->left;
        node->left = left->right;

        if (node->left)
            node->left->parent = node;

        left->parent = node->parent;

        if (!node->parent)
            root = left;
        else if (node == node->parent->left)
            node->parent->left = left;
        else
            node->parent->right = left;

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
        if (node == nullptr) {
            return false;
        }
        // L
        printHelper(node->left);
        // N
//        if (node->color == RED) {
//            std::cout << "(R) ";
//        }
//        else {
//            std::cout << "(B) ";
//        }
        std::cout << node->key << ": ";
        for (int i = 0; i < node->vals.size(); ++i) {
            std::cout << node->vals[i] << " ";
        }
//        if (node->parent) {
//            std::cout << "/ Parent: " << node->parent->key;
//        }
        std::cout << std::endl;
        // R
        printHelper(node->right);
        return true;
    }

    void findHelper(TreeNode* node, T1& key, bool& found) {
        if (node == nullptr) {
            return;
        }
        if (node->key == key) {
            found = true;
            return;
        }

        if (node->key > key)
            findHelper(node->left, key, found);
        else
            findHelper(node->right, key, found);
    }

    void GetKeysHelper(TreeNode* node, std::vector<T1>& keys) {
        if (node == nullptr) {
            return;
        }

        GetKeysHelper(node->left, keys);
        keys.push_back(node->key);
        GetKeysHelper(node->right, keys);
    }

    void clearHelper(TreeNode* node) {
        if (node == nullptr) {
            return;
        }
        // L
        clearHelper(node->left);
        // R
        clearHelper(node->right);
        // N
        root = RemoveLeaf(root, node->key);
        --size;
    }
    TreeNode* RemoveLeaf(TreeNode* node, T1& key) {
        if (node == nullptr) { // reaches if cannot find node to delete
            return nullptr;
        }
        // recurse left
        if (node->key > key) {
            node->left = RemoveLeaf(node->left, key);
            return node;
        }
            // recurse right
        else if (node->key < key) {
            node->right = RemoveLeaf(node->right, key);
            return node;
        }
        else {
            delete node;
            return nullptr;
        }
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
    RedBlackTree() {
        root = nullptr;
        size = 0;
    }

    void Insert(T1 key, T2 val) {
        if (root == nullptr) {
            root = new TreeNode(key, val);
            root->color = BLACK;
        }
        else {
            TreeNode* iterator = root;
            bool newInsert = true;
            TreeNode* node = new TreeNode(key, val);

            while (iterator) {
                // append vector
                if (iterator->key == key) {
                    iterator->vals.push_back(val);
                    newInsert = false;
                    delete node;
                    --size;
                    break;
                }
                    // left branch
                else if (iterator->key > key) {
                    if (!iterator->left) {
                        iterator->left = node;
                        node->parent = iterator;
                        break;
                    } else {
                        iterator = iterator->left;
                    }
                }
                    // right branch
                else {
                    if (!iterator->right) {
                        iterator->right = node;
                        node->parent = iterator;
                        break;
                    } else {
                        iterator = iterator->right;
                    }
                }
            }
            if (newInsert) {
                Balance(node);
            }
        }
        ++size;
        //std::cout << size << std::endl;
    }

    int GetSize() {
        return size;
    }

    std::vector<T2> Get(T1 key) {
        std::vector<T2> vals;
        GetHelper(root, key, vals);
        return vals;
    }

    std::vector<T1> GetKeys() {
        std::vector<T1> keys;
        GetKeysHelper(root, keys);
        return keys;
    }

    bool find(T1 key) {
        bool found = false;
        findHelper(root, key, found);
        return found;
    }

    bool print() {
        return printHelper(root);
    }

    void clear() {
        clearHelper(root);
        //size = 0;
    }

    void ClearVals(T1 key) {
        ClearValsHelper(root, key);
    }

};
