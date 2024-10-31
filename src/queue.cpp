#include "../include/queue.h"

Queue::Queue(int cap) : capacity(cap), front(0), rear(-1), size(0){
    data = new string[capacity];
}

Queue::Queue() : capacity(25), front(0), rear(-1), size(0) {
    data = new string[capacity]; //Размер списка
}

Queue::~Queue() {
    delete[] data;
}

void Queue::push(string value) {
    if (size == capacity) {
        throw overflow_error("Очередь переполнена "); //Проверка на переполнение 
    }
    rear = (rear + 1) % capacity; //Циклическое увеличение индекса 
    data[rear] = value; // Добавление элемента 
    size++; // Увеличение размера очереди 
}

bool Queue::isEmpty(){
    return size == 0;
}

string Queue::pop() { 
    if (size == 0) { 
        throw overflow_error("Очередь пуста ");
    }
    string value =data[front]; // Сохранение значение для возврата 
    front = (front + 1) % capacity; //Циклическое увеличение индекса 
    size--; // Уменьшение размера очереди 
    return value; // Возврат удаленного элемента 
}

string Queue::peek() {
    if (isEmpty()) {
        throw underflow_error("Очередь пуста "); //Проверка на переполнение 
    }
    return data[front];
}

int Queue::Size() {
    return size;
}