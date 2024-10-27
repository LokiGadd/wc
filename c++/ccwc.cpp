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
#include <sstream>
#include <string>

using namespace std;

auto bytesCounter(const string& inputFileName) {
    filesystem::path filePath = inputFileName;
    try {
        auto fileSize = filesystem::file_size(filePath);
        return fileSize;
    } catch (const filesystem::filesystem_error& e) {
        throw invalid_argument(e.what());
    }
}

int linesCounter(const string& inputFileName) {
    ifstream inputFile(inputFileName);
    if (!inputFile) {
        cerr << "Unable to open file" << endl;
        return -1;
    }
    string s;
    int count = 0;
    while (getline(inputFile, s)) {
        count++;
    }
    inputFile.close();
    return count;
}

int lineCounterStream(istream& inputStream){
    string s;
    int count = 0;
    while (getline(inputStream, s)) {
        count++;
    }
    return count;
}

int wordCounterStream(istream& inputStream){
    string s;
    int count = 0;
    while (getline(inputStream, s)) {
        stringstream ss(s);
        string word;
        while (ss >> word) {
            count++;
        }
    }
    return count;
}

size_t charCounterStream(stringstream& inputStream){
    size_t count = inputStream.str().length();
    return count;
}

int bytesCounterStream(istream& inputStream){
    string buffer;
    buffer.assign(istreambuf_iterator<char>(inputStream), istreambuf_iterator<char>());
    return buffer.size();
}

int wordCounter(const string& inputFileName) {
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
    if (argc == 1) {
        // Read from standard input
        stringstream buffer;
        buffer << cin.rdbuf();
        int lineCount = lineCounterStream(buffer); // Placeholder for stdin handling
        buffer.clear(); // Clear the state of the stringstream
        buffer.seekg(0); 
        int wordCount = wordCounterStream(buffer);
        buffer.clear(); // Clear the state of the stringstream
        buffer.seekg(0);
        size_t bytesCount = bytesCounterStream(buffer);
        cout << lineCount << ' ' << wordCount << ' ' << bytesCount << endl;
    } else if (argc == 2) {
        cout << "Entered argc 2" << endl;
        string flag = argv[1];
        if (flag == "-c"){
            stringstream buffer;
            buffer << cin.rdbuf();
            size_t bytesCount = bytesCounterStream(buffer);
            cout << bytesCount << endl;
        } else if (flag == "-l"){
            stringstream buffer;
            buffer << cin.rdbuf();
            int lineCount = lineCounterStream(buffer);
            cout << lineCount << endl;
        } else if (flag == "-w"){
            stringstream buffer;
            buffer << cin.rdbuf();
            int wordCount = wordCounterStream(buffer);
            cout << wordCount << endl;
        } else if (flag == "-m"){
            stringstream buffer;
            buffer << cin.rdbuf();
            size_t charCount = charCounterStream(buffer);
            cout << charCount << endl;
        } else {
            string inputFileName = flag;
            try {
                auto fileSize = bytesCounter(inputFileName);
                int lineCount = linesCounter(inputFileName);
                int wordCount = wordCounter(inputFileName);
                cout << lineCount << ' ' << wordCount << ' ' << fileSize << ' ' << inputFileName << endl;
            } catch (const invalid_argument& e) {
                cerr << "Error: " << e.what() << endl;
            }
        }
    } else if (argc == 3) {
        string flag = argv[1];
        string inputFileName = argv[2];

        if (flag == "-c") {
            try{
                auto fileSize = bytesCounter(inputFileName);
                if (fileSize != -1) {
                    cout << fileSize << ' ' << inputFileName << endl;
                }
            } catch (const invalid_argument& e) {
                cerr << "Error: " << e.what() << endl;
            }
        } else if (flag == "-l") {
            int count = linesCounter(inputFileName);
            if (count != -1) {
                cout << count << ' ' << inputFileName << endl;
            }
        } else if (flag == "-w") {
            int count = wordCounter(inputFileName);
            if (count != -1) {
                cout << count << ' ' << inputFileName << endl;
            }
        }
    }
    return 0;
}