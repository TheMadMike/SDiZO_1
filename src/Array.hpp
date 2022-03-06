// Copyright 2022 by Michał Gibas
#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "util/DataStructure.hpp"

namespace sdizo {

class Array :public DataStructure {

public:
    Array(size_t size=0);
    virtual ~Array();

    void print() override;
    void add(int value, size_t index=-1) override;
    void remove(int value) override;
    size_t find(int value) override;
    void loadFromFile(const char* fileName) override;

    inline size_t getSize() { return size; };
    int get(size_t index);

private:
    int* data;
    size_t size;
};

};

#endif //ARRAY_HPP