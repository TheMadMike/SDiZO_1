// Copyright 2022 by Michał Gibas
#include "Array.hpp"
#include <iostream>
#include "util/FileReader.hpp"

namespace sdizo {

Array::Array(size_t size)
:size(size), data(nullptr) {
    if(size != 0) {
        data = new int[size];
    }
}

Array::~Array() {
    delete[] data;
}

void Array::print() {
    std::cout << '[';
    
    for(size_t i = 0; i < size; ++i) {
        if(i != (size-1))
            std::cout << data[i] << ", ";
        else std::cout << data[i];    
    }

    std::cout << "]\n";
}

void Array::removeFront() {
    int* newData = new int[size-1];
    
    for(int i = 0; i < (size-1); ++i) {
        newData[i] = data[i+1];
    }

    size -= 1;

    if(data != nullptr) {
        delete[] data;
    }

    data = newData;
}

void Array::removeBack() {
    int* newData = new int[size-1];
    
    for(int i = 0; i < (size-1); ++i) {
        newData[i] = data[i];
    }

    size -= 1;

    if(data != nullptr) {
        delete[] data;
    }

    data = newData;
}

void Array::addBack(int value) {
    int* dataCopy = new int[size+1];

    for(int i = 0; i < size; ++i) {
        dataCopy[i] = data[i];
    }

    dataCopy[size] = value;

    size += 1;

    if(data != nullptr) {
        delete[] data;
    }

    data = dataCopy;
}

void Array::addFront(int value) {
    int* dataCopy = new int[size+1];

    for(int i = 0; i < size; ++i) {
        dataCopy[i+1] = data[i];
    }

    size += 1;

    dataCopy[0] = value;

    if(data != nullptr) {
        delete[] data;
    }

    data = dataCopy;
}

void Array::add(int value, size_t index) {
    
    if(index == -1) {
        addBack(value);
        return;
    }

    if(index == -2) {
        addFront(value);
        return;
    }
    
    if(!indexInBounds(index, size)) {
        return;
    }

    resizeAndCopyForInsertion();

    //shift all of the values after index to the right
    for(int i = (size-1); i > index; --i) {
        data[i] = data[i-1];         
    }

    //insert the value at a given index
    data[index] = value;

}

void Array::remove(size_t index) {
    if(size == 0UL) {
        return;
    }
    
    if(index == -2) {
        removeFront();
        return;
    }
    
    else if(index == -1) {
        removeBack();
        return;
    }

    if(!indexInBounds(index, size)) {
        return;
    }

    int* newData = new int[size-1];
    for(int i = 0; i < index; ++i) {
        newData[i] = data[i];
    }

    for(int i = index; i < (size-1); ++i) {
        newData[i] = data[i+1];
    }

    delete[] data;
    data = newData;
    size -= 1;
}

size_t Array::find(int value) {
    //basic linear search O(n)
    for(size_t i = 0; i < size; ++i) {
        if(data[i] == value)
            return i;
    }

    return -1;
}

void Array::loadFromFile(const char* fileName) {
    FileReader reader(fileName);
    size = (size_t)reader.readNext<unsigned long>();

    delete[] data;
    data = new int[size];

    for(size_t i = 0; i < size; ++i) {
        data[i] = reader.readNext<int>();
    }
}

int Array::getKey(size_t index) {
    if(index >= size) {
        std::cout << "Index out of bounds! \n";
        return 0;
    }

    return data[index];
}

void Array::resizeAndCopyForInsertion() {
    //copy the data into a new array with size = size + 1
    int* dataCopy = new int[size+1];
    
    for(int i = 0; i < size; ++i) {
        dataCopy[i] = data[i];
    }

    size += 1;
    
    //delete old data and assign dataCopy address to data
    if(data != nullptr) {
        delete[] data;
    }

    data = dataCopy;
}

};