#include "../include/hashtable.h"

Hash_table::Hash_table() { 
    table = new Hinfo* [SIZE];
    for (size_t i = 0; i < SIZE; ++i) { 
        table[i] = nullptr; //Присваиванпие каждой ноды, нулевого значения
    }
}

Hash_table::~Hash_table() {
    for (size_t i = 0; i < SIZE; ++i) { 
        Hinfo* current = table[i];
        while (current) {
            Hinfo* toDelete = current;
            current = current->next; // Освобождение каждой ноды
            delete toDelete;
        }
    }
    delete[] table;
}

int Hash_table::hashFunction(const string& key) { 
    hash<string> hashFn;
    return hashFn(key) % SIZE;
}
void Hash_table::insert(const string &key, const string value) { 
    int hashValue = hashFunction(key); // Хэш значение соответствующее этому ключу
    Hinfo* newPair = new Hinfo(key, value); // Используем конструктор Ninfo

    if(table[hashValue] == nullptr) { 
        table[hashValue] = newPair; // Если ячейка пуста, вставляем новый элемент
        sizetable++;
    } else { 
        Hinfo* current = table[hashValue];
        while(current) {
            if(current->key == key) { 
                current->value = value; // Обновляем значение, если ключ существует
                delete newPair; // Удаляем временный узел
                return;
            }
            if (current->next == nullptr) break; // Если достигли конца цепочки
            current = current->next;
        }
        current->next = newPair; // Добавляем новый элемент в конец цепочки
        sizetable++;
    }
}

bool Hash_table::get(const string& key, string& value) { 
    int HashValue = hashFunction(key); //Хэш значение соответсвующее этому ключу
    Hinfo* current = table[HashValue];
    while(current) { 
        if(current->key == key) {
            value = current->value;  //Возвращаем значение
            cout << value << endl;
            return true; //Ключ найден
        }
        current = current->next;
    }
    return false; //Ключ не найден
}

bool Hash_table::remove(const string& key) {
    int HashValue = hashFunction(key);
    Hinfo* current = table[HashValue];
    Hinfo* perv = nullptr;

    while(current) {
        if(current->key == key) { 
            if(perv) { 
                perv->next = current->next; //Удаление из цепочки
            } else { 
                table[HashValue] = current->next; // Если это первый элемент в цепочке
            }
            delete current; // Освобождаем память
            return true; // Успешное удаление
        }
        perv = current;
        current = current->next;
    }
    return false; // Ключ не найден
}