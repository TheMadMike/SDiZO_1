// Copyright 2022 by Michał Gibas
#ifndef MENU_HPP
#define MENU_HPP

#include <string>

namespace sdizo {

class Menu {

public:
    int run();

private:
    void openSubmenuFor(size_t structureId);
};

};

#endif //MENU_HPP