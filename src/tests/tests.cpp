#include <stdexcept>
#include <iostream>

#include "ArrayTest.cpp"
#include "ListTest.cpp"
#include "HeapTest.cpp"

int runTests();

int main(void) {   
    return runTests();
}

int runTests() {
    try {
        runArrayTests();
        runListTests();
        runHeapTests();
    } catch(std::exception e) {
        std::cout << e.what() << "\n";
        return -1;
    }

    std::cout << "All tests passed :)\n";
    return 0;
}