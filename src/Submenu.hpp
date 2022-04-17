// Copyright 2022 by Michał Gibas
#ifndef SUBMENU_HPP
#define SUBMENU_HPP

#include "util/DataStructure.hpp"
#include "util/Clock.hpp"
#include "Strings.hpp"

namespace sdizo {

class Submenu {

public:
    Submenu(DataStructure* data, bool askForIndex=true);
    void run();

private:
    void printElements();
    void addElement();
    void findElement();
    void removeElement();
    void loadFromFile();
    void runTimeBenchmarks();

    void printOperationDuration();

    DataStructure* data;
    bool askForIndex;
    Clock operationClock;
};

};

#endif //SUBMENU_HPP