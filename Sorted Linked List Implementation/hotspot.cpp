/******************************************************************************
  Title          : hotspot.cpp
  Author         : Matthew Li
  Created on     : October 21, 2017
  Description    : Implementation for the Hotspot class
  Purpose        : The Hotspot class represents a hotspot object
  Modifications  : 

******************************************************************************/
#include "hotspot.h"

#include <vector>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>

using namespace std;

/*******************************************************************************   
                         HOTSPOT CLASS IMPLEMENTATION
*******************************************************************************/
//Default constructor; fills fields with zero or null strings
Hotspot::Hotspot()
{
    objectId = 0; 
    boro     = "";
    type     = "";
    provider = "";
    name     = "";
    location = "";
    latitude = 0;
    longitude= 0;
    ssid     = "";

};

//Constructor that creates Hotspot object from a hotspot file text file
Hotspot::Hotspot(const string record)
{
    vector<string> fields;
    string_parser(record, fields);
/*
    //prints vector fields
    for(int i = 0; i<fields.size(); i++){
        cout << i << ": "<< fields[i] << endl;
    }
*/    
    /*Take strings in fields and assign it to private members*/
    if (9 != fields.size()){
        cerr << "Usage: Hotspot(const string record): "
             << "this record in the Hotspot data does not have 9 fields\n";
    }

    else if( 9 == fields.size()){
        objectId = atoi(fields[0].c_str());
        //cout << "objectId: " << objectId << endl;

        boro = fields[1];
        //cout << "boro: " << boro << endl;

        type = fields[2];
        //cout << "type: " << type << endl;
        
        provider = fields[3];
        //cout << "provider: " << provider << endl;

        name = fields[4];
        //cout << "name: " << name << endl;

        location = fields[5];
        //cout << "location: " << location << endl;
        
        latitude = strtod(fields[6].c_str(), NULL);
        //cout << "latitude: " << latitude << endl;

        longitude = strtod(fields[7].c_str(), NULL);
        //cout << "longitude: " << longitude << endl;

        ssid = fields[8];
        //cout << "ssid: " << ssid << endl;
        
    }//end of else-if
};

//Copy constructor
Hotspot::Hotspot(const Hotspot &object)
{
    objectId  =  object.objectId;  
    boro      =  object.boro;     
    type      =  object.type;     
    provider  =  object.provider; 
    name      =  object.name;    
    location  =  object.location; 
    latitude  =  object.latitude; 
    longitude =  object.longitude;
    ssid      =  object.ssid;    
};

//Constructor to create a Hotspot object from nine separate data values
Hotspot::Hotspot(int    theobjectId, 
                 string theboro,
                 string thetype,
                 string theprovider,
                 string thename,
                 string thelocation,
                 double thelatitude,
                 double thelongitude,
                 string thessid)
{
    objectId  =  theobjectId;  
    boro      =  theboro;     
    type      =  thetype;     
    provider  =  theprovider; 
    name      =  thename;    
    location  =  thelocation; 
    latitude  =  thelatitude; 
    longitude =  thelongitude;
    ssid      =  thessid;    
};

//Sets all the nine data members
void Hotspot::set(int    theobjectId, 
                  string theboro,
                  string thetype,
                  string theprovider,
                  string thename,
                  string thelocation,
                  double thelatitude,
                  double thelongitude,
                  string thessid)
{
    objectId  =  theobjectId;  
    boro      =  theboro;     
    type      =  thetype;     
    provider  =  theprovider; 
    name      =  thename;    
    location  =  thelocation; 
    latitude  =  thelatitude; 
    longitude =  thelongitude;
    ssid      =  thessid;    
};
//Gets all nine data members
void Hotspot::get(int    &aobjectId, 
                  string &aboro,
                  string &atype,
                  string &aprovider,
                  string &aname,
                  string &alocation,
                  double &alatitude,
                  double &alongitude,
                  string &assid)
{
    aobjectId  =  objectId;  
    aboro      =  boro;     
    atype      =  type;     
    aprovider  =  provider; 
    aname      =  name;    
    alocation  =  location; 
    alatitude  =  latitude; 
    alongitude =  longitude;
    assid      =  ssid;    
};  

//print() - prints the hotspot data onto a given stream 
void Hotspot::print(ostream &s)
{
    s << objectId << ',' << boro << ',' << type << ','     
      << provider << ',' << name << ',' << '"'  
      << location << '"' <<  ',' << latitude << ','
      << longitude<< ',' << ssid << endl; 
};

//parses and stores fields in vector
void Hotspot::string_parser(const string record, vector<string> &vec)
{
    int length = record.length();

    //format of record <objId,boro,type,provider,name,"location",lat,long,ssid>

    for(int i=0; i<length; ++i){ //iterates through entire record
        string field = "";

        if(record[i] == '"'){
            bool done = true;
            while(i<length && done){
                if(record[i] == '"' && record[i+1] == ','){
                    field = field + record[i];
                    done = false;
                    i--;
                }

                else{
                    field = field +record[i];
                }

                i++;
            }//end of while-loop

            vec.push_back(field);
        } 
        
        else if(i<length && record[i] == ',' && record[i+1] == ','){
            field = "";
            vec.push_back(field);
        }

        else if(i<length && record[i] == ',' && record[i+1] == ' '){
            cerr << "Error on a record: whitespace between fields in the record.\n";
        }

        else if(record[i] != ','){
            for(i; i<length && record[i] != ','; ++i){
                field = field + record[i];
            }
            vec.push_back(field);
            i--;
        }
    }//outmost for-loop
};
/*******************************************************************************   
                         FRIEND OPERATORS DEFINITIONS
*******************************************************************************/
//bool operator< (lt, rt) is true if and only if: lt.ObjectId<rt.ObjectId
bool operator< (const Hotspot &lt, const Hotspot &rt)
{
    if(lt.objectId < rt.objectId){return true;}
    else{return false;}
};

//bool operator== (lt, rt) is true if and only if: lt.ObjectId==rt.ObjectId
bool operator== (const Hotspot &lt, const Hotspot &rt)
{
    if(lt.objectId == rt.objectId){return true;}
    else{return false;}
};

bool operator< (const int &objectId, const Hotspot &item)
{
    if(objectId < item.objectId){return true;}
    else{return false;}
};

bool operator< (const Hotspot &item, const int &objectId)
{
    if(item.objectId < objectId){return true;}
    else{return false;}
};
bool operator== (const int &objectId, const Hotspot &item) 
{
    if(objectId == item.objectId){return true;}
    else{return false;}
};
