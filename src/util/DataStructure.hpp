// Copyright 2022 by Michał Gibas
#ifndef DATASTRUCTURE_HPP
#define DATASTRUCTURE_HPP

#include <iostream>
#include "types.hpp"
#include "../Strings.hpp"

namespace sdizo {

class DataStructure {

public:

    virtual void print() = 0;
    virtual void add(int value, size_t index=-1) = 0;
    virtual void remove(size_t index=-1) = 0;
    virtual size_t find(int value) = 0;

    virtual void loadFromFile(const char* fileName) = 0;

protected:
    //check if index is out of bounds and is not a special value [-1 or -2]
    bool indexInBounds(size_t index, size_t size) {
        if((index < size) || (index == -1) || (index == -2)) {
            return true;
        }
        std::cout << OUT_OF_BOUNDS_MESSAGE;
        return false;
    }
};

};

#endif //DATASTRUCTURE_HPP