// Copyright 2022 by Michał Gibas
#include "RedBlackTree.hpp"

#include <iostream>

namespace sdizo {

RedBlackTree::RedBlackTree() 
:size(0UL) {
    nullLeaf = new Element;
    nullLeaf->color = BLACK;
    nullLeaf->left = nullptr;
    nullLeaf->right = nullptr;
    root = nullLeaf;
}

RedBlackTree::~RedBlackTree() {
    deleteSubtree(root);
    delete nullLeaf;
}

void RedBlackTree::deleteSubtree(Element* element) {
    if(element == nullLeaf)
        return;
    
    deleteSubtree(element->left);
    deleteSubtree(element->right);
    
    delete element;
}

void RedBlackTree::print() {
    printRecursive(root, 0UL);
}

void RedBlackTree::printRecursive(Element* element, size_t spaces) {
    if(element == nullLeaf) {
        std::cout << '\n';
        return;
    }
    
    std::cout << element -> value;
    if(element->color == BLACK)
        std::cout << "B\n";
    else
        std::cout << "R\n";

    if((element->left == nullLeaf) && (element->right == nullLeaf))
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
    Element* element = new Element;
    element->value = value;
    element->color = RED;
    element->left = nullLeaf;
    element->right = nullLeaf;

    Element* current = root;
    Element* prev = nullptr;

    if(root == nullLeaf){
        root = element;
    }
    else{

        while(current != nullLeaf){

            prev=current;
            if(element->value > current->value){
                current = current->right;
            }
            else{
                current = current->left;
            }
        }

        element->parent = prev;
        if(element->value > prev->value){
            prev->right = element;
        }
        else{
            prev->left = element;
        }
    }

    if(element->parent == nullptr){
        element->color = BLACK;
        return;
    }

    if(element->parent->parent == nullptr){
        return;
    }

    fixInsertion(element);
}

void RedBlackTree::fixInsertion(Element* element) {

    Element* uncle;

    while (element->parent->color == RED) {

      if (element->parent == element->parent->parent->right) {
        
        uncle = element->parent->parent->left;
        
        if (uncle->color == RED) {
        
          uncle->color = BLACK;
          element->parent->color = BLACK;
          element->parent->parent->color = RED;
          element = element->parent->parent;
        } else {
        
          if (element == element->parent->left) {
            element = element->parent;
            rotateRight(element);
          }
        
          element->parent->color = BLACK;
          element->parent->parent->color = RED;
          rotateLeft(element->parent->parent);
        }
      } else {
        
        uncle = element->parent->parent->right;

        if (uncle->color == RED) {
        
          uncle->color = BLACK;
          element->parent->color = BLACK;
          element->parent->parent->color = RED;
          element = element->parent->parent;
        } else {
        
          if (element == element->parent->right) {
            element = element->parent;
            rotateLeft(element);
          }
        
          element->parent->color = BLACK;
          element->parent->parent->color = RED;
          rotateRight(element->parent->parent);
        }
      }
      if (element == root) {
        break;
      }
    }
    root->color = BLACK;
}

void RedBlackTree::rotateLeft(Element* element) {
    if(element->right == nullLeaf){
        return;
    }

    Element* right = element->right;
    element->right = right->left;
    
    if (right->left != nullLeaf) {
      right->left->parent = element;
    
    }
    
    right->parent = element->parent;
    if (element->parent == nullptr) {
    
      root = right;
    
    } else if (element == element->parent->left) {
    
      element->parent->left = right;
    
    } else {
    
      element->parent->right = right;
    }
    
    right->left = element;
    element->parent = right;
} 

void RedBlackTree::rotateRight(Element* element) {
    if(element->left == nullLeaf){
        return;
    }

    Element* right = element->left;
    element->left = right->right;
    
    if(right->right != nullLeaf) {
      right->right->parent = element;
    }
    
    right->parent = element->parent;
    
    if(element->parent == nullptr) {
    
      root = right;
    
    } 
    else if(element == element->parent->right) {
    
      element->parent->right = right;
    
    } else {
    
      element->parent->left = right;
    }
    
    right->right = element;
    element->parent = right;
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
    else if(previous == previous->parent->left) {
        previous->parent->left = element;
    } else {
        previous->parent->right = element;
    }

    element->parent = previous->parent;



}

void RedBlackTree::removeByValue(int value) {
    Element* element = findElement(value);
    if(element == nullptr){
      return;
    }
    Element *elementToFix, *traverser;

    traverser = element;
    Color originalColor = traverser->color;
    
    if (element->left == nullLeaf) {
      elementToFix = element->right;
      replace(element, element->right);
    } 
    else if (element->right == nullLeaf) {
      elementToFix = element->left;
      replace(element, element->left);
    } 
    else {
        traverser = element->right;
    
        while(traverser->left != nullLeaf){
            traverser = traverser->left;
        }
    
        originalColor = traverser->color;
        elementToFix = traverser->right;
    
        if (traverser->parent == element) {
    
            elementToFix->parent = traverser;
        } 
        else {
    
            replace(traverser, traverser->right);
            traverser->right = element->right;
            traverser->right->parent = traverser;
      }

        replace(element, traverser);
        traverser->left = element->left;
        traverser->left->parent = traverser;
        traverser->color = element->color;
    }
    
    delete element;
    if (originalColor == BLACK) {
      fixRemoval(elementToFix);
    }

}

void RedBlackTree::fixRemoval(Element* element) {
    Element* brother;
    
    while (element != root && element->color == BLACK) {
    
      if (element == element->parent->left) {
    
        brother = element->parent->right;
    
        if (brother->color == RED) {
    
          brother->color = BLACK;
          element->parent->color = RED;
          rotateLeft(element->parent);
          brother = element->parent->right;
        }

        if (brother->left->color == BLACK && brother->right->color == BLACK) {
    
          brother->color = RED;
          element = element->parent;
        } else {
          if (brother->right->color == BLACK) {
    
            brother->left->color = BLACK;
            brother->color = RED;
            rotateRight(brother);
            brother = element->parent->right;
          }

          brother->color = element->parent->color;
          element->parent->color = BLACK;
          brother->right->color = BLACK;
          rotateLeft(element->parent);
          element = root;
        }
      } else {
    
        brother = element->parent->left;
    
        if (brother->color == RED) {
    
          brother->color = BLACK;
          element->parent->color = RED;
          rotateRight(element->parent);
          brother = element->parent->left;
        }

        if (brother->right->color == BLACK && brother->left->color == BLACK) {
    
          brother->color = RED;
          element = element->parent;
        } else {
    
          if (brother->left->color == BLACK) {
    
            brother->right->color = BLACK;
            brother->color = RED;
            rotateLeft(brother);
            brother = element->parent->left;
          }

          brother->color = element->parent->color;
          element->parent->color = BLACK;
          brother->left->color = BLACK;
          rotateRight(element->parent);
          element = root;
        }
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