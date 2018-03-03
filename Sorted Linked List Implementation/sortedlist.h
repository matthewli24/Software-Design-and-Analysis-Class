/******************************************************************************
  Title          : sortedlist.h
  Author         : Matthew Li
  Created on     : October 21, 2017
  Description    : Interface for the Sorted List class template
  Purpose        : The singly SortedList class template 
  Modifications  : 

******************************************************************************/
#ifndef SORTEDLIST_H__
#define SORTEDLIST_H__

#include <fstream>
#include <iostream>

using namespace std;

/*******************************************************************************   
                       SORTEDLIST CLASS TEMPLATE INTERFACE
*******************************************************************************/
/*template for node*/
template <class T>
struct node{
    T data;
    node* next;
};

template<class T>
class SortedList
{
    private:
        node<T>* head;
        int size;

        /* @pre  - prev does not equal NULL
         * @post - prev points to the a new node containing new_item
         *         and the next link of the new node points to what
         *         prev previously pointed to.
         * */
        bool insert_at(node<T>* &prev, T new_item);

        /* write() - starting from head of the list, write data to ostream
         * @pre  - ostream is open for writing
         * @post - write the entire list from the head onto an open ostream 
         * */
        void write(ostream &os, node<T>* link);

    public:
        //Constructor that sets head to NULL and size to 0
        SortedList();

        /* write() - wrapper function
         * @pre  - ostream is open for writing
         * @post - write the entire list onto an open ostream 
         * */
        void write(ostream &os);

        /* @pre  - the list exist
         * @post - returns the size of the list
         * */
        int list_size();

        /* insert() - put new_item into the sortedlist
         * @param T new_item [in] - a object of type T
         * @pre  - the list is sorted or empty
         * @post - add new_item into the sortedlist and return true
         *         else return false if it didn't insert
         * */
        bool insert(T new_item);

        /* remove() - delete item if it is in the list
         * @param T item [const] - a object of type T
         * @pre  - the list is sorted
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

        /* @pre  - none
         * @post - deletes every node in the linked list, set head to null,
         *         and return number of nodes deleted
         * */
        int empty_it();
        
        /* @pre  - none
         * @post - returns the node<T>* head private
         * */
        node<T>* get_head(); 
};

#include "sortedlist.cpp"
#endif //end of template
