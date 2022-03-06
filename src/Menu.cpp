// Copyright 2022 by Michał Gibas
#include "Menu.hpp"
#include <iostream>

namespace sdizo {

int Menu::run() {
    std::cout << GREETING;
    std::cout << HORIZONTAL_SEPARATOR;

    size_t option = 0;
    do {
        std::cout << MENU_OPTIONS;
        std::cout << PROMPT;

        std::cin >> option; 

        openSubmenuFor(option);
    } while(option != 0);


    return 0;
}

void Menu::openSubmenuFor(size_t structureId) {
    if(structureId == 0) return;
    if(structureId > 5) {
        std::cout << "Invalid option\n";
        return;
    }

    options[structureId - 1].run();
}

};