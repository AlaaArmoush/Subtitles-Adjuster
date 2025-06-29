#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <regex>

using namespace std;

int main(int argc, char* argv[]){
    if(argc < 5){
        cerr << "correct usage: subshift -i input.srt -s +/-hh:mm:ss,ms\n"; 
        return 1;
    }

    string inputFile, shiftStr;
    for(int i = 0; i < argc; i++){
        string arg = argv[i];

        if(arg == "-i"){
            
        }

    }




    return 0;
}