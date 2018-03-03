/******************************************************************************
  Title          : hotspotlist.h
  Author         : Matthew Li
  Created on     : October 21, 2017
  Description    : Interface for the Hotspot List class
  Purpose        : The List class represents a list hotspot objects
  Modifications  : 

******************************************************************************/
#ifndef HOTSPOTLIST_H__
#define HOTSPOTLIST_H__

#include "command.h" //need to import the "exported types"
#include "hotspot.h" 
#include "sortedlist.h"

#include <iostream>

using namespace std;

/*******************************************************************************   
                           HOTSPOTLIST CLASS INTERFACE
*******************************************************************************/
typedef node<Hotspot>* link;

class HotspotList
{
    public:
        //Default Constructor
        HotspotList();

        //Copy Constructor- copies hotspotlist member to object created
        HotspotList(const HotspotList &list);

        /* write() - write the hotspot list to ostream in current order 
         *           and return the number of records written.
         * @param ostream &s [inout] - out stream open for writing
         * @pre  - ostream is open for writing and the hotspot list has data
         * @post - write the hotspot list to ostream and return the number
         *         of records writting
         * */
        int write(ostream &s);

        /* insert() - add a single record to the hotspot list
         * @param Hotspot &object - a valid Hotspot object with valid data
         * @pre  - assume we have a valid sorted hotspotlist object
         * @post - insert the given Hotspot object/record into the list and
         *         return 1 if successful and 0 if it is not.
         * */
        int insert(const Hotspot &object);

        /*  insert() - add a sorted hlist into the existing sorted hotspot list
         *  @param HotspotList &hlist [const] - a sorted list of hopspot objects
         *  @param bool isSorted [in]- a boolean argument to see if list is sorted
         *  @pre  - assume hlist is sorted and isSorted is true, else do not merge
         *  @post - merge the hlist to existing sortedlist and return the number
         *          of records successfully inserted into the list
         * */
        int insert(const HotspotList &hlist, bool isSorted);

        /* remove() - deletes a record from the sortedlist given its ObjectId
         * @param int ObjectId [in]- a object id for a WiFi hotspot
         * @pre  - assume the list is sorted and object id is valid
         * @post - if the object exist with the corresponding object id, remove
         *         the object from the list and return the number of records deleted
         * */
        int remove(const int objectId);
        
        /* size() - the size of the hotspotlist
         * @pre   - assume the hotspotlist exist
         * @post  - returns the size of the hotspotlist
         * */
        int size();

        /* retrieve() - searches the hotspot list for the record that matches the ObjectId
         * @param int ObjectId [in] - a object id for a WiFi hotspot
         * @param Hotspot &object [inout] - a valid Hotspot object
         * @pre  - assume a valid hotspotlist exist
         * @post - copy the matching record of the given ObjectId to Hotspot object, which 
         *         is passed by reference and return 1. return 0 if it did not copy over.
         * */
        int retrieve(int ObjectId, Hotspot &object);
        
        /* @pre  - assume a hotspotlist exist
         * @post - deletes all records in the hotspotlist 
         *         and returns the number of records deleted
         * */
        int make_empty();
       
        /* @pre  - assume it has a valid SortedList<Hotspot>
         * @post - returns the head of the sortedlist
         * */
        node<Hotspot>* get_head();

    private:
        SortedList<Hotspot> hotspotlist;
};

#endif //end of HOTSPOTLIST_H
