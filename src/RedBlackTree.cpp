// Copyright 2022 by Michał Gibas
#include "RedBlackTree.hpp"

#include <iostream>

namespace sdizo {

RedBlackTree::RedBlackTree() 
:root(nullptr), size(0UL) {

}

RedBlackTree::~RedBlackTree() {
    deleteSubtree(root);
}

void RedBlackTree::deleteSubtree(Element* element) {
    if(element == nullptr)
        return;
    
    deleteSubtree(element->left);
    deleteSubtree(element->right);
    
    delete element;
}

void RedBlackTree::print() {
    printRecursive(root, 0UL);
}

void RedBlackTree::printRecursive(Element* element, size_t spaces) {
    if(element == nullptr) {
        std::cout << '\n';
        return;
    }
    
    std::cout << element -> value;
    if(element->color == BLACK)
        std::cout << "B\n";
    else
        std::cout << "R\n";

    if((element->left == nullptr) && (element->right == nullptr))
        return;
    
    for(size_t i = 0; i < spaces; ++i)
        std::cout << ' ';

    std::cout << "|L=";
    printRecursive(element->left, spaces + 4);

    for(size_t i = 0; i < spaces; ++i)
        std::cout << ' ';
    std::cout << "|R=";
    printRecursive(element->right, spaces + 4);


}

void RedBlackTree::add(int value, size_t index) {
    //if the tree is empty, then create a new root
    if(root == nullptr) {
        root = new Element;
        root->value = value;
        root->color = BLACK;
        return;
    }

    //firstly, insert the element as in BST
    Element* element = new Element;
    element->value = value;

    Element* iterator = root;
    while(iterator != nullptr) {

        //determine wheter to choose 
        //the right or the left node
        if(iterator->value <= value) {
            if(iterator->right == nullptr) {
                iterator->right = element;
                element->parent = iterator;
                break;
            }

            iterator = iterator->right;
            continue;
        }

        if(iterator->left == nullptr) {
            iterator->left = element;
            element->parent = iterator;
            break;
        }

        iterator = iterator->left;

    }

    //then, perform rotations and change colors to preserve RBT conditions
    fix(element);
}

void RedBlackTree::fix(Element* element) {

    Element* uncle;

    while((element != root) && (element->parent->color == RED)) {
        Element* grandparent = element->parent->parent;

        if(grandparent->left == element->parent) {

            if(grandparent->right != nullptr) {
                uncle = grandparent->right;

                if(uncle->color == RED) {
                    element->parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    element = grandparent;
                }

            } else {
                
                if(element->parent->right == element) {
                    element = element->parent;
                    rotateLeft(element);
                }

                element->parent->color = BLACK;
                grandparent->color = RED;
                rotateRight(grandparent);
            }

        } else {
            if(grandparent->left != nullptr) {

                uncle = grandparent->left;

                if(uncle->color == RED) {
                    element->parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    element = grandparent;
                }

            } else {

                if(element->parent->left == element) {
                    element = element->parent;
                    rotateRight(element);
                }

                element->parent->color = BLACK;
                grandparent->color = RED;
                rotateLeft(grandparent);

            }   

        }
    }

    root->color = BLACK;
}

void RedBlackTree::rotateLeft(Element* element) {
    if(element->right == nullptr) {
        return;
    }

    Element* right = element->right;
    element->right = right->left;
    
    if(right->left != nullptr) {
        right->left->parent = element;
    }

    right->parent = element->parent;
    if(element->parent == nullptr) {
        root = right;
    }
    else if(element == element->parent->left) {
        element->parent->left = right;
    } else {
        element->parent->right = right;
    }

    right->left = element;
    element->parent = right;
} 

void RedBlackTree::rotateRight(Element* element) {
    if(element->left == nullptr) {
        return;
    }

    Element* left = element->left;
    element->left = left->right;
    
    if(left->right != nullptr) {
        left->right->parent = element;
    }

    left->parent = element->parent;
    if(element->parent == nullptr) {
        root = left;
    }
    else if(element == element->parent->right) {
        element->parent->right = left;
    } else {
        element->parent->left = left;
    }

    left->right = element;
    element->parent = left;
}

void RedBlackTree::remove(size_t index) {

}

size_t RedBlackTree::find(int value) {

}

void RedBlackTree::loadFromFile(const char* fileName) {

}

};