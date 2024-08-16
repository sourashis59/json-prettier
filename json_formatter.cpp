#pragma once
#include "parser.cpp"

using namespace std;

class JsonFormatter {
public:
    static string format(const string &input) {
        Object *parse_tree_root = Parser(input).parse();
        string res;
        parse_tree_root->get_formatted_string(res);
        return res;
    }
};