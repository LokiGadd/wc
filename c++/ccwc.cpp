/**
 * This code is written by Lokesh Gaddam on 26th October 2024.
 * 
 * Email: lokesh.gaddam@hotmail.com
 * GitHub: https://github.com/LokiGadd
 * 
 * */

#include <iostream>
#include <fstream>
#include <filesystem>
using namespace std;

auto bytesCounter(string inputFileName){
    filesystem::path filePath = inputFileName;
    try {
        auto fileSize = filesystem::file_size(filePath);
        return fileSize;
    } catch (const filesystem::filesystem_error& e) {
        throw invalid_argument(e.what());
    }
}

int linesCounter(string inputFileName){
    ifstream inputFile(inputFileName);
    if (!inputFile) {
        cerr << "Unable to open file" << endl;
        return -1;
    }
    string s;
    int count = 0;

    while (getline(inputFile, s)){
        count++;
    }
    return count;
}

int wordCounter(string inputFileName){
    ifstream inputFile(inputFileName);
    if (!inputFile) {
        cerr << "Unable to open file" << endl;
        return -1;
    }
    
    string s;
    int count = 0;

    while (getline(inputFile, s)) {
        stringstream ss(s);
        string word;
        
        while (ss >> word) {
            count++;
        }
    }
    return count;
}

int main(int argc, char* argv[]) {
    if (argc == 1){
        cout << "No argument provided." << endl;
    }
    if (argc == 2) {
        string inputFileName = argv[1];
        try{
            auto fileSize = bytesCounter(inputFileName);
            int lineCount = linesCounter(inputFileName);
            int wordCount = wordCounter(inputFileName);
            if ((lineCount != -1)&&(wordCount != -1)){
                cout << lineCount << ' ' << wordCount << ' ' << fileSize << ' ' << inputFileName << endl;
            } else {
                throw invalid_argument("File not present");
            }
        } catch (const invalid_argument& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
    if (argc == 3) {
        string flag = argv[1];
        string inputFileName = argv[2];
        if (flag == "-c"){
            try{
                auto fileSize = bytesCounter(inputFileName);
                cout << fileSize << ' ' << inputFileName << endl;
            } catch (const invalid_argument& e) {
                cerr << "Error: " << e.what() << endl;
            }
        } else if (flag == "-l"){
            int count = linesCounter(inputFileName);
            if (count != -1){
                cout << count << ' ' << inputFileName << endl;
            }
        } else if (flag == "-w"){
            int count = wordCounter(inputFileName);
            if (count != -1){
                cout << count << ' ' << inputFileName << endl;
            }
        }
    }
    return 0;
}