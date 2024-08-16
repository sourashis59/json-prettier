#include<vector>
#include<queue>
#include<string>
#include<unordered_map>
#include <stdexcept>
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;


/*
Grammar:
----------------------------------------------

JSON    -> null
        or, Object

Object  ->  Map
            or, List
            or, Integer
            or, String
            or, Boolean
            or, NULL

Integer -> (Digit)+

String -> '"' (Char)* '"'

Boolean -> 'true'
            or, 'false'

Null -> 'null'

Map     ->  '{' PairList '}'

PairList    ->  null
                or, Pair (',' Pair)*

Pair    ->  String ':' Object

List    ->  '[' ValueList ']'

ValueList   ->  null
                or, Object (',' Object)*
*/ 


// class Object {
// public:
//     virtual ~Object(){}
//     virtual string get_formatted_string(int indentation_level = 0) = 0;
// };

// class List: public Object {
//     vector<Object*> children;
// public:
//     List() {}

//     virtual void add_element(Object *obj) {
//         children.emplace_back(obj);
//     }

//     //TODO:
//     virtual string get_formatted_string(int indentation_level = 0) {
//         string res;

//     } 
// };

// class Pair: public Object {
//     string key;
//     Object* val;
// public:
//     Pair(string key, Object *val): key(key), val(val) {}
//     virtual string get_formatted_string() {
//         //TODO:
//     }
// };

// class Map: public Object {
//     vector<Pair> pair_list;
// public:
//     Map() {}
//     virtual void add_element(string key, Object *val) {
//         pair_list.emplace_back(Pair(key, val));
//     }
// };

// class Integer: public Object {
//     string val;
// public:
//     Integer(string val): val(val) {}
// };

// class String: public Object {
//     string val;
// public:
//     String(const string &val): val(val) {}
// };

// class Boolean: public Object {
//     bool val;
// public:
//     Boolean(bool val): val(val) {}
// };

// class Null: public Object {
// public:
//     Null() {}
// };















enum TokenType {
    INTEGER,
    STRING,
    BOOLEAN_TRUE,
    BOOLEAN_FALSE,
    NULL_TYPE,
    OPENING_CURLY_BRACKET,
    CLOSING_CURLY_BRACKET,
    OPENING_SQUARE_BRACKET,
    CLOSING_SQUARE_BRACKET,
    COMMA,
    COLON
};

unordered_map<string, TokenType> symbol_to_token_type = {
    {"{", TokenType::OPENING_CURLY_BRACKET},
    {"}", TokenType::CLOSING_CURLY_BRACKET},
    {"[", TokenType::OPENING_SQUARE_BRACKET},
    {"]", TokenType::OPENING_SQUARE_BRACKET},
    {",", TokenType::COMMA},
    {":", TokenType::COLON},
    {"null", TokenType::NULL_TYPE},
    {"true", TokenType::BOOLEAN_TRUE},
    {"false", TokenType::BOOLEAN_FALSE},
};

class Token {
public:
    TokenType type;
    string val;
    Token(TokenType type, const string &val): type(type), val(val) {}
};


class Lexer {
    string input;
    int pos = 0;
    queue<Token> res;

    bool string_found(const string &target) {
        int i = 0;
        int j = pos;
        while (i < target.size() && j < input.size()) {
            if (target[i] != input[j]) return false;
            ++i, ++j;
        }
        return i == target.size() && j <= input.size();
    }

    string read_number() {
        int start = pos;
        //* loop until we hit a non digit character
        while (pos < input.size() && isdigit(input[pos])) {
            ++pos;
        }
        return input.substr(start, pos - start);
    }

    string read_string() {
        int start = pos;
        ++pos; //* skip first double quote
        //* loop until we hit double quote such that prev character is not '\' 
        while (pos < input.size()) {
            if (input[pos] == '"' && (input[pos - 1] != '\\' || (pos - 2 >= start && input[pos - 2] == '\\'))) {
                ++pos;
                break;
            }
            ++pos;
        }
        return input.substr(start, pos - start);
    }

public:
    Lexer(const string &input): input(input), pos(0) {}
    
    queue<Token> tonenize() {
        if (!res.empty()) return res;

        while (pos < input.size()) {
            string curr = string(1, input[pos]);
            if (curr == " " || curr == "\n") {
                ++pos;
            } else if (symbol_to_token_type.count(curr)) {
                ++pos;
                res.push(Token(symbol_to_token_type[curr], curr));
            } else if (string_found("null")) {
                pos += string("null").size();
                res.push(Token(TokenType::NULL_TYPE, "null"));
            } else if (string_found("true")) {
                pos += string("true").size();
                res.push(Token(TokenType::BOOLEAN_TRUE, "true"));
            } else if (string_found("false")) {
                pos += string("false").size();
                res.push(Token(TokenType::BOOLEAN_FALSE, "false"));
            } else if (curr == "\"") {
                res.push(Token(TokenType::STRING, read_string()));
            } else if (isdigit(curr[0])) {
                res.push(Token(TokenType::INTEGER, read_number()));
            } else {
                throw runtime_error("Syntax error: Invalid char at pos:" + to_string(pos) + "!");
            }
        }
        return res;
    }

};




int main() {
    ifstream input_file("input.json");
    if (!input_file) {
        std::cerr << "File could not be opened!" << std::endl;
        return 1;
    }

    stringstream buffer;
    buffer << input_file.rdbuf();             // Read the entire file into a string stream
    string input = buffer.str(); // Convert the stream to a string

    queue<Token> tokens;
    
    try {
        tokens = Lexer(input).tonenize();
    } catch (const runtime_error error) {
        cerr << error.what() << endl; 
    }

    while (tokens.size()) {
        Token token = tokens.front();
        tokens.pop();
        cout << token.val << endl;
    }

    return true;
}







