#include<iostream>
#include<fstream>
#include<sstream>
#include "lexer.cpp"
#include "parse_tree_nodes.cpp"

using namespace std;





int main() {
    // ifstream input_file("input.json");
    // if (!input_file) {
    //     std::cerr << "File could not be opened!" << std::endl;
    //     return 1;
    // }

    // stringstream buffer;
    // buffer << input_file.rdbuf();             // Read the entire file into a string stream
    // string input = buffer.str(); // Convert the stream to a string

    // queue<Token> tokens;
    
    // try {
    //     tokens = Lexer(input).tonenize();
    // } catch (const runtime_error error) {
    //     cerr << error.what() << endl; 
    // }

    // while (tokens.size()) {
    //     Token token = tokens.front();
    //     tokens.pop();
    //     cout << token.val << endl;
    // }
    


    List *json = new List(); 
    json->add_element(new Integer("1241"));
    json->add_element(new Integer("11111111111"));
    json->add_element(new String("Hello world"));
    json->add_element(new Boolean("true"));
    json->add_element(new Null());
    
    List *json1 = new List();
    json1->add_element(new Integer("12"));
    json1->add_element(json);
    json1->add_element(new String("Hello world"));
    json1->add_element(json);
    json1->add_element(new Null());

    Map *map = new Map();
    map->add_element("key1", json);
    map->add_element("key212", new Integer("92"));
    map->add_element("key3", json1);


    Map *map1 = new Map();
    map1->add_element("key12", map);
    map1->add_element("keyyyy", json1);


    string res;
    map1->get_formatted_string(res, 0, true);
    cout << res << endl;


    ofstream file("output.json");  
    if (!file) {  
        cerr << "File could not be opened!" << endl;
        return 1;
    }
    file << res;
    file.close();  






    return 0;
}







