#pragma once 

#include "includes.h"

struct NodeT { 
    int data;
    NodeT* left;
    NodeT* right;

    NodeT(int value);
};

struct CompleteBinaryTree { 
    NodeT* root;
    size_t size;

    CompleteBinaryTree();
    ~CompleteBinaryTree();

    void insert(int value);
    bool isEmpty() const;
    void _insert(int value, NodeT* nodeb);
    bool search(NodeT* nodet, int value);
    bool isComplete(NodeT* nodet, int index, int totalNodes);
    bool isComplete();
    string toString(NodeT* node) const;
    void printTree(NodeT* node);
    void clear(NodeT* nodet);
};

#include "../src/tree.cpp"

