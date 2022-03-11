// Copyright 2022 by Michał Gibas
#ifndef SUBMENU_HPP
#define SUBMENU_HPP

#include "util/DataStructure.hpp"
#include "util/Clock.hpp"
#include "Strings.hpp"

namespace sdizo {

class Submenu {

public:
    Submenu(DataStructure* data);
    void run();

private:
    void printElements();
    void addElement();
    void findElement();
    void removeElement();
    void loadFromFile();

    void printOperationDuration();

    DataStructure* data;
    Clock operationClock;
};

};

#endif //SUBMENU_HPP