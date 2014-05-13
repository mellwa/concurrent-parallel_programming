//-----------------------------------------------------
// checking the string grammar to determine whether the
// input string is a valid floating constant or not
//-----------------------------------------------------
#include <iostream>
#include <fstream>                     //define file stream ifstream
using namespace std;

_Coroutine FloatConstant {
public:
    enum Status { CONT, MATCH, ERROR };         // possible status
private:
    enum Categary{ SIGN,DIGIT,DOT,EXP_SIGN,FLOATING_SUFFIX,UNDEFINED };
    Status status;                              // current status of match
    char ch;                                    // character passed by cocaller
    unsigned int nonexpo_num;                   //count the number of non exponent numbers
    unsigned int expo_num;                      //count the number of exponent numbers
    
    //-----------------------------------------------------
    //check the type of input character
    //-----------------------------------------------------
    Categary categary(){
        if(ch<='9'&&ch>='0'){//the digit numbers
            return DIGIT;
        }
        else if(ch == '.'){
            return DOT;
        }
        else if(ch == '+' || ch=='-'){
            return SIGN;
        }
        else if(ch == 'e' || ch == 'E'){
            return EXP_SIGN;
        }
        else if(ch == 'f' || ch == 'F' || ch == 'l' || ch == 'L'){
            return FLOATING_SUFFIX;
        }
        else{
            return UNDEFINED;//any type not included in categary function
        }
    }//categary
    
    //-----------------------------------------------------
    //the main function in coroutine to check the grammar
    //-----------------------------------------------------
    void main(){
        nonexpo_num = 0;
        expo_num = 0;
        status = CONT;
        //the input char is a sign
        if(categary() == SIGN){
            status = CONT;
            suspend();
        }
        //input char is a digit
        while(categary() == DIGIT){
            nonexpo_num++;
            if(nonexpo_num>16){
                status = ERROR;//the non exponent digits cannot more than 16 digits
            }
            else{
                status = CONT;
            }
            suspend();
        }
        //now it's in the first valid format
        if(categary()==DOT){
            //fractional constant
            if(nonexpo_num>0){
                status = MATCH;
            }
            suspend();
            //digit
            while(categary() == DIGIT){
                nonexpo_num++;
                if(nonexpo_num>16){
                    status = ERROR;
                }
                else{
                    status = MATCH;
                }
                suspend();
            }
            if(categary() == EXP_SIGN){
                if(nonexpo_num == 0){//a dot cannot followed by a exponent sign directly
                    status = ERROR;
                    suspend();
                }
                //exponent
                status = CONT;
                suspend();
                //digit seq with sign
                if(categary()==SIGN){
                    suspend();
                    while(categary()==DIGIT){
                        expo_num++;
                        if(expo_num>3){//the number of exponent part digits cannot more than 3
                            status = ERROR;
                        }
                        else{
                            status = MATCH;
                        }
                        suspend();
                    }
                    if(categary()==FLOATING_SUFFIX){//end by floating suffix?
                        status = MATCH;
                        suspend();
                        status = ERROR;//after floating suffix, there cannot be any more char
                        suspend();
                    }else{
                        status =ERROR;
                        suspend();
                    }
                }
                else if(categary()==DIGIT){
                    status = MATCH;
                    expo_num++;
                    suspend();
                    while(categary()==DIGIT){
                        expo_num++;
                        if(expo_num>3){
                            status = ERROR;
                        }
                        else{
                            status = MATCH;
                        }
                        suspend();
                    }
                    //end by floating suffix?
                    if(categary()==FLOATING_SUFFIX){
                        status = MATCH;
                        suspend();
                        status = ERROR;
                        suspend();
                    }
                    else{
                        status = ERROR;
                        suspend();
                    }
                }
                else{
                    status = ERROR;
                }
            }
            else if(categary()==FLOATING_SUFFIX){
                if(nonexpo_num == 0){
                    status = ERROR;
                    suspend();
                }
                status = MATCH;
                suspend();
                status = ERROR;
                suspend();
            }
            else{
                status = ERROR;
                suspend();
            }
        }
        else if(categary() == EXP_SIGN && nonexpo_num>0){//digit seq have to follow expo
            //exponent                                   // it's in the second valid format
            suspend();
            //digit seq with sign
            if(categary()==SIGN){
                suspend();
                while(categary()==DIGIT){
                    expo_num++;
                    if(expo_num>3){
                        status = ERROR;
                    }
                    else{
                        status = MATCH;
                    }
                    suspend();
                }
                //end by floating suffix?
                if(categary()==FLOATING_SUFFIX){
                    if(expo_num>0){
                        status = MATCH;
                    }
                    else{//e and E cannot followed by a floating suffix directly
                        status = ERROR;
                    }
                    suspend();
                    status = ERROR;
                    suspend();
                }
                else{
                    status = ERROR;
                    suspend();
                }
            }
            else if(categary()==DIGIT){//only digit seq followed by exponent-part in second
                status = MATCH;
                expo_num++;
                suspend();
                while(categary()==DIGIT){
                    expo_num++;
                    if(expo_num>3){
                        status = ERROR;
                    }
                    else{
                        status = MATCH;
                    }
                    suspend();
                }
                //end by floating suffix?
                if(categary()==FLOATING_SUFFIX){
                    status = MATCH;
                    suspend();
                    status = ERROR;
                    suspend();
                }
                else{
                    status = ERROR;
                    suspend();
                }
            }
            else{
                status = ERROR;
                suspend();
            }
        }
        else{
            status = ERROR;
            suspend();
        }
    }                               // coroutine main

public:
    //-----------------------------------------------------
    //called by uMain to run coroutine
    //-----------------------------------------------------
    Status next( char c ) {
        ch = c;                                 // communication in
        resume();                               // activate
        return status;                          // communication out
    }//FloatConstant::next
};//FloatConstant

