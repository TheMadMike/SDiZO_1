#include "../RedBlackTree.hpp"
#include <cassert>

using namespace sdizo;

namespace RBTreeTest {

RedBlackTree initRBT() {
    RedBlackTree rbt;

    rbt.add(2); //      2
    rbt.add(1); //     / /
    rbt.add(3); //    1  3

    return rbt;
}

void shouldRotateLeft() {
    auto rbt = initRBT();

    rbt.rotateLeft(rbt.getRoot());
    /*       3
            /
           2
          /
         1      */

    assert(rbt.getRoot()->value == 3);
    assert(rbt.getRoot()->right == nullptr);
    assert(rbt.getRoot()->left->value == 2);
    assert(rbt.getRoot()->left->left->value == 1);
}

void shouldRotateRight() {
    auto rbt = initRBT();

    rbt.rotateRight(rbt.getRoot());
    /*  1
         \
          2
           \
            3 */

    assert(rbt.getRoot()->value == 1);
    assert(rbt.getRoot()->left == nullptr);
    assert(rbt.getRoot()->right->value == 2);
    assert(rbt.getRoot()->right->right->value == 3);
}

};

void runRBTreeTests() {
    RBTreeTest::shouldRotateLeft();
    RBTreeTest::shouldRotateRight();
}