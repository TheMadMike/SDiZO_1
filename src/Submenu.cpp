// Copyright 2022 by Michał Gibas
#include "Submenu.hpp"

#include <iostream>
#include "util/Benchmark.hpp"

namespace sdizo {

Submenu::Submenu(DataStructure* data, bool askForIndex) 
:data(data), askForIndex(askForIndex) {
    
}

void Submenu::run() {
    std::cout << HORIZONTAL_SEPARATOR;

    size_t option = 0;
    do {
        std::cout << SUBMENU_OPTIONS << PROMPT;
        std::cin >> option;

        if(option == 6) {
            runTimeBenchmarks();
            continue;
        }
        
        switch(option) {
            case 1: addElement(); break;
            case 2: removeElement(); break;
            case 3: findElement(); break;
            case 4: printElements(); break;
            case 5: loadFromFile(); break;
            default: std::cout << "Invalid option\n"; break;
        }

        operationClock.stop();
        printOperationDuration();
        

    } while(option != 0);
}

void Submenu::printElements() {
    operationClock.start();
    data->print();
}

int readValueFromStdin();
size_t readIndexFromStdin();

void Submenu::addElement() {
    size_t index = -1;
    if(askForIndex) {
        index = readIndexFromStdin();
    }

    int value = readValueFromStdin();

    operationClock.start();
    data->add(value, index);
    
}

void Submenu::removeElement() {
    operationClock.start();
    data->remove(readIndexFromStdin());
}

void Submenu::findElement() {
    int value = readValueFromStdin();

    operationClock.start();
    size_t index = data->find(value);
    
    if(index == -1) {
        std::cout << "Element not found!\n";
        return;
    }
    
    std::cout << index;
    std::cout << '\n';
}

void Submenu::loadFromFile() {
    std::string fileName;
    std::cout << "File name: "; std::cin >> fileName;
    operationClock.start();
    data->loadFromFile(fileName.c_str());
}

void Submenu::runTimeBenchmarks() {
    std::string filePrefix;
    std::cout << "Output file prefix: "; std::cin >> filePrefix;
    
    size_t sampleCount;
    std::cout << "Number of samples: "; std::cin >> sampleCount;

    std::cout << "Sample sizes [" << sampleCount << "]\n";

    size_t* sampleSizes = new size_t[sampleCount];

    for(size_t i = 0; i< sampleCount; ++i) {
        std::cin >> sampleSizes[i];
    }

    size_t repetitions;
    std::cout << "Repetitions: "; std::cin >> repetitions;

    std::cout << "For insertion: ";
    size_t insertIndex = readIndexFromStdin();

    std::cout << "For removal: ";
    size_t removeIndex = readIndexFromStdin();


    Benchmark benchmark(data, filePrefix.c_str());
    benchmark.setSampleSizes(sampleSizes, sampleCount);
    benchmark.setRepetitions(3);
    benchmark.setInsertionIndex(insertIndex);
    benchmark.setRemovalIndex(removeIndex);
    benchmark.run();

    delete[] sampleSizes;
}

void Submenu::printOperationDuration() {
    std::cout << "Total operation time: " << operationClock.getDurationMs()
        << "ms\n\n";
}

int readValueFromStdin() {
    int value = 0;
    std::cout << "Value: "; std::cin >> value;
    return value;
}

size_t readIndexFromStdin() {
    size_t index = -1;
    std::cout << INDEX_PROMPT; std::cin >> index;
    return index;
}

};
