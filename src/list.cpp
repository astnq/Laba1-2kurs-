#include "../include/list.h"

Node::Node(string value) { 
    data = value;
    next = nullptr;
}

SinglyLinkedList::SinglyLinkedList() { 
    head = nullptr;
    elementCount = 0;  
}

SinglyLinkedList::~SinglyLinkedList() { 
    while(!isEmpty()) { 
        popFront();
    }
}

bool SinglyLinkedList::isEmpty() const { 
    return elementCount == 0;
}

void SinglyLinkedList::print() { 
    Node* current = head;
    while(current) { 
        cout << current->data << " ";  
        current = current->next;  
    }
    cout << endl;
}

void SinglyLinkedList::pushFront(string value) { 
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    elementCount++;
}

void SinglyLinkedList::pushBack(string value) {
    Node* newNode = new Node(value);
    if(head == nullptr) { 
        head = newNode;  
    } else {
        Node* current = head; 
        while(current->next != nullptr) { 
            current = current->next;
        }
        current->next = newNode;
    }
    elementCount++;  
}

void SinglyLinkedList::popFront() { 
    if(head == nullptr) return;
    Node* nextHead = head->next;
    delete head;
    head = nextHead;
    elementCount--;
}

void SinglyLinkedList::popBack() { 
    if(head == nullptr) return;
    if(head->next == nullptr) { 
        delete head;
        head = nullptr;
    } else {
         Node* current = head;
         while(current->next->next != nullptr) { 
            current = current->next;
         }
         delete current->next;
         current->next = nullptr;
    }
    elementCount--;
}

void SinglyLinkedList::removeAt(string value) { 
    if(isEmpty()) return;
    if(head->data == value) {
        popFront();
        return;
    }
    Node* current = head;
    while(current->next != nullptr && current->next->data != value) { 
        current = current->next;  
    }
    if(current->next != nullptr) {
        Node* nodeToDelete = current->next;
        current->next = nodeToDelete->next;
        delete nodeToDelete;
        elementCount--;
    }
}

bool SinglyLinkedList::find(string value) { 
    Node* current = head;
    while(current != nullptr) {
         if(current->data == value) { 
            return true;
         }
         current = current->next;
    }
    return false;
}

void SinglyLinkedList::clearSList() { 
    while(!isEmpty()) {  
        popFront();
    }
}

Node* SinglyLinkedList::getHead() const { 
    return head;
}

// DoubleLinkedList
DoubleNode::DoubleNode(string value) {  
    data = value;
    next = nullptr;
    prev = nullptr;
}

DoubleLinkedList::DoubleLinkedList() { 
    head = nullptr;
    tail = nullptr;
    elementCount = 0;  
}

DoubleLinkedList::~DoubleLinkedList() { 
    while(!isEmpty()) { 
        popFront();
    }
}

DoubleNode* DoubleLinkedList::getHead() const {
    return head;
}

bool DoubleLinkedList::isEmpty() const { 
    return elementCount == 0;
}

void DoubleLinkedList::pushFront(string value) { 
    DoubleNode* newNode = new DoubleNode(value);
    newNode->next = head; 
    if(head != nullptr) { 
        head->prev = newNode;
    } else { 
        tail = newNode;
    }
    head = newNode;
    elementCount++; 
}

void DoubleLinkedList::pushBack(string value) { 
    DoubleNode* newNode = new DoubleNode(value);
    if(tail == nullptr) { 
        head = newNode;
        tail = newNode;
    } else { 
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    elementCount++;  
}

void DoubleLinkedList::popFront() { 
    if(head == nullptr) return;
    DoubleNode* nextHead = head;  
    head = head->next;
    if(head != nullptr) { 
        head->prev = nullptr;
    } else { 
        tail = nullptr;
    }
    delete nextHead;
    elementCount--;  
}

void DoubleLinkedList::popBack() { 
    if(tail == nullptr) return;
    DoubleNode* nodeToDelete = tail;
    if(head == tail) { 
        head = nullptr;  
        tail = nullptr;  
    } else { 
        tail = tail->prev;
        tail->next = nullptr;
    }
    delete nodeToDelete;
    elementCount--;  
}

void DoubleLinkedList::removeAt(string value) { 
    DoubleNode* current = head;
    while(current) { 
        if(current->data == value) { 
            if(current->prev) { 
                current->prev->next = current->next;
            } else { 
                head = current->next;
            }
            if(current->next) { 
                current->next->prev = current->prev;
            } else { 
                tail = current->prev;
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
            return true;
        }
        current = current->next;
    }
    return false;
}

void DoubleLinkedList::print() { 
    DoubleNode* current = head;
    while(current) { 
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void DoubleLinkedList::clearDList() { 
    while(!isEmpty()) { 
        popFront();  
    }
}
