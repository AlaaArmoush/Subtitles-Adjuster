#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <regex>
#include <chrono>

using namespace std;

int parseShift(const string& shiftStr);
int timeToMs(const string& timeStr);
string msToTimeStr(int totalMs);

int main(int argc, char* argv[]){
    if(argc < 5){
        cerr << "correct usage: subshift -i input.srt -s +/-hh:mm:ss,ms\n"; 
        return 1;
    }

    string inputFile, shiftStr;

    for(int i = 1; i < argc; i++){
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

    ifstream input(inputFile);
    if(!input){
        inputFile += ".srt";
        input.open(inputFile);
        if (!input) {
            cerr << "Error: Cannot open file '" << inputFile << "'\n";
            return 1;
        }
    }

    string outputFile;
    size_t dotPos = inputFile.rfind('.');
    if(dotPos == string::npos){
        outputFile = inputFile + "_adjusted.srt";
    } else{
        outputFile = inputFile.substr(0, dotPos) + "_adjusted.srt"; 
    }
    ofstream output(outputFile);

    cout << "Shifting subtitles by " << shiftStr << ".....\n";
    string line;
    int i = 1;
    regex indexRegex("[0-9]+");
    while(getline(input, line)){
        if(regex_match(line, indexRegex)){
            output << i++ << "\n";
        }else if(line.find("-->") != string::npos){
            size_t arrowPos = line.find(" --> "); 
            string start = line.substr(0, arrowPos);
            string end = line.substr(arrowPos + 5);

            int startMs = timeToMs(start) + shiftMs;
            int endMs = timeToMs(end) + shiftMs;
            
            output << msToTimeStr(startMs) << " --> " << msToTimeStr(endMs) << "\n";
        } else {
            output << line << "\n";
        }
    }

    input.close();
    output.close();

    cout << "Subtitles shifted, and saved to: " << outputFile << "\n";
    return 0;
}

int parseShift(const string& shiftStr){
    regex rgx(R"(([+-]?)(\d{2}):(\d{2}):(\d{2}),(\d{3}))");
    smatch match;
    if(!regex_match(shiftStr, match, rgx)){
        cerr << "Invalid shift format, use Use +/-hh:mm:ss,ms\n";
        exit(1);
    }

    int sign = (match[1] == "-") ? -1 : 1;
    int h = stoi(match[2]);
    int m = stoi(match[3]);
    int s = stoi(match[4]);
    int ms = stoi(match[5]);

    using namespace std::chrono;
    auto duration = hours(h) + minutes(m) + seconds(s) + milliseconds(ms);
    
    return duration_cast<milliseconds>(duration).count() * sign; 
}

int timeToMs(const string& timeStr){
    int h, m, s, ms;
    char sep;
    sscanf(timeStr.c_str(), "%d:%d:%d%c%d", &h, &m, &s, &sep, &ms);
    return ((h * 3600 + m * 60 + s) * 1000 + ms);
}

string msToTimeStr(int totalMs){
    if(totalMs < 0) totalMs = 0;
    int h = totalMs / (3600000);
    int m = (totalMs %  3600000) / 60000;
    int s = (totalMs % 60000) / 1000;
    int ms = totalMs % 1000;
    
    char newStamp[20];
    sprintf(newStamp, "%02d:%02d:%02d,%03d", h, m, s, ms);
    return newStamp;
}

