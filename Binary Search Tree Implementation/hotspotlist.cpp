/******************************************************************************
  Title          : HotspotList.cpp
  Author         : Matthew Li
  Created on     : October 22, 2017
  Description    : Implementation for the Hotspot List class
  Purpose        : The List class represents a list hotspot objects
  Modifications  : 

******************************************************************************/
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
    hotspotlist = BST<Hotspot>(list.hotspotlist);
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
int HotspotList::insert(const HotspotList &hlist)
{
    int count = 0;

    HotspotList templist(hlist);    //copies hlist to templist 

    node<Hotspot>* b_root = templist.get_root();   //b is the root to list getting merged
    
    while(b_root != NULL){
        Hotspot element;
        templist.findsmallest(element);
        hotspotlist.insert(element);
        count++;
        cout << count << endl;
        templist.remove(element.get_id());
    }
    
    cout << "items merged: " << count << endl;
    return count;
};

//remove item in list given objectId
int HotspotList::remove(const int objectId)
{
    return hotspotlist.remove(objectId);
};

//returns the number of nodes in the tree
int HotspotList::size()
{
    return hotspotlist.tree_size();
};

//find object and store into another
int HotspotList::find(const int objectId, Hotspot &object)
{
    return hotspotlist.find(objectId, object);
};

//find the smallest node
int HotspotList::findsmallest(Hotspot &object)
{
   return hotspotlist.findsmallest(object); 
};

//make the entire tree/list empty
void HotspotList::make_empty()
{
    hotspotlist.destroy();   
};

//return root of the tree
node<Hotspot>* HotspotList::get_root()
{
    return hotspotlist.get_root();
};

//destroy tree
HotspotList::~HotspotList()
{
    hotspotlist.destroy();
};
