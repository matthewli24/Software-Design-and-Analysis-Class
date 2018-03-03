/******************************************************************************
  Title          : bst.cpp
  Author         : Matthew Li
  Created on     : December 02, 2017
  Description    : Implementation for the Binary Search Tree class template
  Purpose        : The implementation of the BST class template 
  Modifications  : 

******************************************************************************/
#include <iostream>
#include "stdlib.h"
#include <fstream>

#include "bst.h"

using namespace std;

/*******************************************************************************   
                     BST CLASS TEMPLATE IMPLEMENTATION
*******************************************************************************/
//Constructor that sets root to NULL and size to 0
template <class T>
BST<T>::BST()
{
    root = NULL;
    size = 0;
};

template <class T>
BST<T>::BST(const BST &tree)
{
    copy_tree(tree.root, root);
    
};

/*
template <class T>
BST<T>& BST<T>::operator = (const BST<T> &tree)
{
    copy_tree(tree.root, this->root);
    return *this;
};
*/

template <class T>
void BST<T>::copy_tree(node<T>* tree_ptr, node<T>* &new_ptr)
{
    //preorder traversal
    if(tree_ptr != NULL){
        new_ptr = new node<T>;
        new_ptr->data  = tree_ptr->data;
        new_ptr->left  = NULL; 
        new_ptr->right = NULL;
        copy_tree(tree_ptr->left, new_ptr->left);
        copy_tree(tree_ptr->right, new_ptr->right);
    }

    else{
        new_ptr = NULL; //copy empty tree
    }
};

template <class T>
int BST<T>::tree_size()
{
    return size;
};

template <class T>
node<T>* BST<T>::get_root()
{
    return root;
};

template <class T>
BST<T>::~BST()
{
    destroy();
};

template <class T>
void BST<T>::write(ostream &os)
{
    write(os, root);
};

template <class T>
void BST<T>::write(ostream &os, node<T>* &link)
{
    node<T>* current = link;

    //write to os with in-order traversal
    if(current != NULL){
        write(os, current->left);
        current->data.print(os);
        write(os, current->right);
    }

};


template <class T>
//inserts new_item to the sorted list
bool BST<T>::insert(T new_item)
{
    bool success = insert(root, new_item);
    if(success){
        size++;
    }
    return success;
};

template <class T>
//inserts new_item to the sorted list
bool BST<T>::insert(node<T>* &current, T new_item)
{
    //preorder traversal, insert if empty/NULL found
    if(current == NULL){
        node<T>* p;
        p = new node<T>;
        if(p == NULL){
            cerr << "Out of Memory\n";
            exit(1);
        }
        p->data = new_item;
        p->left = NULL;
        p->right = NULL;
        current = p;
        return true;
    }

    else if(new_item < current->data){
        insert(current->left, new_item);
    }

    else if(current->data < new_item){
        insert(current->right, new_item);
    }

    else{
        return false;
    };

};

template <class T>
//remove item from the sorted list
int BST<T>::remove(const int objectId)
{
    return remove(root, objectId);
};

template <class T>
int BST<T>::remove(node<T>* &current, const int objectId)
{
    int count = 0;

    if(current == NULL){ //object not found
        return count;    
    }

    else if(objectId < current->data){
        remove(current->left, objectId);
    }

    else if(current->data < objectId){
        remove(current->right, objectId);
    }

    else{
        //item is equal to the item in node
        //check how many children it has
        if(current->left != NULL && current->right != NULL){
            //it has two children. Need to replace it by the smallest node
            //in the right subtree.
            
            //get the pointer to the smallest node in the right subtree
            node<T>* temp = findmin(current->right);

            //copy the item into the current node
            current->data = temp->data;

            //recursively call remove to delete the item that was copied
            remove(current->right, current->data.get_id());
        }

        else{
            //the current node has at most one child.
            node<T>* old = current;

            //if left child is not empty, make the left child the child
            //of the parent of current.
            if(current->left != NULL){
                current = current->left;
            }
            else{
                current = current->right;
            }

            //delete the node current use to point to
            delete old;
            size--;
            count = count + 1;
            return count;
        }
                
    }//outmost else
    
};

template <class T>
node<T>* BST<T>::findmin(node<T>* current)
{
    if(current == NULL){
        return NULL;
    }

    if(current->left == NULL){
        return current;
    }

    return findmin(current->left);
};

template <class T>
int BST<T>::find(const int objectId, T &copy)
{
    return find(root, objectId, copy);
};

template <class T>
int BST<T>::find(node<T>* &current, const int objectId, T &copy)
{

    if(current == NULL){
        return 0;
    }

    else{
        if(objectId < current->data){
            find(current->left, objectId, copy);
        }

        else if(current->data < objectId){
            find(current->right, objectId, copy);
        }

        else{ //item is in the current node
            copy = current->data;
            return 1;
        }
    }
};

template <class T>
int BST<T>::findsmallest(T &copy)
{
    node<T>* temp = findmin(root);
    if(temp != NULL){
        copy = temp->data;
        return 1;
    } 
    else{
        return 0;
    }
};

template <class T>
void BST<T>::destroy()
{
    destroy(root);
};

template <class T> 
void BST<T>::destroy(node<T>* &current)
{
    //postorder traversal 
    if(current != NULL){
        destroy(current->left);
        destroy(current->right);
        delete current;
        current = NULL;
    }
};

