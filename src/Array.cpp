// Copyright 2022 by Michał Gibas
#include "Array.hpp"
#include <iostream>

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

void Array::add(int value, size_t index) {

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

    if(index == -1) {
        data[size-1] = value;
        return;
    }

    //shift all of the values after index to the right
    for(int i = (size-1); i > index; --i) {
        data[i] = data[i-1];         
    }

    //insert the value at a given index
    data[index] = value;

}

void Array::remove(int value) {

}

size_t Array::find(int value) {

}

void Array::loadFromFile(const char* fileName) {
    
}

};