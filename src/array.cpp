#include "../include/array.h"

Array::Array() : volume(10), size(0){
    arr = new string[volume];
}

Array::~Array(){
    delete[] arr; // Освобождение памяти
}

void Array::ShowArray() const{
    for(size_t i = 0; i < size; ++i){
        cout << arr[i] << endl;
    }
    cout << endl;
}

void Array::addToEnd(string value){
    string *newArr = new string[size + 1]; // Создание нового массива с увеличенным размером
    for(size_t i = 0; i < size; ++i){
        newArr[i] = arr[i]; // Копирование существующих элементов
    }
    delete[] arr; // Удаление старого массива
    arr = newArr;
    arr[size++] = value; // Добавление нового элемента в конец
}

void Array::add(size_t index, string value){
    if(index >= size) return;
    
    string *newArr = new string[size + 1];
    for(size_t i = 0; i <= index; ++i){ // Копирование элементов до указанного индекса
        newArr[i] = arr[i];
    }
    newArr[index] = value; // Вставка нового элемента
    for(size_t i = index + 1; i < size + 1; ++i){ // Копирование остальных элементов
        newArr[i] = arr[i - 1];
    }
    delete[] arr;
    arr = newArr;
    size++;
}

string Array::getIndex(size_t index){
    if(index >= size){
        throw out_of_range("Index out of range");
    }
    return arr[index];
}

void Array::remove(size_t index, string value){
    if(index >= size) return;
    
    string *newArr = new string[size - 1]; // Создание нового массива с уменьшенным размером
    for(size_t i = 0; i < index; ++i){ // Копирование элементов до указанного индекса
        newArr[i] = arr[i];
    }
    for(size_t i = index + 1; i < size; ++i){ // Копирование остальных элементов
        newArr[i - 1] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    size--;
}

void Array::replace(size_t index, string value){
    if(index >= size) return;
    arr[index] = value; // Замена значения по указанному индексу
}

size_t Array::getSize() const {
    return size; // Исправление опечатки в return
}
