/******************************************************************************
  Title          : HotspotList.cpp
  Author         : Matthew Li
  Created on     : October 22, 2017
  Description    : Implementation for the Hotspot List class
  Purpose        : The List class represents a list hotspot objects
  Modifications  : 

******************************************************************************/
#include "command.h" //need to import the "exported types"
#include "hotspotlist.h" 

#include <iostream>

using namespace std;

/*******************************************************************************   
                       HotspotList CLASS IMPLEMENTATION
*******************************************************************************/
//Default Constructor
HotspotList::HotspotList()
{/*cout << "HotspotList Object Created!\n";*/};

//Copy Constructor
HotspotList::HotspotList(const HotspotList &list)
{ 
    hotspotlist = list.hotspotlist; //copies the list over
};

//write to ostream
int HotspotList::write(ostream &s)
{
    hotspotlist.write(s);
};

//insert object to sortedlist
int HotspotList::insert(const Hotspot &object)
{
    if(hotspotlist.insert(object)){return 1;}
    else{return 0;}
};

//merge hlist to current list 
int HotspotList::insert(const HotspotList &hlist, bool isSorted)
{
    int count = 0;
    bool success;

    HotspotList templist(hlist);    //copies hlist to templist 

    link a = hotspotlist.get_head();//a is the head to currentlist
    link b = templist.get_head();   //b is the head to list getting merge

    link temp_ptr;    
    link current = a; //current is the head of list a
    link previous;

    if(isSorted){
        //while b is not NULL or empty       
        while(b != NULL){
            //if a is empty or (b->data < a->data), insert in front of a
            if(a == NULL || b->data < a->data){
                temp_ptr = b->next;
                b->next = a;
                a = b;
                b = temp_ptr;
                count++;
            }

            //if a == b, then node from templist, advance b to next node;
            else if(b->data == a->data){
                temp_ptr = b->next;
                b->next = NULL;
                delete b; //delete node from templist
                b = temp_ptr;
            }

            //if current->data < b->data, advance current and previous ptrs
            else if(current->data < b->data){
                previous = current;
                current = current->next;
            }
            
            //if b->data < current->data, insert at previous
            else{
                temp_ptr = b->next;
                b->next = current;
                previous->next = b;
                previous = previous->next;
                b = temp_ptr;
                count++;
            }
        }//end of while-loop     
    }//end of if

    else if(!(isSorted)){
        link temp = b;    
        while (temp != NULL){
            hotspotlist.insert(temp->data);
            count++;
            temp = temp->next;
        }        
    }
            
            

    return count;
};

int HotspotList::remove(const int objectId)
{
    return hotspotlist.remove(objectId);
};

int HotspotList::size()
{
    return hotspotlist.list_size();
};

int HotspotList::retrieve(const int objectId, Hotspot &object)
{
    return hotspotlist.find(objectId, object);
};

int HotspotList::make_empty()
{
    return hotspotlist.empty_it();   
};

node<Hotspot>* HotspotList::get_head()
{
    return hotspotlist.get_head();
};
