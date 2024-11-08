#include "../include/stack.h"

Stack::Stack(size_t size) : capacity(size), top(-1) {
    data = new string[capacity];
}

Stack::Stack() : capacity(15), top(-1) { //Устанавливаем начальную емкость 10
    data = new string[capacity];
}

Stack::~Stack() {
    delete[] data;
}

void Stack::push(string value) {
    if (top == capacity - 1) { 
        throw overflow_error("Стек переполнен ");
    }
    data[++top] = value; //Добавляем элемент и увелечения индекса 
}

string Stack::pop() {
    if (top == - 1) { 
        throw underflow_error("Стек пустой ");
    }
    return data[top--]; //Возврат элемента и уменьшение индекса 
}

string Stack::peek() {
    if (top == - 1) {
        throw underflow_error("Стек пустой ");
    }
    return data[top];
}

bool Stack::isEmpty(){
    return top == - 1;
}

size_t Stack::size() {
    return top + 1;
}
