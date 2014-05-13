#include "q1.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

//----------------uMain::main--------------------
// Purpose: drives program
//
// Return:
//--------------------------------------------------
void uMain::main(){
    vector< vector<unsigned int> > requests;
    ifstream ifs;
    int x;
    switch (argc) {
        case 2:
            x = atoi(argv[1]);
            if((x > 1) && (x< 101)) break;
            else{
                cerr<<"Usage: "<<argv[0]<<" stations (2..100) [input-file]"<<endl;
                return;
            }
        case 3:
            try{
                ifs.open(argv[2],ifstream::in);//open the input file
                x = atoi(argv[1]);
                if((x > 1) && (x< 101))
                break;
            }
            catch(...){//handle the open fail event
                cerr<<"Error! Could not open output file \""<<argv[2]<<"\""<<endl;
            }
        default:
            cerr<<"Usage: "<<argv[0]<<" stations (2..100) [input-file]"<<endl;
            return;
    }
    
    //read command lines
    unsigned int round;
    unsigned int src;
    unsigned int dst;
    unsigned int prio;
    string line;
    stringstream ss;
    while(1){
        vector<unsigned int> request;
        ss.clear();
        if(argc == 2){
            getline(cin,line);
            if(line.size() == 0) break;
        }
        else{
            getline(ifs,line);
            if(line.size() == 0) break;
        }
        //read input
        ss<<line;
        ss>>round;
        ss>>src;
        ss>>dst;
        ss>>prio;
        
        if((src >= (unsigned int)x) || (dst >= (unsigned int)x) || (src == dst)){
            cout<<"ignoring bad send request: "<<round<<" "<<src<<" "<<dst<<" "<<prio<<endl;
        }
        else{
            request.push_back(round);
            request.push_back(src);
            request.push_back(dst);
            request.push_back(prio);
            requests.push_back(request);
        }
        if(argc == 2){
            if(cin.eof()) break;
        }
        else{
            if(ifs.eof()) break;
        }
    }
    
    //setup stations
    Station *station0;
    Station *pre_station;
    Station *station;
    cout<<"round";
    for(unsigned int i = 0; i < (unsigned int)x; i++){
        station = new Station(i);
        if(i == 0){ station0 = station; }
        else{
            pre_station->setup(station);
        }
        for(unsigned int k = 0; k < requests.size();k++){
            if(requests[k][1] == i){//set sending requests to stations
                station->sendreq(requests[k][0],requests[k][2],requests[k][3]);
            }
        }
        pre_station = station;
        cout<<'\t'<<"s:"<<i;
    }
    pre_station->setup(station0);
    cout<<endl;
    //destroy the requests vector
    for(unsigned int k = 0;k<requests.size();k++){
        requests.erase(requests.begin()+k);
    }
    station0->start();
    delete station0;

}