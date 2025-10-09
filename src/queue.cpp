#include "../include/queue.h"

Queue::Queue(int cap) : capacity(cap), front(0), rear(-1), size(0) { 
    data = new string[capacity];    
}

Queue::Queue() : capacity(30), front(0), rear(-1), size(0) { 
    data = new string[capacity];
}

Queue::~Queue() { 
    delete[] data;
}

bool Queue::isEmpty() { 
    return size == 0;
}

void Queue::push(string value) {  
    if (size == capacity) { 
        throw overflow_error(" Queue is full ");  
    }
    rear = (rear + 1) % capacity;
    data[rear] = value;
    size++;
}

string Queue::pop() { 
    if (size == 0) { 
        throw overflow_error(" Queue is empty");  
    }
    string value = data[front];
    front = (front + 1) % capacity;
    size--;
    return value;
} 

string Queue::peek() { 
    if (isEmpty()) { 
        throw underflow_error(" Queue is empty ");  
    }
    return data[front];
}

int Queue::Size() { 
    return size;
}
