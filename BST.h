#pragma once
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <memory>
/*
   BST: Binary search tree

   https://en.wikipedia.org/wiki/Binary_search_tree
   https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
*/


struct BST {
    struct BSTNode {
        int value;
        BSTNode* parent;
        BSTNode* left;
        BSTNode* right;
        BSTNode(int val):value{val},parent{nullptr},left{nullptr},right{nullptr}{};
    };

    BSTNode* root;
    size_t nodes;

    BST():root{nullptr},nodes{0}{};
    void insert(int);
    void remove(int);
    bool find(int,BSTNode*);
    bool find(int);
    void print();


};

bool BST::find(int val)
{
    return this->find(val,this->root);
}

bool BST::find(int val,BSTNode* head)
{
    BSTNode* current = head;
    while(current)
    {
        if(val == current->value)
        {
            return true;
        }
        else if(val < current->value){

            return find(val,current->left);
        }
        else{
            return find(val,current->right);
        }
    }
    return false;
}

//Tree insertion runs in O(h) time for tree of depth h.
void BST::insert(int val)
{
    if(!this->root)
    {
        this->root = new BSTNode(val);
    }
    else
    {
        BSTNode* current = this->root;

        BSTNode* node = new BSTNode(val);
        while(current)
        {   
            node->parent = current;
            if(val < current->value){
                current = current->left;
            }
            else{
                current = current->right;
            }
        }
        if(val < node->parent->value)
            node->parent->left = node;
        else
            node->parent->right=node;

    }
    this->nodes++;
}

// Remove the first node we find with a value
void BST::remove(int val)
{
    
}
