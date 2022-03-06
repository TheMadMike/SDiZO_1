// Copyright 2022 by Michał Gibas
#include "Submenu.hpp"

#include <iostream>

namespace sdizo {

Submenu::Submenu(DataStructure* data) 
:data(data) {

}

void Submenu::run() {
    std::cout << HORIZONTAL_SEPARATOR;

    size_t option = 0;
    do {
        std::cout << SUBMENU_OPTIONS << PROMPT;
        std::cin >> option;
        
        switch(option) {
            case 1: addElement(); break;
            case 2: removeElement(); break;
            case 3: findElement(); break;
            case 4: printElements(); break;
            case 5: loadFromFile(); break;
            default: std::cout << "Invalid option\n"; break;
        }

    } while(option != 0);
}

void Submenu::printElements() {
    data->print();
}

int readValueFromStdin();
size_t readIndexFromStdin();

void Submenu::addElement() {
    size_t index = readIndexFromStdin();
    int value = readValueFromStdin();

    data->add(value, index);
}

void Submenu::removeElement() {
    data->remove(readValueFromStdin());
}

void Submenu::findElement() {
    std::cout << data->find(readValueFromStdin()) << '\n';
}

void Submenu::loadFromFile() {
    std::string fileName;
    std::cout << "File name: "; std::cin >> fileName;
    data->loadFromFile(fileName.c_str());
}

int readValueFromStdin() {
    int value = 0;
    std::cout << "Value: "; std::cin >> value;
    return value;
}

size_t readIndexFromStdin() {
    size_t index = -1;
    std::cout << "Index [-1 -> last]: "; std::cin >> index;
    return index;
}

};
