#include <stdexcept>
#include <iostream>

#include "ArrayTest.cpp"
#include "ListTest.cpp"
#include "HeapTest.cpp"
#include "RBTreeTest.cpp"

int runTests();

int main(void) {   
    return runTests();
}

int runTests() {
    try {
        runArrayTests();
        runListTests();
        runHeapTests();
        runRBTreeTests();
    } catch(std::exception e) {
        std::cout << e.what() << "\n";
        return -1;
    }

    std::cout << "All tests passed :)\n";
    return 0;
}