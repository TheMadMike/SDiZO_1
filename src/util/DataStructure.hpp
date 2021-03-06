// Copyright 2022 by Michał Gibas
#ifndef DATASTRUCTURE_HPP
#define DATASTRUCTURE_HPP

#include <iostream>
#include "types.hpp"
#include "../Strings.hpp"
#include "FileReader.hpp"

namespace sdizo {

/*
    An abstract class with all neccessary 
    operations for each data structure
*/
class DataStructure {

public:

    virtual void print() = 0;
    virtual void add(int value, size_t index=-1) = 0;
    virtual void remove(size_t index=-1) = 0;
    virtual void removeByValue(int value) {}
    virtual size_t find(int value) = 0;

    virtual void loadFromFile(const char* fileName) {
        FileReader reader(fileName);
        size_t dataSetSize = (size_t) reader.readNext<unsigned long>();
        for(size_t i = 0; i < dataSetSize; ++i) {
            this->add(reader.readNext<int>());
        }
    }

    virtual int getKey(size_t index) { return 0; }

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