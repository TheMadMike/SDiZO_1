#include "DoublyLinkedList.hpp"

#include <iostream>

namespace sdizo {

DoublyLinkedList::DoublyLinkedList() {
    head = nullptr;
    head = last;
    size = 0UL;
}

DoublyLinkedList::~DoublyLinkedList() {
    while(head != nullptr) {
        Element* ptr = head;
        head = head->next;
        delete ptr;
    }
}

void DoublyLinkedList::addFront(int value) {
    Element* element = new Element;
    element->value = value;
    element->next = head;
    element->previous = nullptr;
    head->previous = element;
    head = element;
}

void DoublyLinkedList::addBack(int value) {
    Element* element = new Element;
    element->value = value;
    element->next = nullptr;
    element->previous = last;
    if(last == nullptr) {
        last = element;
        head = last;
        return;
    }
    last->next = element;
    last = element;
}

void DoublyLinkedList::add(int value, size_t index) {

    if(!indexInBounds(index, size)) {
        return;
    }

    if(index == -1) {
        addBack(value);
        ++size;
        return;
    }
    if(index == -2) {
        addFront(value);
        ++size;
        return;
    }
    
    Element* iterator = head;
    for(int i = 1; i <= index; ++i) {
        iterator = iterator->next;
    }

    if(iterator != nullptr) {
        Element* previous = iterator->previous;
        Element* next = iterator->next;
        Element* element = new Element;
        element->value = value;
        
        if(previous != nullptr) {
            previous->next = element;
        }

        if(next != nullptr) {
            next->previous = element;
        }

        element->previous = previous;
        element->next = iterator;

        ++size;
    }
}

void DoublyLinkedList::print() {
    Element* ptr = head;
    std::cout << '[';
    while(ptr != nullptr) {
        if(ptr->next == nullptr) {
            std::cout << ptr->value;
            break;
        }
        std::cout << ptr->value << ", ";
        ptr = ptr->next;
    }
    std::cout << "]\n";
}

void DoublyLinkedList::removeBack() {
    if(size == 0UL)
        return;

    Element* element = last;
    last = element->previous;
    last->next = nullptr;

    --size;
    delete element;
}

void DoublyLinkedList::removeFront() {
    if(size == 0UL)
        return;
    
    Element* element = head;
    head = element->next;
    head->previous = nullptr;

    --size;
    delete element;
}

void DoublyLinkedList::remove(size_t index) {
    if(!indexInBounds(index, size))
        return;

    if(index == -1) {
        removeBack();
        return;
    }
    else if(index == -2) {
        removeFront();
        return;
    }

    Element* iterator = head;
    for(int i = 1; i <= index; ++i) {
        iterator = iterator->next;
    }

    if(iterator != nullptr) {
        Element* previous = iterator->previous;
        Element* next = iterator->next;

        if(previous != nullptr) {
            previous->next = next;
        }
        if(next != nullptr) {
            next->previous = previous;
        }
    }

    delete iterator;

    --size;
}

size_t DoublyLinkedList::find(int value) {
    Element* iterator = head;
    size_t index = 0UL;
    while(iterator != nullptr) {
        if(iterator->value == value) {
            return index;
        }
        iterator = iterator->next;
        ++index;
    }

    return -1;
}

void DoublyLinkedList::loadFromFile(const char* fileName) {

}

size_t DoublyLinkedList::getSize() {
    return size;
}

};