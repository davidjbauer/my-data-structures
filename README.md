My implementations of some basic data structures in C++, with some tests written using Google Test.
I'm statically linking Google Test, so I've included the googletest directory here.

Implemented so far:
* singly-linked list with basic push, pop, clear operations. needs copy assignemnt operator, sort, maybe insert_after
* dynamically-sized hash map of integer keys & values, insertion but no deletion
* binary search tree of integers with insertion and ability to check if a value is in the tree

Build instructions:

`$ mkdir bin`

`$ cd bin`

`$ cmake ..`

`$ make`

