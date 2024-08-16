
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


#include "parse_tree_nodes.h"
#include "lexer.cpp"

class Parser {
    queue<Token> q;
    Object *root;

public:
    Parser(const string &input) {
        q = Lexer(input).tonenize();
        root = nullptr;
    }

    Object *parse() {
        if (root != nullptr) return root;
        root = parse_json();
        if (!q.empty())
            throw runtime_error("Trailing characters!");

        return root;
    }

private:
    bool match(TokenType type) {
        return q.size() && q.front().type == type;
    }

    bool token_is_object(Token type) {
        return !match(TokenType::COMMA)
            && !match(TokenType::COLON);
    }


    Object *parse_json() {
        if (q.empty())  return new Null();
        else return parse_object();
    }

    Object *parse_object() {
        Object *x = nullptr;
        if (match(TokenType::OPENING_CURLY_BRACKET)) {
            x = parse_map();
        } else if (match(TokenType::OPENING_SQUARE_BRACKET)) {
            x = parse_list();
        } else if (match(TokenType::INTEGER)) {
            x = new Integer(q.front().val);
            q.pop();
        } else if (match(TokenType::STRING)) {
            x = new String(q.front().val);
            q.pop();
        } else if (match(TokenType::BOOLEAN_FALSE) || match(TokenType::BOOLEAN_TRUE)) {
            x = new Boolean(q.front().val);
            q.pop();
        } else if (match(TokenType::NULL_TYPE)) {
            x = new Null();
            q.pop();
        } else {
            throw runtime_error("Invalid token!");
        }
        return x;
    }

    List *parse_list() {
        if (!match(TokenType::OPENING_SQUARE_BRACKET))
            throw runtime_error("'[' missing for list!");

        //* pop the opening bracket
        q.pop();
        List *x = parse_value_list();
        
        //* pop the closing bracket
        if (!match(TokenType::CLOSING_SQUARE_BRACKET))
            throw runtime_error("Missing ']'!");
        
        q.pop();
        return x;
    }

    List *parse_value_list() {
        List *x = new List();
        while (!q.empty() && !match(TokenType::CLOSING_SQUARE_BRACKET)) {
            x->add_element(parse_object());
            if (!match(TokenType::COMMA))
                break;
            
            //* pop the comma
            q.pop();
        }
        return x;        
    }

    Map *parse_map() {
        if (!match(TokenType::OPENING_CURLY_BRACKET))
            throw runtime_error("'{' missing for map!");

        //* pop the opening bracket
        q.pop();
        Map *x = parse_pair_list();

        //* pop the closing bracket
        if (!match(TokenType::CLOSING_CURLY_BRACKET))
            throw runtime_error("Missing '}'!");
        
        q.pop();
        return x;
    }

    Map *parse_pair_list() {
        Map *x = new Map();
        while (!q.empty() && !match(TokenType::CLOSING_CURLY_BRACKET)) {
            if (!match(TokenType::STRING))
                throw runtime_error("Map key must be string!");

            string key = q.front().val;
            q.pop();

            if (!match(TokenType::COLON))
                throw runtime_error("Colon missing for map key:value pair!");

            //* pop the colon
            q.pop();

            if (!token_is_object(q.front()))
                throw runtime_error("Value missing for map key!");

            Object *val = parse_object();
            x->add_element(key, val);

            if (!match(TokenType::COMMA))
                break;
            
            //* pop comma
            q.pop();
        }
        return x;
    }
};

