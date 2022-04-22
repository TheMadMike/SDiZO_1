#include "../MaxHeap.hpp"
#include <cassert>

using namespace sdizo;
namespace HeapTest {

void shouldAddElements() {
    MaxHeap heap;
    heap.add(1);
    heap.add(2);
    heap.add(3);

    /* 

    This heap should look like this:
      3
     / \
    1   2
    
    */

    assert(heap.getKey(0) == 3);
    assert(heap.getKey(1) == 1);
    assert(heap.getKey(2) == 2);
}

};

void runHeapTests() {
    HeapTest::shouldAddElements();
}