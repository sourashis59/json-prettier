
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
