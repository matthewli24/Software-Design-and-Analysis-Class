/******************************************************************************
  Title          : bst.h
  Author         : Matthew Li
  Created on     : December 02, 2017
  Description    : Interface for the Binary Search Tree class template
  Purpose        : The BST class template 
  Modifications  : 

******************************************************************************/
#ifndef BST_H__
#define BST_H__

#include <fstream>
#include <iostream>

using namespace std;

/*******************************************************************************   
                       BST CLASS TEMPLATE INTERFACE
*******************************************************************************/
/*template for node*/
template <class T>
struct node{
    T data;
    node* left;
    node* right;
};

template<class T>
class BST
{
    public:
        //Constructor that sets head to NULL and size to 0
        BST();
        
        //Copy Constructor
        BST(const BST & tree);
        
        //Copy Assignment Operator
        //BST<T>& operator = (const BST<T> &tree);

        //Destructor
        ~BST();
        
        //returns the size
        int tree_size();

        /* write() - wrapper function
         * @pre  - ostream is open for writing
         * @post - write the entire tree onto an open ostream 
         * */
        void write(ostream &os);

        /* insert() - put new_item into the BST
         * @param T new_item [in] - a object of type T
         * @pre  - the list is sorted or empty
         * @post - add new_item into the BST and return true
         *         else return false if it didn't insert
         * */
        bool insert(T new_item);

        /* remove() - delete item if it is in the tree
         * @param T item [const] - a object of type T
         * @pre  - BST is not empty.
         * @post - deletes the any item that matches the provided key
         *         and returns the number of items deleted
         * */
        int remove(const int objectId);

        /* find() - searches for the key item in the list
         * @param T item [const] - a object of type T
         * @pre  - the key item should be the same data type as the list
         * @post - searches for the key item in the list and 
         *         returns the number of items of that item found
         * */
        int find(const int objectId, T &copy); 
        
        /* findsmallest() - searches for the key item in the list
         * @pre  - BST is not empty and valid 
         * @post - searches for the tree item in the list and 
         *         returns 1 if the smallest item found, and store it in copy
         *         else return 0
         * */
        int findsmallest(T &copy); 

        /* @pre  - none
         * @post - deletes every node in the tree
         * */
        void destroy();
        
        /* get_root() - returns the pointer, root
         * */
        node<T>* get_root();
        
    private:
        node<T>* root;

        int size;
        
        //helper functions:
        node<T>* findmin(node<T>* current);

        void copy_tree(node<T>* tree_ptr, node<T>* &new_ptr);
        
        void write(ostream &os, node<T>* &link);

        bool insert(node<T>* &current, T new_item);

        int remove(node<T>* &current, const int objectId);

        int find(node<T>* &current, const int objectId, T &copy);

        void destroy(node<T>* &current);
};

#include "bst.cpp"
#endif //end of template
