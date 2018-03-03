/******************************************************************************
  Title          : main.cpp
  Author         : Matthew Li
  Created on     : October 24, 2017
  Description    : To process NYC Open Data : Hot Spots
  Purpose        : Using Linked Lists to process NYC HotSpots and to handle
                   commands for the HotspotList
  Modifications  : 

******************************************************************************/
#include "command.h" 
#include "hotspot.h" 
#include "hotspotlist.h"

#include <string>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;


/*******************************************************************************   
                     HAVERSINE FUNCTION PROTOTYPE
*******************************************************************************/
const double R = 6372.8; //radius of the Earth in km
const double TO_RAD = M_PI / 180.0; //conversion of degrees of rads

double haversine(double lat1, double lon1,
                 double lat2, double lon2);
/*******************************************************************************   
                             MAIN PROGRAM
*******************************************************************************/

int main(int argc, char* argv[])
{
    /** Validating the number of command line arguments **/
    if(argc < 3){
        cerr << "Usage: " << argv[0] << "nyc_hotspots.csv hotspot_commands\n"
             << "Must include the two input files in the command arguments!\n";
    }
    
    /* Declaring the hot spot list */
    HotspotList HotList;

    /***** Store nyc_hotspots.csv into HotList *****/
    ifstream datafile;
    datafile.open(argv[1]);
    if(datafile.fail()){
        cerr << "Error: The command line file cannot open: " << argv[1] << endl;
        exit(1);
    }
    string record = "";
    while(getline(datafile, record)){
        Hotspot X (record); //constructor and stores record into object X
        int success = HotList.insert(X);
    }
    datafile.close();

    /***** Read and execute commands in the commands file *****/
    Command C;

    ifstream commands;
    commands.open(argv[2]);
    if(commands.fail()){
        cerr << "Error: The command line file cannot open: " << argv[2] << endl;
        exit(1);
    }

    int count = 0; //use to keep track of the command line

    while(C.get_next(commands)) {
        
        count++;

        string fromfile  = "";
        string tofile    = "";
        double latitude  = 0; 
        double longitude = 0; 
        double distance  = 0;
        bool   result;
        
        /*get and store the arguments!*/
        C.get_args(fromfile, tofile, latitude, longitude, distance, result);
        
        //printing out args
        //cout <<"*************************************************\n";
        //cout <<"fromfile: " << fromfile << endl;
        //cout <<"tofile: " << tofile << endl;
        //cout <<"lat n lon: " << latitude << " : " << longitude << endl;
        //cout <<"distance: " << distance << endl;

        if(!(result)){
            cerr << "Command on line " << count << " returns the bool result == false.\n";
        }
        else if(C.type_of() == write_cmmd){
            //cout << "write_cmmd is read!\n";
            ofstream os;
            os.open(tofile.c_str());
            if(os.fail()){
                cerr << "write_cmmd: ofstream os cannot open: " << tofile << endl;
                exit(1);
            }
            //write the list to ostream 
            HotList.write(os);
            os.close();
        }
        else if(C.type_of() == save_by_id_cmmd){
            //cout << "save_by_id_cmmd is read!\n";
            ifstream is;
            is.open(fromfile.c_str());
            if(is.fail()){
                cerr << "save_by_id_cmmd: ifstream is cannot open: " << fromfile << endl;
                exit(1);
            }
            ofstream os;
            os.open(tofile.c_str());
            if(os.fail()){
                cerr << "save_by_id_cmmd: ofstream os cannot open: " << tofile << endl;
                exit(1);
            }
            
            //read the objectId from ifstream, 
            //and print the Hotspot with matching id in list 
            string id;
            int objectId;
            while(getline(is, id)){
                objectId = atoi(id.c_str());
                Hotspot Temp;
                int success = HotList.retrieve(objectId, Temp);
                if(1 == success){
                    Temp.print(os);
                }
            }
            is.close();
            os.close();
        }

        else if(C.type_of() == insert_cmmd){
            //cout << "insert_cmmd is read!\n";
            ifstream is;
            is.open(fromfile.c_str());
            if(is.fail()){
                cerr << "insert_cmmd: ifstream is cannot open: " << fromfile << endl;
                exit(1);
            }
            string record;
            while(getline(is, record)){
                Hotspot Temp (record);
                HotList.insert(Temp);
            } 
            is.close();
        }

        else if(C.type_of() == delete_by_id_cmmd){
            //cout << "delete_by_id is read!\n";
            ifstream is;
            is.open(fromfile.c_str());
            if(is.fail()){
                cerr << "delete_by_id_cmmd: ifstream is cannot open: " << fromfile << endl;
                exit(1);
            }

            //search through list, and delete hotspot with matching objectId
            string id;
            int objectId;
            while(getline(is, id)){
                objectId = atoi(id.c_str());
                int num = HotList.remove(objectId);
            }

            is.close();
        }

        else if(C.type_of() == save_by_loc_cmmd){
            //cout << "save_by_loc_cmmd is read!\n";
            int    iD    = 0;
            string boro  = "";
            string type  = "";
            string prov  = "";
            string name  = "";
            string loca  = "";
            double lat   = 0;;
            double lon   = 0;
            string ssid  = "";

            ofstream os;
            os.open(tofile.c_str());
            if(os.fail()){
                cerr << "save_by_loc: ofstream is cannot open: " << tofile << endl;
                exit(1);
            }

            node<Hotspot>* current = HotList.get_head();

            while(current != NULL){
                   (current->data).get(iD, boro, type, 
                                       prov, name, loca,
                                       lat, lon, ssid);
                   
                   //compute distance between the two HotSpots
                   double dist = haversine(latitude, longitude,
                                              lat, lon);

                   //if the computed dist <= given distance, print to os
                   if(dist <= distance){
                       os << iD << endl;
                   }

                   current = current->next;
            }

            os.close();
        }//else-if
    
    }//end of while-loop

    commands.close();    
    return 0;
}

/*******************************************************************************   
                             HAVERSINE FUNCTION
*******************************************************************************/
double haversine(double lat1, double lon1,
                 double lat2, double lon2)
{
    lat1 = TO_RAD * lat1;
    lat2 = TO_RAD * lat2;

    double dLat = (lat2-lat1)/2;
    double dLon = (lon2-lon1)/2;

    double a = sin(dLat);
    double b = sin(dLon);

    return 2 * R * asin(sqrt(a*a + cos(lat1) * cos(lat2) * b*b));
};
