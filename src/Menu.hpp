// Copyright 2022 by Michał Gibas
#ifndef MENU_HPP
#define MENU_HPP

#include "Submenu.hpp"
#include "Array.hpp"
#include "DoublyLinkedList.hpp"

namespace sdizo {

class Menu {

public:
    int run();

private:
    void openSubmenuFor(size_t structureId);

    Submenu options[5] = {
        Submenu(new Array()),
        Submenu(new DoublyLinkedList()),
        Submenu(nullptr),
        Submenu(nullptr),
        Submenu(nullptr)
    };
};

};

#endif //MENU_HPP