// Copyright 2022 by Michał Gibas
#ifndef MAX_HEAP_HPP
#define MAX_HEAP_HPP

#include "Array.hpp"

namespace sdizo {

/* Maximum binary heap implementation */
class MaxHeap :public Array {

public:
    MaxHeap();
    virtual ~MaxHeap();

    void print() override;
    void add(int value, size_t index=-1) override;
    void remove(size_t index) override;
    void removeByValue(int value) override {
        size_t index = find(value);
        if(index == -1)
            return;
        remove(index);
    }

    void loadFromFile(const char* fileName) override;

    void push(int value);
private:
    size_t getParentIndex(size_t index);
    size_t getLeftIndex(size_t index);
    size_t getRightIndex(size_t index);

    void heapify(size_t index);

    void swapNodes(size_t a, size_t b);
};

};

#endif //MAX_HEAP_HPP