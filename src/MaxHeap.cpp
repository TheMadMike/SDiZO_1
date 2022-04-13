// Copyright 2022 by Michał Gibas
#include "MaxHeap.hpp"
#include <iostream>

namespace sdizo {

MaxHeap::MaxHeap() {
}

MaxHeap::~MaxHeap() {
}

void MaxHeap::print() {
    if(data == nullptr)
        std::cout << '\n';
    
    size_t rowIterator = 1;
    size_t rowMaxItems = 1;
    for(size_t i = 0UL; i < size; ++i) {
        std::cout << data[i] << ' ';
        if(rowMaxItems == rowIterator) {
            std::cout << '\n';
            rowMaxItems *= 2;
            rowIterator = 0;
        }
        ++rowIterator;
    }

    std::cout << '\n';
}

void MaxHeap::add(int value, size_t index) {

    Array::add(value);
    
    if(size == 1) {
        return;
    }

    size_t addedNodeIndex = size - 1;
    size_t parent = getParentIndex(addedNodeIndex);
    
    while((data[parent] < data[addedNodeIndex]) && (addedNodeIndex != 0)) {
        swapNodes(addedNodeIndex, parent);
        addedNodeIndex = parent;
        parent = getParentIndex(addedNodeIndex);
    }
}

size_t MaxHeap::getParentIndex(size_t index) {
    return (index - 1) / 2;
}

size_t MaxHeap::getLeftIndex(size_t index) {
    return (index * 2) + 1;
}

size_t MaxHeap::getRightIndex(size_t index) {
    return (index * 2) + 2;
}

void MaxHeap::swapNodes(size_t a, size_t b) {
    int tmp = data[a];
    data[a] = data[b];
    data[b] = tmp;
}

};