#include "../include/array.h"

Array::Array() : volume(10), size(0) {  // Добавлено :
    arr = new string[volume];
}

Array::~Array() {  
    delete[] arr;
}

void Array::ShowArray() const { 
    for(size_t i = 0; i < size; ++i) { 
        cout << arr[i] << endl;
    }
    cout << endl;
}

void Array::addToEnd(string value) { 
    string *newArr = new string[size + 1];
    for(size_t i = 0; i < size; ++i) { 
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    arr[size++] = value;
}

void Array::add(size_t index, string value) { 
    if(index >= size) return;

    string *newArr = new string[size + 1];
    for(size_t i = 0; i < index; ++i) {  
        newArr[i] = arr[i];
    }
    newArr[index] = value;
    for(size_t i = index; i < size; ++i) {  
        newArr[i + 1] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    size++; 
}

string Array::getIndex(size_t index) { 
    if(index >= size) {
        throw out_of_range("Index out of range"); 
    }
    return arr[index];
}

void Array::remove(size_t index) { 
    if(index >= size) return;

    string *newArr = new string[size - 1];  
    for(size_t i = 0; i < index; ++i) {
        newArr[i] = arr[i];
    }
    for(size_t i = index + 1; i < size; ++i) { 
        newArr[i - 1] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    size--;
}

void Array::replace(size_t index, string value) { 
    if(index >= size) return;  
    arr[index] = value;
}

size_t Array::getSize() const {  
    return size;
}
