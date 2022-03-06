// Copyright 2022 by Michał Gibas
#ifndef DATASTRUCTURE_HPP
#define DATASTRUCTURE_HPP

#include "types.hpp"

namespace sdizo {

class DataStructure {

public:

    virtual void print() = 0;
    virtual void add(int value, size_t index=-1) = 0;
    virtual void remove(int value) = 0;
    virtual size_t find(int value) = 0;

    virtual void loadFromFile(const char* fileName) = 0;

};

};

#endif //DATASTRUCTURE_HPP