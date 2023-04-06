#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include <iostream>
#include "dbms.hpp"
#include "lexical_analyzer.hpp"
#include <regex>

namespace Parser {

class ParserException { // класс исключений
    std::string error_message; // сообщение об ошибке

public:
    enum ParserExceptionCode { // код ошибки
        E,
        CREATE_1,
        CREATE_2,
        CREATE_3,
        CREATE_4,
        CREATE_5,
        CREATE_6,
        CREATE_7,
        CREATE_8,
        CREATE_9,
        CREATE_10,
        CREATE_11,
        CREATE_12,
        DROP_1,
        DROP_2,
        DROP_3,
        INSERT_1,
        INSERT_2,
        INSERT_3,
        INSERT_4,
        INSERT_5,
        INSERT_6,
        INSERT_7,
        INSERT_8,
        INSERT_9,
        INSERT_10,
        INSERT_11,
        INSERT_12,
        SELECT_1,
        SELECT_2,
        SELECT_3,
        SELECT_4,
        SELECT_5,
        SELECT_6,
        SELECT_7,
        DELETE_1,
        DELETE_2,
        DELETE_3,
        UPDATE_1,
        UPDATE_2,
        UPDATE_3,
        UPDATE_4,
        UPDATE_5,
        UPDATE_6,
        EXPR_1,
        EXPR_2,
        EXPR_3,
        EXPR_4,
        MLT_1,
        BR_1,
        BR_2,
        BR_3,
        BR_4,
        BR_5,
        WHERE_1,
        WHERE_2,
        WHERE_3,
        WHERE_4,
        WHERE_5,
        WHERE_6,
        WHERE_7,
        WHERE_8,
        WHERE_9,
        WHERE_10,
        WHERE_11,
        EXPR_W_1,
        EXPR_W_2,
        MLT_W_1,
        MLT_W_2,
        BR_W_1,
        BR_W_2,
        BR_W_3,
        BR_W_4,
        BR_W_5,
        BR_W_6,
        BOOL_EXPR_1,
        BOOL_MLT_1,
        BOOL_BR_1,
        BOOL_BR_2,
        BOOL_BR_3,
        BOOL_BR_4,
        BOOL_BR_5
    };

    ParserException(ParserExceptionCode code); // конструктор
    ~ParserException(); // деструктор

    void print_message(); // печать сообщения об ошибке
};

    void init(std::string s);

    void S();
    void CRT();
    void DRP();
    void INSRT();
    void SLCT();
    void UPDT();
    void DLT();
    void EXPR(char* filename, long num, struct DataBase::CellStruct* p);
    void MLT(char* filename, long num, struct DataBase::CellStruct* p);
    void BR_EXPR(char* filename, long num, struct DataBase::CellStruct* p);
    std::vector<long> WHR(char* filename);
    void EXPR_W(char* filename, struct DataBase::CellStruct* p, int& flag);
    void MLT_W(char* filename, struct DataBase::CellStruct* p, int& flag);
    void BR_EXPR_W(char* filename, struct DataBase::CellStruct* p, int& flag);
    void BOOL_EXPR(char* filename, struct DataBase::CellStruct* p, int& flag);
    void BOOL_MLT(char* filename, struct DataBase::CellStruct* p, int& flag);
    void BOOL_BR_EXPR(char* filename, struct DataBase::CellStruct* p, int& flag);

}

#endif
