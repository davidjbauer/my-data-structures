#pragma once
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <memory>
/*
    HashMap: A basic hash table class.
 
    References used:
    https://www.geeksforgeeks.org/implementing-our-own-hash-table-with-separate-chaining-in-java/
    https://medium.com/@aozturk/simple-hash-map-hash-table-implementation-in-c-931965904250
    https://codereview.stackexchange.com/questions/14498/implementation-of-hash-map
    https://www.geeksforgeeks.org/implementing-hash-table-open-addressing-linear-probing-cpp/
    https://gist.github.com/aozturk/2368896
*/


// Starting with integer key/value pairs. Doing 
struct IntHashFunction{
    int operator()(const int &key) const
     {
         return 0;
     }
};

template <typename F = IntHashFunction>
struct IntHashMap {

    struct HashNode {
        int key;
        int value;
        HashNode* next;
        HashNode(const int &k, const int &v) : key {k}, value {v} {};
        HashNode() : key {0}, value {0} {};
    };

    HashNode** table;
    F hash_function;
    size_t buckets;
    size_t filled;

    IntHashMap(F f): buckets {5}, filled {0}, table {new HashNode*[5]},
                     hash_function {f}
                    {
                        for(int i; i < this->buckets; i++)
                        {
                            table[i] = nullptr;
                        }
                    };
    void add(const int&, const int&);
    size_t index(const int&);

};

template <typename F>
size_t IntHashMap<F>::index(const int &key)
{
    int hash = this->hash_function(key);
    size_t index = hash % buckets;
    return index;
}

template <typename F>
void IntHashMap<F>::add(const int &key, const int &value)
{

        size_t bucket_index = index(key);
        HashNode* head = nullptr;

        if(this->table[bucket_index])
        {
            head = this->table[bucket_index];
        }

        while (head)
        {
            if (head->key == key)
            {
                head->value = value;
                return;
            }
        }

        this->filled++;
        HashNode* node = new HashNode(key,value);
        node->next = head;
        this->table[bucket_index] = node;
 
        // if we get too full, resize array and copy
        if ((1.0*this->filled)/this->buckets >= 0.7)
        {
            HashNode** temp = this->table;
            this->buckets = 2 * this->buckets;
            this->table = new HashNode*[buckets];

            size_t temp_size = sizeof(temp)/(sizeof(temp[0]));
            for (unsigned i=0; i < temp_size; i++)
            {
                node = temp[i];
                while(node)
                {
                    this->add(node->key,node->value);
                    node = node->next;
                }
            }
            delete[] temp;
        }
}

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

