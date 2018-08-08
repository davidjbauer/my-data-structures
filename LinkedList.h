#pragma once
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <memory>
#include <sstream>
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
    LinkedList& operator=(const LinkedList<T>*);
    // TO DO
    LinkedList(LinkedList<T>&& ) = delete;
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
    // Print the list in the form "val1->val2->..."
    void print();
    // Return a sorted copy of the list.
    LinkedList* sorted();



    // TO DO
    bool search(const T& value);
    void insert_after(const T& find_val, const T& insert_val);
private:
    //Node* step_ahead(const Node* start ,size_t steps);


};


// Destructor
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

// Copy constructor (deep copy).
// help from https://codereview.stackexchange.com/questions/121488/linked-list-with-deep-copy-constructor
// time O(n)
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
// push an element to the front of the list
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

// push to the back of the list
// Time complexity O(1) at the expense of maintaining tail pointer.
template <typename T>
void LinkedList<T>::push_back(const T& data)
{
    Node* node = new Node(data);
    this->tail->next = node;
    this->tail = node;
    this->length++;
}

// remove the front of the list and return it
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

// check if the list is empty
template <typename T>
bool LinkedList<T>::empty()
{
    if(head)
        return false;
    return true;
}

// Delete the entire list
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


// sort a LinkedList of ints
// using Merge Sort for this, per https://www.chiark.greenend.org.uk/~sgtatham/algorithms/listsort.html
// and https://stackoverflow.com/questions/1525117/whats-the-fastest-algorithm-for-sorting-a-linked-list
// Time complexity O(n log n)
template <>
LinkedList<int>* LinkedList<int>::sorted()
{
    // std::cout << "Entering sorted()" << std::endl;

    size_t step_size = 1;
    bool done = false;
    LinkedList<int>* temp = this;
    while(!done)
    {
        LinkedList<int>* list = temp;
        temp = new LinkedList<int>();
        //std::cout << "!done" << std::endl;
        size_t merge_count = 0;

        Node* p_node = list->head;
        
        //std::cout << "Outside while loop" << std::endl;
        while(p_node)
        {
            merge_count++;
            //std::cout << "Entering while(p_node)" << std::endl;
            //std::cout << "Step size is currently " << step_size << std::endl;
            //std::cout << "Merge count is currently " << merge_count << std::endl;
            Node* q_node = p_node;
            size_t p_size = 0;
            size_t q_size = step_size;
            for(int i=0; i < step_size; i++)
            {
                //std::cout << "In for loop, i=" << i << std::endl;
                p_size++;
                if(q_node->next)
                {
                    //std::cout << "q_node->next exists, step." << std::endl;
                    q_node = q_node->next;

                }
                else
                {
                    //std::cout << "No q_node->next, breaking for loop." << std::endl;
                    q_node = q_node->next;
                    break;
                }

            }

            while(p_size > 0 || (q_size > 0 && q_node))
            {
                //std::cout << "--> We have a p or a q, so we need to merge." << std::endl;
                //std::cout << "--> p_size = " << p_size << ", q_size = " << q_size << std::endl;
                int val;
                if(!q_node || q_size == 0)
                {
                    // std::cout << "-->--> p_value = " << p_node->value << std::endl;
                    // std::cout << "-->--> No q_node, use p value" << std::endl;
                    val = p_node->value;
                    p_node = p_node->next;
                    p_size--;
                }
                else if(!p_node || p_size==0)
                {
                    // std::cout << "-->--> q_value = " << q_node->value << std::endl;
                    // std::cout << "-->--> No p_node, use q value" << std::endl;
                    val = q_node->value;
                    q_node = q_node->next;
                    q_size--;
                }
                else if(q_node->value < p_node->value)
                {
                    // std::cout << "-->--> p_value = " << p_node->value << ", q_value = " << q_node->value << std::endl;
                    // std::cout << "-->--> q less than p" << std::endl;
                    val = q_node->value;
                    q_node = q_node->next;
                    q_size--;
                }
                else if(q_node->value > p_node->value)
                {
                    // std::cout << "-->--> p_value = " << p_node->value << ", q_value = " << q_node->value << std::endl;
                    // std::cout << "-->--> q greater than p" << std::endl;
                    val = p_node->value;
                    p_node = p_node->next;
                    p_size--;
                }
                else if(q_node->value == p_node->value)
                {
                    // std::cout << "--> p_value = " << p_node->value << ", q_value = " << q_node->value << std::endl;
                    // std::cout << "--> q==p, use p value" << std::endl;
                    val = p_node->value;
                    p_node = p_node->next;
                    p_size--;
                }
                // std::cout << "--> Current value we're pushing to list " << val << std::endl;
                if(temp->head)
                    temp->push_back(val);
                else
                    temp->push_front(val);
            }

            // std::cout << "Set p_node = q_node" << std::endl;
            p_node = q_node;
            
        }

        if(merge_count == 1)
        {
            // std::cout << "Merge count is 1." << std::endl;
            p_node = nullptr;
            done = true;
            return temp;
        }
        // std::cout << "Double step size" << std::endl;
        step_size = 2*step_size;
    }
    
}

template <typename T>
LinkedList<T>* LinkedList<T>::sorted()
{
    return nullptr;
}

template <typename T>
void LinkedList<T>::print()
{
    Node* node = this->head;
    std::stringstream ss;
    if(!node)
    {
        std::cout << "(Empty list)" << std::endl;
    }

    while(node->next)
    {
        ss << "(" << node->value << ")->";   
        node = node->next;
    }
    ss << "(" << node->value << ")";

    std::cout << ss.str() << std::endl;
}

