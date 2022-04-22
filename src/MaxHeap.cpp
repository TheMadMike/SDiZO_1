// Copyright 2022 by Michał Gibas
#include "MaxHeap.hpp"
#include <iostream>
#include "util/FileReader.hpp"

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

void MaxHeap::remove(size_t index) {
    if(!indexInBounds(index, size))
        return;

    if(data == nullptr) 
        return;

    if(index == -1) {
        if(data+1 == nullptr) {
            delete[] data;
        }

        data[0] = data[size - 1];
        heapify(0);
        Array::remove(-1);
        return;
    }

    data[index] = data[size - 1];
    heapify(0);
    Array::remove(-1);

}

void MaxHeap::heapify(size_t index) {
    size_t left = this->getLeftIndex(index);
    size_t right = this->getRightIndex(index);
    size_t largest;
    largest = index;
    if(left < size){
        if(data[left] > data[largest])
        largest = left;
    }
    if(right < size){
        if(data[right] > data[largest])
        largest = right;
    }

    if(largest != index){
        int buffer = data[index];
        data[index] = data[largest];
        data[largest] = buffer;
        heapify(largest);
    }
}

void MaxHeap::loadFromFile(const char* fileName) {
    FileReader reader(fileName);
    size_t size = reader.readNext<unsigned long>();

    for(size_t i = 0; i < size; ++i) {
        int value = reader.readNext<int>();
        this->add(value);
    }

}

};