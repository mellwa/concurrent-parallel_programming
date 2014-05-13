#include "q3quicksort.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <uC++.h>
using namespace std;

//---------------check_Flag------------------------
// Purpose: check if the string is a valid flag to
//          set the depth
//
// Return: Integer
//-------------------------------------------------
int check_Flag(string str){
    int d;
    if(str[0] != '-')//check if the first char is a dash
        return -1;
    for(unsigned int i=1;i < str.length();i++){
        if(!isdigit(str[i])){//the rest should be valid numbers
            return -1;
        }
    }
    string depth = str.substr(1,str.length()-1);
    istringstream(depth) >> d;
    return d;
}

//------------------uMain::main---------------------------
// Purpose: drives program.
//
// Return: nothing
//---------------------------------------------------------
void uMain::main(){
    ifstream ifs;
    int depth = 0;//initialize depth
    int mode = 0;
    switch (argc) {
        case 3:
            depth = check_Flag(argv[2]);//check if the second argument passed into main is valid
            if(depth > -1){//depth > -1 means the flag is valid
                mode = 1;
            }
            else{
                cerr<<"Usage: "<<argv[0]<<" unsorted-file [ sorted-file | -depth (>= 0) ]"<<endl;
            return;
            }
        case 2:
            try{
                ifs.open(argv[1],ifstream::in);//open the input file
                break;
            }
            catch(...){//handle the open fail event
                cerr<<"Error! Could not open unsorted input file \""<<argv[1]<<"\""<<endl;
            }
        default:
            cerr<<"Usage: "<<argv[0]<<" unsorted-file [ sorted-file | -depth (>= 0) ]"<<endl;
            return;
    }

    uProcessor p[ (1 << depth) - 1 ] __attribute__(( unused )); // 2^depth-1 kernel threads
    
    int x;
    TYPE n;
    
    if(mode == 1){//go to the second mode to sort an array of descending order numbers
        ifs>>x;//read the number of numbers
        TYPE *values = new TYPE[x];
        for(int i=0; i < x; i++){
            values[i] = x-i;
        }
        {Quicksort<TYPE> quicksort(values, 0, x-1, depth);}//doing quick sort
        delete[] values;
        return;
    }
    
    //the first mode
    while(ifs>>x){
        if(x < 1){
            cout<<endl;
            cout<<endl;
            cout<<endl;
            continue;
        }
        TYPE *values = new TYPE[x];
        for(int i = 0; i < x; i++){
            if(ifs>>n){
                values[i] = n;
                if((i>0) &&(i % 25 == 0)){
                    cout<<endl;
                    cout<<"  ";
                }
                cout<<n<<" ";
            }
            else{
                break;
            }
        }
        cout<<endl;
        {Quicksort<TYPE> quicksort(values, 0, x-1, depth);}
        for(int j=0; j < x; j++){
            if((j>0) &&(j % 25 == 0)){//start a newline with 2 spaces after pringting 25 values
                cout<<endl;
                cout<<"  ";
            }
            cout<<values[j]<<" ";
        }
        cout<<endl;
        cout<<endl;//end each set of output with a blank line
        delete[] values;
    }
    return;
}