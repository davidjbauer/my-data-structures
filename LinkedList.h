#pragma once
#include <iostream>
#include <cmath>
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
    ~LinkedList();
    LinkedList(const LinkedList<T>*);

    // TO DO
    LinkedList(LinkedList<T>&& ) = delete;
    LinkedList& operator=(const LinkedList<T>*);
    LinkedList& operator=(LinkedList<T>&&) = delete;

    
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

    // TO DO
    bool search(const T& value);
    void insert_after(const T& find_val, const T& insert_val);
    void sort();
    /* Stuff I want to implement:
        - STL-style iterator
    */

};

template <typename T>
LinkedList<T>::~LinkedList()
{
    if(this->head)
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

        delete current;
    }

}

// help from https://codereview.stackexchange.com/questions/121488/linked-list-with-deep-copy-constructor
// you know it's gotta be O(n), buddy.
template <typename T>
LinkedList<T>::LinkedList(const LinkedList* list)
{
    this->length = 0;

    if(!list->head)
        this->head = nullptr;
    else
    {

        Node* temp = new Node(list->head->value);
        Node* current = temp;
        Node* parent_head = list->head;
        Node* parent_node = list->head;

        while (parent_node->next) 
        {

            current->next = new Node(parent_node->next->value);
            parent_node = parent_node->next;
            current = current->next;
            this->length++;
        }
        this->head=temp;
    }
}

// Time complexity O(1)
template <typename T>
void LinkedList<T>::push_front(const T& data)
{
    Node* node = new Node(data);
    node->next = this->head;
    if(!this->head)
        this->tail = node;
    this->head = node;
    this->length++;
}

// Time complexity O(1) at the expense of maintaining tail pointer.
template <typename T>
void LinkedList<T>::push_back(const T& data)
{
    Node* node = new Node(data);
    this->tail->next = node;
    this->tail = node;
    this->length++;
}
// template <typename T>
// void LinkedList<T>::push_back(const T& data)
// {
//     Node* node = new Node;
//     node = this->head;
//     while(node->next)
//     {
//         node = node->next;
//     }
//     node->next = new Node(data);
//     this->length++;
// }

// Time complexity O(1)
template <typename T>
T LinkedList<T>::pop_front()
{
    Node* n = this->head;
    T value = this->head->value;
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
    delete current;
    this->head = nullptr;
}

