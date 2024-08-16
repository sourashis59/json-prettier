#include<iostream>
#include<fstream>
#include<sstream>
#include "json_formatter.cpp"

using namespace std;


int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Please provide input and output file paths!" << endl;
        return 1;
    }
    string input_filename = argv[1];
    string output_filename = argv[2];

    ifstream input_file(input_filename);
    if (!input_file) {
        std::cerr << "File could not be opened!" << std::endl;
        return 1;
    }

    stringstream buffer;
    buffer << input_file.rdbuf();             
    string input = buffer.str(); 

    string res = JsonFormatter::format(input);


    ofstream file(output_filename);  
    if (!file) {  
        cerr << "File could not be opened!" << endl;
        return 1;
    }
    file << res;
    file.close();  

    return 0;
}







