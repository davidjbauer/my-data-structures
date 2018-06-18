#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <string>
#include <memory>
/*
    LinkedList: A singly-linked list storing generic-typed data.

    In writing this I drew heavily from this stackexchange post:
    https://codereview.stackexchange.com/questions/96555/unit-testing-with-a-singly-linked-list

*/
template <typename T> 
struct LinkedList {
    
    // First we implement Node that points to its successor. 
    struct Node {
        // using dumb pointers because we're building a low-level data structure
        // if we're going to use smart pointers we should probably also be using STL
        Node* next;
        T value;

        Node(): value {}, next {nullptr} {};
        Node(const T& val): value {val}, next {nullptr} {};

    };

    int length;
    Node* head;
    Node* tail;

    LinkedList(): length {0}, head {nullptr}, tail {nullptr} {};

    //implement later
    /*  
    ~LinkedList() = delete;
    LinkedList(const LinkedList&) = delete;
    LinkedList(LinkedList&& ) = delete;
    LinkedList& operator=(const LinkedList&) = delete;
    LinkedList& operator=(LinkedList&&) = delete;
    */
    
    // Add a node to the head of the list
    void push_front(const T& data);
    // Add a node to the tail of the list
    void push_back(const T& data);
    // Remove the head node from the list and return its value 
    T pop_front();
    // Is the list empty?
    bool empty();
    // Delete the entire list, removing each Node from memory
    void clear();
    /* Stuff I want to implement:
        - STL-style iterator
    */

};

// Time complexity O(1)
template <typename T>
void LinkedList<T>::push_front(const T& data)
{
    Node* node = new Node(data);
    node->next = this->head;
    this->head = node;
    this->length++;
}

// Time complexity O(N)
// Could make this O(1) by maintaining a pointer to the tail node. I plan to do this.
template <typename T>
void LinkedList<T>::push_back(const T& data)
{
    Node* node = new Node;
    node = this->head;
    while(node->next)
    {
        node = node->next;
    }
    node->next = new Node(data);
    this->length++;
}

// Time complexity O(1)
template <typename T>
T LinkedList<T>::pop_front()
{
    T value = this->head->data;
    this->head = this->head->next;
    this->length--;
    return value;         
}

template <typename T>
bool LinkedList<T>::empty()
{
    if(head)
        return false;
    return true;
}

// Time complexity O(N)
template <typename T>
void LinkedList<T>::clear()
{
    Node* current = this->head;
    Node* temp;
    while(current->next)
    {    
        temp = current;
        current = current->next;
        delete temp;
        this->length--;
    }
    this->head = nullptr;
}

