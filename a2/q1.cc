#include "q1.h"
#include <iostream>
using namespace std;


unsigned int Station::requests = 0;

//------------Station::Station--------------------------
// Purpose: Constructor
//
// Return:
//-------------------------------------------
Station::Station( unsigned int id) : id(id){}

//------------Station::~Station-------------------
// Purpose: Destructor
//
// Return:
//--------------------------------------------
Station::~Station(){
    if(this->nexthop->id == 0){
        //do nothing
    }
    else{
        delete this->nexthop;
    }
}

//----------------Station::setup--------------------
// Purpose: Setup each station,
//          link the stations as a circle
//
// Return:
//--------------------------------------------------
void Station::setup(Station *nexthop){
    this->nexthop = nexthop;//link the station
}

//----------------Station::data--------------------
// Purpose: The method used to pass frame
//
// Return:
//--------------------------------------------------
void Station::data(Frame frame){
    this->frame = frame;
    resume();
}

//----------------Station::sendreq----------------------
// Purpose: Initialize sending requests for this station
//
// Return:
//-------------------------------------------------------
void Station::sendreq(unsigned int round, unsigned int dst, unsigned int prio){
    //store the round number, destination, and priority
    this->round.push_back(round);
    this->dst.push_back(dst);
    this->prio.push_back(prio);
    this->requests++;
}

//----------------Station::start--------------------
// Purpose: start a frame passing
//
// Return:
//--------------------------------------------------
void Station::start(){
    this->frame.type = Frame::Token;
    this->frame.prio = 0;
    resume();
}

//----------------Station::search_Request--------------------
// Purpose: Try to get a request from this station
//
// Return: index of the request or -1 if not found
//--------------------------------------------------
int Station::search_Request(){
    int index = -1;
    unsigned int min_round = this->num_Round+1;
    for(unsigned int i = 0; i < this->round.size();i++){
        if(this->round[i] <= num_Round){
                if(this->round[i] < min_round){
                    min_round = this->round[i];
                    if(this->prio[i]>=this->frame.prio){
                        index = i;
                    }
                    else{
                        index = -1;
                    }
                }
            else;
        }
    }
    return index;
}

//----------------Station::search_Reserve--------------------
// Purpose: Searching if the request's priority is larger than
//          the priority of current frame
//
// Return: index of the request or -1 if not found
//--------------------------------------------------
int Station::search_Reserve(){
    int index = -1;
    unsigned int min_round = this->num_Round + 1;
    for(unsigned int i = 0; i < this->round.size();i++){
        if(this->round[i] <= num_Round){
            if(this->round[i] < min_round){
                min_round = this->round[i];
                if(this->prio[i] > this->frame.prio){
                    index = i;
                }
                else{
                    index = -1;
                }
            }
            else;
        }
    }
    return index;
}

//----------------Station::main--------------------
// Purpose: execute current coroutine
//
// Return:
//--------------------------------------------------
void Station::main(){
    int reserve_prio = -1;
    int index = -1;
    this->num_Round = 0;
    while(this->requests > 0){
        if(this->id == 0)
            cout<<this->num_Round<<'\t';//print out the number of round
        if(this->frame.type == Frame::Token){
            index = search_Request();//find a request
            if(index > -1){
                //sending data to destination
                this->frame.type = Frame::Data;
                this->frame.src = this->id;
                this->frame.dst = this->dst[index];
                
                if(this->reserve_prio > -1){//if there is a reserved priority in this station
                    this->frame.prio = this->reserve_prio;
                    this->reserve_prio = -1;
                }
                cout<<"p"<<this->frame.prio<<":"<<"d"<<this->frame.src<<","<<this->frame.dst;
                if(this->nexthop->id == 0){
                    cout<<endl;
                }
                else{
                    cout<<'\t';
                }
                //remove the request
                this->round.erase(this->round.begin()+index);
                this->dst.erase(this->dst.begin()+index);
                this->prio.erase(this->prio.begin()+index);
            }
            else{
                cout<<"p"<<this->frame.prio<<":tok";
                if(this->nexthop->id == 0){
                    cout<<endl;
                }
                else{
                    cout<<'\t';
                }
            }
        }
        else{//passing a data or ack frame
            index = search_Reserve();//find a request
            if(this->frame.dst == this->id){
                if(this->frame.type == Frame::Data){
                    this->frame.dst = this->frame.src;
                    this->frame.src = this->id;
                    this->frame.type = Frame::Ack;
                    if(index>-1){
                        //reserve priority
                        this->reserve_prio = this->frame.prio;
                        this->frame.prio = this->prio[index];
                    }
                }
                else{
                    this->frame.dst = this->frame.src;
                    this->frame.src = this->id;
                    this->frame.type = Frame::Token;
                    this->requests--;
                }
            }
            else if(index>-1){
                //reserve priority
                this->reserve_prio = this->frame.prio;
                this->frame.prio = this->prio[index];
            }
            else;
            //print out sending frame
            cout<<"p"<<this->frame.prio<<":";
            if(this->frame.type != Frame::Token){
                if(this->frame.type == Frame::Data){
                    cout<<"d";
                }
                else{
                    cout<<"a";
                }
                cout<<this->frame.src<<","<<this->frame.dst;
            }
            else{
                cout<<"tok";
            }
            if(this->requests == 0){
                cout<<endl;
                break;
            }
            if(this->nexthop->id == 0){
                cout<<endl;
            }
            else{
                cout<<'\t';
            }
        }
        this->nexthop->data(this->frame);
        if(this->requests == 0){
            break;
        }
        this->num_Round++;
    }
}

