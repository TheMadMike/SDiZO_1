#include "../Array.hpp"
#include <cassert>

using namespace sdizo;
namespace ArrayTest {

void shouldCreateAnArrayIfEmpty() {
    Array array;
    assert(array.getSize() == 0);
    array.add(0);
    assert(array.getSize() == 1);
}

};

void runArrayTests() {
    ArrayTest::shouldCreateAnArrayIfEmpty();
}