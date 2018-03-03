/******************************************************************************
  Title          : sortedlist.cpp
  Author         : Matthew Li
  Created on     : October 22, 2017
  Description    : Implementation for the Sorted List class template
  Purpose        : The singly SortedList class template 
  Modifications  : 

******************************************************************************/
#include <iostream>
#include <fstream>

#include "sortedlist.h"

using namespace std;

/*******************************************************************************   
                     SORTEDLIST CLASS TEMPLATE IMPLEMENTATION
*******************************************************************************/
//Constructor that sets head to NULL and size to 0
template <class T>
SortedList<T>::SortedList()
{
    head = NULL;
    size = 0;
};


template <class T>
//returns size of the list
int SortedList<T>::list_size()
{
    return size;
};

template <class T>
void SortedList<T>::write(ostream &os)
{
    write(os, head);
};

template <class T>
void SortedList<T>::write(ostream &os, node<T>* link)
{
    if(link == NULL){
        cerr << "SortedList<T>::write link == NULL\n";
    }
    
    node<T>* current = link;
    while(current != NULL){
        current->data.print(os);
        current = current->next;
    }
};


template <class T>
bool SortedList<T>::insert_at(node<T>* &prev, T new_item)
{
    node<T>* temp_ptr = new node<T>;

    if(NULL == temp_ptr){
        cerr << "Cannot create temp_ptr in insert_at function\n";
        return false;
    }
    
    temp_ptr->data = new_item;
    temp_ptr->next = prev;
    prev = temp_ptr;

    return true;
};

template <class T>
//inserts new_item to the sorted list
bool SortedList<T>::insert(T new_item)
{
    node<T>* current;
    node<T>* previous;
    bool success;     

    //if list is empty or if new_item smaller than the first
    if(NULL == head || new_item < head->data){
        success = insert_at(head, new_item);
        if(success){
            size++;
        }
        return success;
    }

    //if list is not empty, and first item is not larger than new_item
    //check if the 1st item is equal to new_item
    if(head->data == new_item){ //exit since it is in the list already
        return false;
    }

    //if head->data < new_item, start at the 2nd node<T> if it exists
    previous = head;
    current  = head->next;

    while(current != NULL){
        if (current->data < new_item){ 
            //pointer chasing, advance both ptrs
            previous = current;
            current = current->next;
        }

        else if(new_item < current->data){ 
            //previous points to the item that was smaller and current is bigger
            //so insert new_item after previous
            if(success = insert_at(previous->next, new_item)){
                size++;
            }
            return success;
        }

        else{ //found a dulicate, do not insert
            return false;
        }
    }//end of while-loop

    //if we reach here, the item is bigger than everything in the list
    //and previous points to the last node<T>
    if(success = insert_at(previous->next, new_item)){
        size++;
    }
    return success;
};


template <class T>
//remove item from the sorted list
int SortedList<T>::remove(const int objectId)
{
    node<T>* current;
    node<T>* previous;
    int count = 0;
    
    if(NULL != head){
        //if list is not empty

        current = head;
        previous = NULL;
        while(current != NULL){
            if(current->data < objectId){
                //item is bigger than current, so advance both ptrs
                previous = current;
                current  = current->next;
            }

            else if(objectId < current->data){
                //item is smaller than current item, so item cannot be in list
                break;
            }

            else{ //objectId == current->data
                if(NULL == previous){
                    //if it is the first node in the list
                    head = current->next;
                    current->next = NULL;
                    delete current;
                    current = head;
                    count++;
                }

                else{
                    //not first node, previous can be dereferenced
                    current = current->next;
                    previous->next->next = NULL;
                    delete previous->next;
                    previous->next = current;
                    count++;
                }
            }

        }//end of while-loop
    }

    size = size - count;
    return count;
};


template <class T>
int SortedList<T>::find(const int objectId, T &copy)
{
    node<T>* current;

    //if list is empty
    if(head == NULL){
        return 0;
    }    

    //list is not empty
    current = head;
    while (current != NULL){
       
       if(current->data < objectId){
           //if temp is less than objectId, advance current ptr
           current = current->next;          
       }

       else if(objectId < current->data){
           //item is not in the remainder of the list! 
           return 0;
       }

       else{ //found matching!
           copy = current->data;
           return 1;
       }

    }//end of while-loop
    
    //if it reaches here, it doesnt exist 
    return 0;
}; 

template<class T> 
int SortedList<T>::empty_it()
{
    int count = 0;
    node<T>* current = head;
    //if current == NULL, list is already empty return 0
    if(current == NULL){
        return 0;
    }
    
    while(current != NULL){
        head = current->next;
        current->next = NULL;
        delete current;
        current = head;
        count++;
    }
    
    size = size - count;
    return count;
};

template<class T>
node<T>* SortedList<T>::get_head()
{
    return head;
}; 
