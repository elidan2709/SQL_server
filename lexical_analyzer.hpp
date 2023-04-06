#ifndef _LEXICAL_ANALYZER_HPP_
#define _LEXICAL_ANALYZER_HPP_

#include <iostream>
#include "dbms.hpp"

enum lex_type_t { // таблица лексем модельного языка (состояний автомата)
    ALL,
    AND,
    CREATE,
    DELETE,
    DROP,
    FROM,
    IN,
    INSERT,
    INTO,
    LIKE,
    LONG,
    NOT,
    OR,
    SELECT,
    SET,
    TABLE,
    TEXT,
    UPDATE,
    WHERE,
    PLUS,
    MINUS,
    MULT,
    SLASH,
    PERCENT,
    ROUND_OPEN,
    ROUND_CLOSE,
    COMMA,
    EQUAL,
    NOT_EQUAL,
    GREATER,
    LESS,
    GREATER_EQUAL,
    LESS_EQUAL,
    NUMBER,
    STRING,
    IDENT,
    END
    };

namespace Lexer {

    class LexerException { // класс исключений
        std::string error_message; // сообщение об ошибке

    public:
        LexerException(); // конструктор
        ~LexerException(); // деструктор

        void print_message(); // печать сообщения об ошибке
    };

    extern enum lex_type_t cur_lex_type; // тип лексемы
    extern std::string cur_lex; // текущая лексема
    extern std::string input; // вводимая строка
    extern std::string::iterator p; // итератор строки
    extern char c; // текущий символ
    extern int flag; // флаг для считывания (0 если надо читать, -1 если нет)

    void init(std::string s); // инициализация строки
    void get_lex(); // получение лексемы
}

#endif

