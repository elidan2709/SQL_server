#include "lexical_analyzer.hpp"

enum lex_type_t Lexer::cur_lex_type;
std::string Lexer::cur_lex;
std::string Lexer::input;
std::string::iterator Lexer::p;
char Lexer::c;
int Lexer::flag = 0;

Lexer::LexerException::LexerException() {
    error_message = "lexer: lexical error. try again...";
}

Lexer::LexerException::~ LexerException() {}

void Lexer::LexerException::print_message() {
    std::cout << error_message << std::endl << std::endl;
}

void Lexer::init(std::string s) {
    input = s;
    p = input.begin();
}

void Lexer::get_lex() {
    try {
        cur_lex.clear();
        if(flag == 0) {
            c = *p;
            p++;
        }
        else {
            flag = 0;
        }
        enum state_t {
            H,
            A,
            ALL_,
            AND_,
            CRT,
            D,
            DLT,
            DRP,
            FRM,
            I,
            INSRT,
            INT,
            L,
            LK,
            LNG,
            NT,
            OR_,
            S,
            SLCT,
            ST,
            T,
            TBL,
            TXT,
            UPDT,
            WHR,
            MNS,
            NT_EQL,
            GRTR,
            LSS,
            NMBR,
            IDNT,
            STRNG,
            OK
            } state = H;

        while(state != OK) {
            switch(state) {
            case H:
                if ((std::isspace(c)) && (c != 0)) {
                }
                else if(c == 'A') {
                    state = A;
                }
                else if(c == 'C') {
                    state = CRT;
                }
                else if(c == 'D') {
                    state = D;
                }
                else if(c == 'F') {
                    state = FRM;
                }
                else if(c == 'I') {
                    state = I;
                }
                else if(c == 'L') {
                    state = L;
                }
                else if(c == 'N') {
                    state = NT;
                }
                else if(c == 'O') {
                    state = OR_;
                }
                else if(c == 'S') {
                    state = S;
                }
                else if(c == 'T') {
                    state = T;
                }
                else if(c == 'U') {
                    state = UPDT;
                }
                else if(c == 'W') {
                    state = WHR;
                }
                else if(c == '+') {
                    cur_lex = "+";
                    cur_lex_type = PLUS;
                    state = OK;
                }
                else if(c == '-') {
                    state = MNS;
                }
                else if(c == '*') {
                    cur_lex = "*";
                    cur_lex_type = MULT;
                    state = OK;
                }
                else if(c == '/') {
                    cur_lex = "/";
                    cur_lex_type = SLASH;
                    state = OK;
                }
                else if(c == '%') {
                    cur_lex = "%";
                    cur_lex_type = PERCENT;
                    state = OK;
                }
                else if(c == '(') {
                    cur_lex = "(";
                    cur_lex_type = ROUND_OPEN;
                    state = OK;
                }
                else if(c == ')') {
                    cur_lex = ")";
                    cur_lex_type = ROUND_CLOSE;
                    state = OK;
                }
                else if(c == ',') {
                    cur_lex = ",";
                    cur_lex_type = COMMA;
                    state = OK;
                }
                else if(c == 39) { // символ ' ' '
                    state = STRNG;
                }
                else if(c == '=') {
                    cur_lex = "=";
                    cur_lex_type = EQUAL;
                    state = OK;
                }
                else if(c == '!') {
                    state = NT_EQL;
                }
                else if(c == '>') {
                    state = GRTR;
                }
                else if(c == '<') {
                    state = LSS;
                }
                else if(std::isdigit(c)) {
                    state = NMBR;
                }
                else if(std::isalpha(c) || (c == '_')) {
                    state = IDNT;
                }
                else if((c == 0) || (c == EOF)) {
                    cur_lex_type = END;
                    state = OK;
                }
                else {
                    throw LexerException();
                }
                break;

            case A:
                if(c == 'L') {
                    state = ALL_;
                }
                else if(c == 'N') {
                    state = AND_;
                }
                else {
                    state = IDNT;
                }
                break;

            case ALL_:
                if(c != 'L') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                cur_lex_type = ALL;
                state = OK;
                break;
            case AND_:
                if(c != 'D') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                cur_lex_type = AND;
                state = OK;
                break;
            case CRT:
                if(c != 'R') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'E') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if (c != 'A') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'T') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'E') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                cur_lex_type = CREATE;
                state = OK;
                break;
            case D:
                if(c == 'E') {
                    state = DLT;
                }
                else if(c == 'R') {
                    state = DRP;
                }
                else {
                    state = IDNT;
                }
                break;
            case DLT:
                if(c != 'L') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'E') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'T') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'E') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                cur_lex_type = DELETE;
                state = OK;
                break;
            case DRP:
                if(c != 'O') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'P') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                cur_lex_type = DROP;
                state = OK;
                break;
            case FRM:
                if(c != 'R') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'O') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if (c != 'M') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                cur_lex_type = FROM;
                state = OK;
                break;
            case I:
                if(c != 'N') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if (c == 'S') {
                    state = INSRT;
                }
                else if (c == 'T') {
                    state = INT;
                }
                else if (std::isspace(c)) {
                    cur_lex_type = IN;
                    state = OK;
                }
                else {
                    state = IDNT;
                }
                break;
            case INT:
                if(c != 'O') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                cur_lex_type = INTO;
                state = OK;
                break;
            case INSRT:
                if(c != 'E') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'R') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'T') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                cur_lex_type = INSERT;
                state = OK;
                    break;
            case L:
                if(c == 'I') {
                    state = LK;
                }
                else if (c == 'O') {
                    state = LNG;
                }
                else {
                    state = IDNT;
                }
                break;
            case LK:
                if(c != 'K') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'E') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                cur_lex_type = LIKE;
                state = OK;
                break;
            case LNG:
                if(c != 'N') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'G') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                cur_lex_type = LONG;
                state = OK;
                break;
            case NT:
                if(c != 'O') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'T') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                cur_lex_type = NOT;
                state = OK;
                break;
            case OR_:
                if(c != 'R') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                cur_lex_type = OR;
                state = OK;
                break;
            case S:
                if(c != 'E') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c == 'L') {
                    state = SLCT;
                }
                else if(c == 'T') {
                    state = ST;
                }
                else {
                    state = IDNT;
                }
                break;
            case SLCT:
                if(c != 'E') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'C') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'T') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                cur_lex_type = SELECT;
                state = OK;
                break;
            case ST:
                if(std::isspace(c)) {
                    cur_lex_type = SET;
                    state = OK;
                }
                else {
                    state = IDNT;
                }
                break;
            case T:
                if(c == 'E') {
                    state = TXT;
                }
                else if(c == 'A') {
                    state = TBL;
                }
                else {
                    state = IDNT;
                }
                break;
            case TBL:
                if(c != 'B') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'L') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'E') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                cur_lex_type = TABLE;
                state = OK;
                break;
            case TXT:
                if(c != 'X') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'T') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                cur_lex_type = TEXT;
                state = OK;
                break;
            case UPDT:
                if(c != 'P') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'D') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'A') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'T') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'E') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                cur_lex_type = UPDATE;
                state = OK;
                break;
            case WHR:
                if(c != 'H') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'E') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'R') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                c = *p;
                p++;
                if(c != 'E') {
                    state = IDNT;
                    break;
                }
                cur_lex.push_back(c);
                cur_lex_type = WHERE;
                state = OK;
                break;
            case MNS:
                if(std::isdigit(c)) {
                    state = NMBR;
                }
                else {
                    cur_lex_type = MINUS;
                    flag = 1;
                    state = OK;
                }
                break;
            case NT_EQL:
                if(c != '=') {
                    throw LexerException();
                }
                cur_lex.push_back(c);
                cur_lex_type = NOT_EQUAL;
                state = OK;
                break;
            case GRTR:
                if(c == '=') {
                    cur_lex.push_back(c);
                    cur_lex_type = GREATER_EQUAL;
                    state = OK;
                }
                else {
                    cur_lex_type = GREATER;
                    flag = 1;
                    state = OK;
                }
                break;
            case LSS:
                if(c == '=') {
                    cur_lex.push_back(c);
                    cur_lex_type = LESS_EQUAL;
                    state = OK;
                }
                else {
                    cur_lex_type = LESS;
                    flag = 1;
                    state = OK;
                }
                break;
            case NMBR:
                if(std::isdigit(c)) {
                }
                else if(std::isalpha(c)) {
                    state = IDNT;
                }
                else {
                    flag = 1;
                    cur_lex_type = NUMBER;
                    state = OK;
                }
                break;
            case IDNT:
                if(std::isalpha(c) || std::isdigit(c) || (c == '_')) {
                }
                else {
                    flag = 1;
                    cur_lex_type = IDENT;
                    state = OK;
                }
                break;
            case STRNG:
                if((c != 39) && (c != EOF) && (c != '\n')) { // символ 39 = ' ' '
                }
                else if((c == EOF) || (c == '\n')) {
                    throw LexerException();
                }
                else {
                    cur_lex_type = STRING;
                    state = OK;
                }
                break;
            case OK:
                break;
            }

            if (state != OK) {
                if((state == STRNG) && (c != 39)) {
                    cur_lex.push_back(c);
                }
                else if((state == IDNT) && (c != '_') && (!std::isdigit(c)) && (!std::isalpha(c))) {
                    cur_lex_type = IDENT;
                    state = OK;
                    p--;
                }
                else if(!std::isspace(c) && (cur_lex_type != END) && (c != 39)) { // символ 39 = ' ' '
                    cur_lex.push_back(c);
                }
                c = *p;
                p++;
            }
        }
    }
    catch(...) {
        throw LexerException();
    }
}
