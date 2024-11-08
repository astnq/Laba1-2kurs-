#pragma once

//#ifndef stack.h
//#define stack.h

#include "includes.h"

struct Stack{

    string* data; 
    int top;
    int capacity;

    Stack(size_t size);
    Stack();
    ~Stack();

    void push(string value);
    string pop();
    string peek();
    bool isEmpty();
    size_t size();
};

#include "../src/stack.cpp"

//#endif 