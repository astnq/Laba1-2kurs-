#pragma once 

#include "includes.h"

struct Queue{
    string* data;
    size_t size;
    int front; // Индекс первого элемента 
    int rear; // Индекс последнего элемента 
    int capacity; // Вместимость очереди 

    Queue(int cap);
    Queue();
    ~Queue();

    void push(string value); // Функция добавление элемента 
    bool isEmpty();
    string pop(); // Функция удаления элемента с начала очереди и его возврат
    string peek(); // Функция вывода элемента в начале очереди 
    int Size();
};

#include "../src/queue.cpp"
