// Copyright 2022 by Michał Gibas
#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "util/DataStructure.hpp"

namespace sdizo {

/* Dynamic array implementation */
class Array :public DataStructure {

public:
    Array(size_t size=0);
    virtual ~Array();

    void print() override;
    void add(int value, size_t index=-1) override;
    void remove(size_t index=-1) override;
    size_t find(int value) override;
    void loadFromFile(const char* fileName) override;

    inline size_t getSize() { return size; };
    int getKey(size_t index) override;

    void addBack(int value);
    void addFront(int value);
    void removeFront();
    void removeBack();

protected:
    int* data;
    size_t size;

private:
    void resizeAndCopyForInsertion();

};

};

#endif //ARRAY_HPP