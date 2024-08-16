// #pragma once

#include<vector>
#include<string>

using namespace std;

// Abstract class 
class Object {
protected:
    void add_tabs(int tab_count, string &str) {
        for (int i = 0; i < tab_count; ++i)
            // str += '\t';

            // 4 spaces
            str += "    "; 
    }

public:
    virtual ~Object(){}
    virtual void get_formatted_string(string &res, int indentation_level = 0, bool print_tab_on_first_line = false) = 0;
};



class List: public Object {
    vector<Object*> children;
public:
    List() {}

    virtual void add_element(Object *obj) {
        children.emplace_back(obj);
    }

    virtual void get_formatted_string(string &res, int indentation_level = 0, bool print_tab_on_first_line = false) {
        if (print_tab_on_first_line) {
            add_tabs(indentation_level, res);
        }        
        res += "[\n";
        for (Object *child: children) {
            child->get_formatted_string(res, indentation_level + 1, true);
            res += ",\n";
        }
        // pop the last comma and new line
        res.pop_back();
        res.pop_back();

        res += '\n';
        add_tabs(indentation_level, res);
        res += ']';        
    } 
};



class Pair: public Object {
    string key;
    Object* val;
public:
    Pair(string key, Object *val): key(key), val(val) {}

    virtual void get_formatted_string(string &res, int indentation_level = 0, bool print_tab_on_first_line = false) {
        if (print_tab_on_first_line) {
            add_tabs(indentation_level, res);
        }           
        res += '"' + key + '"';
        res += ": ";
        val->get_formatted_string(res, indentation_level, false);
    } 
};



class Map: public Object {
    vector<Pair> pair_list;
public:
    Map() {}
    virtual void add_element(string key, Object *val) {
        pair_list.emplace_back(Pair(key, val));
    }

    virtual void get_formatted_string(string &res, int indentation_level = 0, bool print_tab_on_first_line = false) {
        if (print_tab_on_first_line) {
            add_tabs(indentation_level, res);
        }           
        res += "{\n";
        for (Pair pair: pair_list) {
            pair.get_formatted_string(res, indentation_level + 1, true);
            res += ",\n";
        }
        // pop the last comma and new line
        res.pop_back();
        res.pop_back();

        res += '\n';
        add_tabs(indentation_level, res);
        res += '}';        
    } 
};




class Integer: public Object {
    string val;
public:
    Integer(string val): val(val) {}
    virtual void get_formatted_string(string &res, int indentation_level = 0, bool print_tab_on_first_line = false) {
        if (print_tab_on_first_line) {
            add_tabs(indentation_level, res);
        }
        res += val;  
    }
};




class String: public Object {
    string val;
public:
    String(const string &val): val(val) {}

    virtual void get_formatted_string(string &res, int indentation_level = 0, bool print_tab_on_first_line = false) {
        if (print_tab_on_first_line) {
            add_tabs(indentation_level, res);
        }
        res += '"';
        res += val;
        res += '"';  
    }
};




class Boolean: public Object {
    string val;
public:
    Boolean(string val): val(val) {}

    virtual void get_formatted_string(string &res, int indentation_level = 0, bool print_tab_on_first_line = false) {
        if (print_tab_on_first_line) {
            add_tabs(indentation_level, res);
        }
        res += val;  
    }
};




class Null: public Object {
public:
    Null() {}

    virtual void get_formatted_string(string &res, int indentation_level = 0, bool print_tab_on_first_line = false) {
        if (print_tab_on_first_line) {
            add_tabs(indentation_level, res);
        }
        res += "null";  
    }
};

