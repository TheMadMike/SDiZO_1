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

void shouldAddElements() {
    Array array;
    array.add(1);
    array.add(2);
    array.add(3);
    
    assert(array.getSize() == 3);
    array.add(0, 0);
    
    for(size_t i = 0; i < 4; ++i) {
        assert(array.getKey(i) == i);
    }
}

void shouldFindElement() {
    Array array;
    array.add(1);
    array.add(2);
    array.add(3);

    assert(array.find(3) == 2UL);
    assert(array.find(0) == -1);
}

void shouldRemoveElement() {
    Array array;
    array.add(1);
    assert(array.getSize() == 1);
    array.remove(-1);
    assert(array.getSize() == 0);
}

void shouldNotThrowWhenRemovedFromEmptyArray() {
    Array array;
    for(size_t i = 0; i < 10; ++i) {
        array.remove(-1);
        array.remove(-2);
        array.remove(1);
    }

    assert(array.getSize() == 0UL);
}

};

void runArrayTests() {
    ArrayTest::shouldCreateAnArrayIfEmpty();
    ArrayTest::shouldAddElements();
    ArrayTest::shouldFindElement();
    ArrayTest::shouldRemoveElement();
    ArrayTest::shouldNotThrowWhenRemovedFromEmptyArray();
}