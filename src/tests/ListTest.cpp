#include "../DoublyLinkedList.hpp"
#include <cassert>

using namespace sdizo;
namespace ListTest {

void shouldAddElements() {
    DoublyLinkedList list;
    list.add(1);
    list.add(2);
    list.add(3);

    assert(list.getSize() == 3UL);
}

void shouldInsertInTheMiddle() {
    DoublyLinkedList list;
    list.add(1); list.add(3);
    list.add(2, 1UL);

    assert(list.getSize() == 3UL);
    assert(list.find(2) == 1UL);
}

};

void runListTests() {
    ListTest::shouldAddElements();
    ListTest::shouldInsertInTheMiddle();    
}