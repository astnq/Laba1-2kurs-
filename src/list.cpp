#include "../include/list.h"

Node::Node(string value) { 
    data = value;
    next = nullptr;                                 // Односвязный узел - только next
}

SinglyLinkedList::SinglyLinkedList() { 
    head = nullptr;
    elementCount = 0;                               // Счетчик элементов
}

SinglyLinkedList::~SinglyLinkedList() { 
    while(!isEmpty()) { 
        popFront();                                 // Последовательное удаление с начала
    }
}

bool SinglyLinkedList::isEmpty() const { 
    return elementCount == 0;                       // Проверка через счетчик
}

void SinglyLinkedList::print() { 
    Node* current = head;
    while(current) { 
        cout << current->data << " ";  
        current = current->next;                    // Линейный обход всего списка
    }
    cout << endl;
}

void SinglyLinkedList::pushFront(string value) { 
    Node* newNode = new Node(value);
    newNode->next = head;                           // Новый узел указывает на старую голову
    head = newNode;                                 // Обновление головы списка
    elementCount++;
}

void SinglyLinkedList::pushBack(string value) {
    Node* newNode = new Node(value);
    if(head == nullptr) { 
        head = newNode;                             // Если список пуст - новый узел становится головой
    } else {
        Node* current = head; 
        while(current->next != nullptr) { 
            current = current->next;                // Поиск последнего узла
        }
        current->next = newNode;                    // Добавление после последнего узла
    }
    elementCount++;  
}

void SinglyLinkedList::popFront() { 
    if(head == nullptr) return;
    Node* nextHead = head->next;                    // Сохранение ссылки на следующий узел
    delete head;                                    // Удаление текущей головы
    head = nextHead;                                // Обновление головы
    elementCount--;
}

void SinglyLinkedList::popBack() { 
    if(head == nullptr) return;
    if(head->next == nullptr) { 
        delete head;                                // В списке один элемент
        head = nullptr;
    } else {
         Node* current = head;
         while(current->next->next != nullptr) { 
            current = current->next;                // Поиск предпоследнего узла
         }
         delete current->next;                      // Удаление последнего узла
         current->next = nullptr;                   // Обнуление ссылки
    }
    elementCount--;
}

void SinglyLinkedList::removeAt(string value) { 
    if(isEmpty()) return;
    if(head->data == value) {
        popFront();                                 // Удаление из головы
        return;
    }
    Node* current = head;
    while(current->next != nullptr && current->next->data != value) { 
        current = current->next;                    // Поиск узла ПЕРЕД удаляемым
    }
    if(current->next != nullptr) {
        Node* nodeToDelete = current->next;
        current->next = nodeToDelete->next;         // Перелинковка через узел
        delete nodeToDelete;
        elementCount--;
    }
}

bool SinglyLinkedList::find(string value) { 
    Node* current = head;
    while(current != nullptr) {
         if(current->data == value) { 
            return true;                            // Линейный поиск по значению
         }
         current = current->next;
    }
    return false;
}

void SinglyLinkedList::clearSList() { 
    while(!isEmpty()) {  
        popFront();                                 // Очистка через popFront
    }
}

Node* SinglyLinkedList::getHead() const { 
    return head;                                    // Получение указателя на голову
}

// DoubleLinkedList
DoubleNode::DoubleNode(string value) {  
    data = value;
    next = nullptr;
    prev = nullptr;                                 // Двусвязный узел - next и prev
}

DoubleLinkedList::DoubleLinkedList() { 
    head = nullptr;
    tail = nullptr;                                 // Двусвязный список имеет хвост
    elementCount = 0;  
}

DoubleLinkedList::~DoubleLinkedList() { 
    while(!isEmpty()) { 
        popFront();                                 // Рекурсивное удаление
    }
}

DoubleNode* DoubleLinkedList::getHead() const {
    return head;                                    // Получение головы
}

bool DoubleLinkedList::isEmpty() const { 
    return elementCount == 0;                       // Проверка пустоты
}

void DoubleLinkedList::pushFront(string value) { 
    DoubleNode* newNode = new DoubleNode(value);
    newNode->next = head; 
    if(head != nullptr) { 
        head->prev = newNode;                       // Обновление prev старой головы
    } else { 
        tail = newNode;                             // Если список был пуст - хвост = голова
    }
    head = newNode;                                 // Обновление головы
    elementCount++; 
}

void DoubleLinkedList::pushBack(string value) { 
    DoubleNode* newNode = new DoubleNode(value);
    if(tail == nullptr) { 
        head = newNode;                             // Пустой список
        tail = newNode;
    } else { 
        newNode->prev = tail;                       // Новый узел ссылается на старый хвост
        tail->next = newNode;                       // Старый хвост ссылается на новый узел
        tail = newNode;                             // Обновление хвоста
    }
    elementCount++;  
}

void DoubleLinkedList::popFront() { 
    if(head == nullptr) return;
    DoubleNode* nextHead = head;  
    head = head->next;
    if(head != nullptr) { 
        head->prev = nullptr;                       // Обнуление prev новой головы
    } else { 
        tail = nullptr;                             // Список стал пустым
    }
    delete nextHead;
    elementCount--;  
}

void DoubleLinkedList::popBack() { 
    if(tail == nullptr) return;
    DoubleNode* nodeToDelete = tail;
    if(head == tail) { 
        head = nullptr;                             // В списке один элемент
        tail = nullptr;  
    } else { 
        tail = tail->prev;                          // Перемещение хвоста назад
        tail->next = nullptr;                       // Обнуление ссылки нового хвоста
    }
    delete nodeToDelete;
    elementCount--;  
}

void DoubleLinkedList::removeAt(string value) { 
    DoubleNode* current = head;
    while(current) { 
        if(current->data == value) { 
            if(current->prev) { 
                current->prev->next = current->next; // Перелинковка предыдущего узла
            } else { 
                head = current->next;                // Удаление из головы
            }
            if(current->next) { 
                current->next->prev = current->prev; // Перелинковка следующего узла
            } else { 
                tail = current->prev;                // Удаление из хвоста
            }
            delete current;
            elementCount--;
            return;
        }
        current = current->next;
    }
}

bool DoubleLinkedList::find(string value) { 
    DoubleNode* current = head; 
    while(current) { 
        if(current->data == value) { 
            return true;                            // Линейный поиск
        }
        current = current->next;
    }
    return false;
}

void DoubleLinkedList::print() { 
    DoubleNode* current = head;
    while(current) { 
        cout << current->data << " ";
        current = current->next;                    // Обход от головы к хвосту
    }
    cout << endl;
}

void DoubleLinkedList::clearDList() { 
    while(!isEmpty()) { 
        popFront();                                 // Очистка через popFront
    }
}
