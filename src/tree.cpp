#include "../include/tree.h"

NodeT::NodeT(int value) { 
    data = value;
    left = nullptr;
    right = nullptr;
}

FullBinaryTree::FullBinaryTree() { 
    root = nullptr;
    size = 0;
}

void FullBinaryTree::print() { 
    printTree(root, 0);
    cout << endl; 
}

string FullBinaryTree::toString() { 
    return _toString(root);
}

void FullBinaryTree::insert(int value) {
    root = _insert(root, value);  
    size++;
}

NodeT* FullBinaryTree::_insert(NodeT* node, int value) { 
    if (node == nullptr) { 
        return new NodeT(value);
    }
    if (value < node->data) { 
        node->left = _insert(node->left, value);  
    } else {
        node->right = _insert(node->right, value);  
    }
    return node;
}

bool FullBinaryTree::search(NodeT* node, int value) { 
    if (node == nullptr) return false;
    if (node->data == value) return true; 
    return search(node->left, value) || search(node->right, value);  
}

bool FullBinaryTree::isFull() { 
    return isFull(root);
}

bool FullBinaryTree::isFull(NodeT* node) { 
    if (node == nullptr) return true;
    
    
    if (node->left == nullptr && node->right == nullptr) return true;  // Лист - полный
    if (node->left != nullptr && node->right != nullptr) {  // Оба потомка есть
        return isFull(node->left) && isFull(node->right);
    }
    return false;  
}

string FullBinaryTree::_toString(NodeT* node) { 
    if (node == nullptr) return "";
    ostringstream oss;  
    oss << node->data << " ";
    oss << _toString(node->left);
    oss << _toString(node->right);
    return oss.str();
}

void FullBinaryTree::printTree(NodeT* node, int depth) { 
    if (node == nullptr) return;
    printTree(node->right, depth + 1);
    cout << setw(4 * depth) << " " << node->data << endl;
    printTree(node->left, depth + 1);
}

void FullBinaryTree::clear(NodeT* node) { 
    if (node == nullptr) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

FullBinaryTree::~FullBinaryTree() { 
    clear(root);
}
