#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

#include "util/DataStructure.hpp"

namespace sdizo {

class DoublyLinkedList :public DataStructure {
public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    struct Element {
        int value = 0;
        Element* previous = nullptr;
        Element* next = nullptr;
    };

    void print() override;
    void add(int value, size_t index=-1) override;
    void remove(int value) override;
    size_t find(int value) override;
    void loadFromFile(const char* fileName) override;

    void addFront(int value);
    void addBack(int value);
    size_t getSize();
private:
    Element* head;
    Element* last;
    size_t size;
};

};

#endif //DOUBLY_LINKED_LIST_HPP