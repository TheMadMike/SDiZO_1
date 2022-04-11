set(TEST_SOURCES
tests.cpp
../Array.cpp
../DoublyLinkedList.cpp
../Strings.cpp)

set(TEST_TARGET
test
)

add_executable(${TEST_TARGET} ${TEST_SOURCES})