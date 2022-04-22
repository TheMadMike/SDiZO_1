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

    if(element->parent->parent == nullptr)
        return;

    //then, perform rotations and change colors to preserve RBT conditions
    fixInsertion(element);
}

void RedBlackTree::fixInsertion(Element* element) {

    Element* uncle;

    while((element != root) && (element->parent->color == RED)) {
        Element* grandparent = element->parent->parent;
        if(grandparent == nullptr) {
            break;
        }

        if(element->parent == grandparent->right) {
            uncle = grandparent->left;

            if(uncle != nullptr) {
                if(uncle->color == RED) {

                    uncle->color = BLACK;
                    element->parent->color = BLACK;
                    grandparent->color = RED;
                    element = grandparent;
                } else {
                    if(element == element->parent->left) {
                        element = element->parent;
                        grandparent = element->parent->parent;
                        rotateRight(element);
                    }

                    element->parent->color = BLACK;
                    if(grandparent != nullptr)
                        grandparent->color = RED;
                    rotateLeft(grandparent);
                }
            } else {

                if(element == element->parent->left) {
                    element = element->parent;
                    grandparent = element->parent->parent;
                    rotateRight(element);
                }

                element->parent->color = BLACK;
                if(grandparent != nullptr)
                    grandparent->color = RED;
                rotateLeft(grandparent);
            }

        } else {
            uncle = grandparent->right;
            if(uncle != nullptr) {
                if(uncle->color == RED) {

                    uncle->color = BLACK;
                    element->parent->color = BLACK;
                    element->parent->color = RED;
                    element = grandparent;
                } else {

                    if(element == element->parent->right) {
                        element = element->parent;
                        grandparent = element->parent->parent;
                        rotateLeft(element);
                    }

                    element->parent->color = BLACK;
                    if(grandparent != nullptr)
                        grandparent->color = RED;
                    rotateRight(grandparent);
                }
            } else {
                if(element == element->parent->right) {
                    element = element->parent;
                    grandparent = element->parent->parent;
                    rotateLeft(element);
                }

                element->parent->color = BLACK;
                if(grandparent != nullptr)
                        grandparent->color = RED;
                rotateRight(grandparent);
            }

        }
    }

    root->color = BLACK;
}

void RedBlackTree::rotateLeft(Element* element) {
    if(element == nullptr) {
        return;
    }
    
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
    if(element == nullptr) {
        return;
    }

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
    if(index == -1) {
        removeByValue(root->value);
    }
}

void RedBlackTree::replace(Element* previous, Element* element) {

    if(previous->parent == nullptr) {
        root = element;
    }
    else if (previous == previous->parent->left) {
      previous->parent->left = element;
    } else {
      previous->parent->right = element;
    }

    if(element != nullptr) {
        element->parent = previous->parent;
    }



}

void RedBlackTree::removeByValue(int value) {
    Element* element = findElement(value);
    if(element == nullptr) {
        return;
    }

    Element *elementToFix;
    Element* iterator = element;

    Color originalColor = iterator->color;

    if(element->right == nullptr) {
        elementToFix = element->left;
        replace(element, element->left);
    }

    else if (element->left == nullptr) {
        elementToFix = element->right;
        replace(element, element->right);
    } else {
        iterator = element->right;

        while(iterator->left != nullptr) {
            iterator = iterator->left;
        }

        originalColor = iterator->color;
        elementToFix = iterator->right;
        
        if(iterator->parent == element) {
            if(elementToFix != nullptr) {
                elementToFix->parent = iterator;
            }
        } else {
            replace(iterator, iterator->right);
            iterator->right = element->right;
            iterator->right->parent = iterator;
        }

        replace(element, iterator);
        iterator->left = element->left;
        iterator->left->parent = iterator;
        iterator->color = element->color;

    }

    delete element;
    element = nullptr;
    if(originalColor == BLACK)
        fixRemoval(elementToFix);

}

void RedBlackTree::fixRemoval(Element* element) {
    if(element == nullptr || element->parent == nullptr) {
        return;
    }
    Element* brother;

    while(element->color == BLACK && element != root) {
        if(element->parent->left == element) {
            brother = element->parent->right;

            if(brother == nullptr) {
                element = element->parent;
                continue;
            }

            if(brother->color == RED) {
                brother->color = BLACK;
                element->parent->color = RED;
                rotateLeft(element->parent);
                brother = element->parent->right;
            }

            if(brother != nullptr) {

                if(brother->left == nullptr && brother->right == nullptr) {
                    brother->color = RED;
                    element = element->parent;
                }

                Color leftColor = brother->left == nullptr ? BLACK : brother->left->color;
                Color rightColor = brother->right == nullptr ? BLACK : brother->right->color;

                if(leftColor == BLACK && rightColor == BLACK) {
                    brother->color = RED;
                    element = element->parent;
                    
                } else {
                    if(brother->right == nullptr) {
                        if(brother->left != nullptr) {
                            brother->left->color = BLACK;
                        }
                        brother->color = RED;
                        rotateRight(brother);
                        brother = element->parent->right;
                    } 
                    
                    else if(rightColor == BLACK) {
                        if(brother->left != nullptr) {
                            brother->left->color = BLACK;
                        }
                        brother->color = RED;
                        rotateRight(brother);
                        brother = element->parent->right;
                    }

                    brother->color = element->parent->color;
                    if(element->parent != nullptr) {
                        element->parent->color = BLACK;
                    }

                    if(brother->right != nullptr) {
                        brother->right->color = BLACK;
                    }
                    rotateLeft(element->parent);
                    element = root;
                }
            }

        } else {
            brother = element->parent->left;

            if(brother == nullptr) {
                element = element->parent;
                continue;
            }

            if(brother->color == RED) {
                brother->color = BLACK;
                element->parent->color = RED;
                rotateRight(element->parent);
                brother = element->parent->left;
            }

            if(brother != nullptr) {

                if(brother->left == nullptr && brother->right == nullptr) {
                    brother->color = RED;
                    element = element->parent;
                }

                Color leftColor = brother->left == nullptr ? BLACK : brother->left->color;
                Color rightColor = brother->right == nullptr ? BLACK : brother->right->color;

                if(leftColor == BLACK && rightColor == BLACK) {
                    brother->color = RED;
                    element = element->parent;
                    
                } else {
                    if(brother->left == nullptr) {
                        if(brother->right != nullptr) {
                            brother->right->color = BLACK;
                        }
                        brother->color = RED;
                        rotateRight(brother);
                        brother = element->parent->right;
                    } 
                    
                    else if(leftColor == BLACK) {
                        if(brother->right != nullptr) {
                            brother->right->color = BLACK;
                        }
                        brother->color = RED;
                        rotateLeft(brother);
                        brother = element->parent->left;
                    }

                    brother->color = element->parent->color;
                    if(element->parent != nullptr) {
                        element->parent->color = BLACK;
                    }
                    if(brother->left != nullptr) {
                        brother->left->color = BLACK;
                    }
                    rotateRight(element->parent);
                    element = root;
                }
            }

        }
        if(element == nullptr) {
            return;
        }
    }
    element->color = BLACK;
}

RedBlackTree::Element* RedBlackTree::findElement(int value) {
    Element* traverser = root;
    while(traverser != nullptr) {
        if(traverser->value == value) {
            break;
        }

        if(traverser->value <= value) {
            traverser = traverser->right;
        } else {
            traverser = traverser->left;
        }
    }

    return traverser;
}

size_t RedBlackTree::find(int value) {
    if(findElement(value) == nullptr)
        return 0;
    return 1;
}

};