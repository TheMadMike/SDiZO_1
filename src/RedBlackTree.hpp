// Copyright 2022 by Michał Gibas
#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include "util/DataStructure.hpp"

namespace sdizo {

class RedBlackTree :public DataStructure {
public:

    RedBlackTree();
    virtual ~RedBlackTree();

    enum Color {
        BLACK = 0,
        RED = 1
    };

    struct Element {
        int value = 0;
        Color color = Color::RED;
        Element *parent = nullptr, *left = nullptr, *right = nullptr;
    };


    void print() override;
    void add(int value, size_t index=-1) override;
    void remove(size_t index=-1) override;
    size_t find(int value) override;

    inline Element* getRoot() { return root; }

    void rotateLeft(Element* element);
    void rotateRight(Element* element);

private:
    void printRecursive(Element* element, size_t spaces);
    void deleteSubtree(Element* element);

    void fix(Element* element);

    Element* root;
    size_t size;
};

};

#endif //RED_BLACK_TREE_HPP