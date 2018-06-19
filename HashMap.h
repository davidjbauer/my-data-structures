#pragma once
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <string>
#include <memory>
#include "LinkedList.h"
/*
    HashMap: A basic hash table class.
 
    References used:
    https://www.geeksforgeeks.org/implementing-our-own-hash-table-with-separate-chaining-in-java/
    https://medium.com/@aozturk/simple-hash-map-hash-table-implementation-in-c-931965904250
    CLRS
    https://codereview.stackexchange.com/questions/14498/implementation-of-hash-map

*/

// starting with integer key/value pairs. doing this in maybe a dumb way...
struct HashFunction{
    int operator()(const int &key) const
     {
         return 0;
     }
};

struct IntHashMap {

    struct KeyVal {int key, value;}; 

    LinkedList<KeyVal>* table;
    HashFunction hash_function;
    unsigned length;
    unsigned filled;

    IntHashMap(HashFunction f): length {2}, 
                                    filled {0}, 
                                    table {new LinkedList<KeyVal>[2]},
                                    hash_function {f} {};

};



// template <typename K, typename V, typename F=HashFunction<K>> 
// struct HashMap {
    
//     struct HashNode {

//         HashNode* next;
//         K key;
//         V value;

//         HashNode(): key {}, value {}, next {} {};
//         HashNode(const K& k, const V& v): key {k}, value {v}, next {nullptr} {};

//     };

//     HashNode hash_node;
//     F hash_function;

// };
// Default hash function class
// template <typename K>
// struct HashFunction {
//     unsigned long operator()(const K& key) const
//     {
//         return reinterpret_cast<unsigned long>(key);
//     }
// };

