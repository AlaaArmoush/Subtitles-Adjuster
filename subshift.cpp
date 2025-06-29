#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <regex>
#include <chrono>

using namespace std;

int parseShift(const string& shiftStr);
int timeToMs(const string& timeStr);
int msToTimeStr(int totalMs);

int main(int argc, char* argv[]){
    if(argc < 5){
        cerr << "correct usage: subshift -i input.srt -s +/-hh:mm:ss,ms\n"; 
        return 1;
    }

    string inputFile, shiftStr;
    for(int i = 0; i < argc; i++){
        if(argv[i] == "-i"){
            inputFile = argv[i+1];
        }
        else if(argv[i] == "-s"){
            shiftStr = argv[i + 1];
        }
        else{
            cerr << "Unknown argument: " << argv[i] << "\n";
            return 1;
        }
    }

    int shiftMs = parseShift(shiftStr);

    

    return 0;
}

int parseShift(const string& shiftStr){
    regex rgx(R"(([+-]?)(\d{2}):(\d{2}):(\d{2}),(\d{3}))");
    smatch match;
    if(!regex_match(shiftStr, match, rgx)){
        cerr << "Invalid shift format, use Use +/-hh:mm:ss,ms\n";
        exit(1);
    }

    int sign = (match[1] == "+") ? 1 : -1;
    int h = stoi(match[2]);
    int m = stoi(match[3]);
    int s = stoi(match[4]);
    int ms = stoi(match[5]);

    using namespace std::chrono;
    auto duration = hours(h) + minutes(m) + seconds(s) + milliseconds(ms);
    
    return duration_cast<milliseconds>(duration).count() * sign; 
}