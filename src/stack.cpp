#include "../include/stack.h"

Stack::Stack(size_t size) : capacity(size), head(-1) { 
    data = new string[capacity];
}

Stack::Stack() : capacity(30), head(-1) { 
    data = new string[capacity];
}

Stack::~Stack() {
    delete[] data;
}

void Stack::push(string value) { 
    if (head == capacity - 1) { 
        throw overflow_error(" Stack is full"); 
    }
    data[++head] = value;
}

string Stack::pop() { 
    if (head == -1) { 
        throw underflow_error(" Stack is empty"); 
    }
    return data[head--];
}

string Stack::peek() { 
    if (head == -1) { 
        throw underflow_error(" Stack is empty");  
    } 
    return data[head];
}

bool Stack::isEmpty() {  
    return head == -1;
}

size_t Stack::size() { 
    return head + 1;
}