//-----------------------------------------------------
// uMain, the main function of this program
//-----------------------------------------------------
void uMain::main(){
    ifstream ifs;
    if(argc > 2){//number of input files is wrong
        cout<<"Usage: "<<argv[0]<<" [infile-file]"<<endl;
        return;
    }
    if(argc > 1){
        try{
            ifs.open(argv[1],ifstream::in);//open the input file
        }
        catch(...){//handle the open fail event
            cout<<"Error! Could not open input file \""<<argv[1]<<"\""<<endl;
            return;
        }
    }
    FloatConstant::Status status;
    char c;
    string line;//temp variable to store the string each line
    string defined;
    string undefined;
    while(1){
        status = FloatConstant::CONT;
        FloatConstant floatconstant;
        defined.clear();
        undefined.clear();
        line.clear();
        if(argc == 2){//the input strings from a file
            getline(ifs,line);
            if(ifs.eof())
                break;
        }
        else{// input strings from standard input
            getline(cin,line);
            if(cin.eof())
                break;
        }
        //read line and put char into coroutine
        for(int i = 0; i<line.length();i++){
            c = line[i];
            if(status == FloatConstant::ERROR){
                undefined.push_back(c);//put the extraneous characters into undefined string
                continue;
            }
            status = floatconstant.next(c);//Resume

            defined.push_back(c);
        
        }
        if(line.length()==0){
            cout<<"\"\" : Warning! Blank line."<<endl;
        }
        else if(status == FloatConstant::MATCH){
            cout<<"\""<<line<<"\""<<" : \""<<defined<<"\" yes"<<endl;
        }
        else{
            if(undefined.length()==0)
                cout<<"\""<<line<<"\""<<" : \""<<defined<<"\" no"<<endl;
            else{
                cout<<"\""<<line<<"\""<<" : \""<<defined<<"\" no -- extraneous characters ";
                cout<<"\""<<undefined<<"\""<<endl;
            }
        }
    }
}//uMain:main