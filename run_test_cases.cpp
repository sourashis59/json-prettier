#include<iostream>
#include<fstream>
#include<string>
#include<filesystem>
#include "json_formatter.cpp"

using namespace std;
using namespace filesystem;


string read_file_to_string(const string& file_path) {
    ifstream file(file_path);
    if (!file.is_open())
        throw runtime_error("Could not open file: " + file_path);
    
    return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}


void write_string_to_file(const string& file_path, const string& str) {
    ofstream file(file_path);
    if (!file.is_open()) 
        throw runtime_error("Could not open file: " + file_path);
    
    file << str;
}


int main() {
    path TEST_CASE_DIR_PATH = "test-cases";
    try {
        for (const auto& test_dir : directory_iterator(TEST_CASE_DIR_PATH)) {
            if (!test_dir.is_directory()) 
                continue;
            
            string dir_path = test_dir.path().string();
            string input_file = dir_path + "/input.json";
            string expected_output_file = dir_path + "/expected_output.json";
            string output_file = dir_path + "/output.json";

            string input_json = read_file_to_string(input_file);

            string output_json = JsonFormatter::format(input_json);
            write_string_to_file(output_file, output_json);

            string expected_output_json = read_file_to_string(expected_output_file);

            cout << test_dir.path().filename() << ": " << (output_json == expected_output_json ? "SUCCEEDED" : "FAILED") << endl;
        }
    } catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
    }

    return 0;
}
