#include "DoublyLinkedList.hpp"

#include <iostream>

namespace sdizo {

DoublyLinkedList::DoublyLinkedList() {
    head = nullptr;
    last = nullptr;
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
    last->next = element;
    element->previous = last;
    last = element;
}

void DoublyLinkedList::add(int value, size_t index) {

    if(!indexInBounds(index, size)) {
        return;
    }

    if(head == nullptr) {
        head = new Element;
        head->value = value;
        head->previous = nullptr;
        head->next = nullptr;
        last = head;
        size += 1;
        return;
    }

    if(index == -1) {
        addBack(value);
        ++size;
        return;
    }
    if(index == -2 || index == 0) {
        addFront(value);
        ++size;
        return;
    }
    
    Element* iterator = head;
    for(int i = 0; i < index; ++i) {
        iterator = iterator->next;
    }

    if(iterator != nullptr) {
        Element* previous = iterator->previous;
        Element* element = new Element;
        element->value = value;
        
        if(previous != nullptr) {
            previous->next = element;
        }

        element->previous = previous;
        element->next = iterator;
        iterator->previous = element;

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
    Element* element = last;
    if(element == nullptr) {
        return;
    }

    if(element == head) {
        head = nullptr;
        last = nullptr;
    }

    else if(element->previous == head) {
        last = head;
    }

    last = element->previous;
    if(last != nullptr) {
        last->next = nullptr;
    }

    --size;
    delete element;
}

void DoublyLinkedList::removeFront() {
    if(head == nullptr) {
        return;
    }

    Element* element = head;
    head = element->next;
    if(head != nullptr) {
        head->previous = nullptr;
    } else {
        last = nullptr;
    }

    --size;
    delete element;
}

void DoublyLinkedList::remove(size_t index) {
    if(size == 0UL) {
        return;
    }
    
    if(!indexInBounds(index, size))
        return;

    if(index == -1 || index == (size -1)) {
        removeBack();
        return;
    }
    else if(index == -2 || index == 0) {
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
        
        delete iterator;

        --size;
    }


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

size_t DoublyLinkedList::getSize() {
    return size;
}

};