#include "parser.hpp"

Parser::ParserException::ParserException(ParserExceptionCode code) {
    switch (code) {
        case E:
            error_message = "parser: syntax error. try again...";
            break;
        case CREATE_1:
            error_message = "parser: syntax error. wrong 'CREATE' request: 'TABLE' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case CREATE_2:
            error_message = "parser: syntax error. wrong 'CREATE' request: table name expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case CREATE_3:
            error_message = "parser: syntax error. wrong 'CREATE' request: '(' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case CREATE_4:
            error_message = "parser: syntax error. wrong 'CREATE' request: ',' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case CREATE_5:
            error_message = "parser: syntax error. wrong 'CREATE' request: field name expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case CREATE_6:
            error_message = "parser: syntax error. wrong 'CREATE' request: field name is too long.";
            break;
        case CREATE_7:
            error_message = "parser: syntax error. wrong 'CREATE' request: 'TEXT' or 'LONG' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case CREATE_8:
            error_message = "parser: syntax error. wrong 'CREATE' request: text field length expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case CREATE_9:
            error_message = "parser: syntax error. wrong 'CREATE' request: '(' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case CREATE_10:
            error_message = "parser: syntax error. wrong 'CREATE' request: end of request expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case CREATE_11:
            error_message = "parser: syntax error. wrong 'CREATE' request: table can't contain 0 fields.";
            break;
        case CREATE_12:
            error_message = "parser: syntax error. wrong 'CREATE' request: two identical fields.";
            break;
        case DROP_1:
            error_message = "parser: syntax error. wrong 'DROP' request: 'TABLE' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case DROP_2:
            error_message = "parser: syntax error. wrong 'DROP' request: table name expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case DROP_3:
            error_message = "parser: syntax error. wrong 'DROP' request: end of request expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case INSERT_1:
            error_message = "parser: syntax error. wrong 'INSERT' request: 'INTO' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case INSERT_2:
            error_message = "parser: syntax error. wrong 'INSERT' request: table name expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case INSERT_3:
            error_message = "parser: syntax error. wrong 'INSERT' request: '(' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case INSERT_4:
            error_message = "parser: syntax error. wrong 'INSERT' request: ',' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case INSERT_5:
            error_message = "parser: syntax error. wrong 'INSERT' request: text value expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case INSERT_6:
            error_message = "parser: syntax error. wrong 'INSERT' request: apostrophe expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case INSERT_7:
            error_message = "parser: syntax error. wrong 'INSERT' request: long value expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case INSERT_8:
            error_message = "parser: syntax error. wrong 'INSERT' request: long or text value expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case INSERT_9:
            error_message = "parser: syntax error. wrong 'INSERT' request: end of request expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case INSERT_10:
            error_message = "parser: syntax error. wrong 'INSERT' request: wrong number of fields.";
            break;
        case INSERT_11:
            error_message = "parser: syntax error. wrong 'INSERT' request: wrong value type.";
            break;
        case INSERT_12:
            error_message = "parser: syntax error. wrong 'INSERT' request: unacceptable text value length.";
            break;
        case SELECT_1:
            error_message = "parser: syntax error. wrong 'SELECT' request: field name or '*' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case SELECT_2:
            error_message = "parser: syntax error. wrong 'SELECT' request: field name expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case SELECT_3:
            error_message = "parser: syntax error. wrong 'SELECT' request: 'FROM' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case SELECT_4:
            error_message = "parser: syntax error. wrong 'SELECT' request: table name expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case SELECT_5:
            error_message = "parser: syntax error. wrong 'SELECT' request: wrong field name.";
            break;
        case SELECT_6:
            error_message = "parser: syntax error. wrong 'SELECT' request: two identical fields.";
            break;
        case SELECT_7:
            error_message = "parser: syntax error. wrong 'SELECT' request: 'WHERE' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case DELETE_1:
            error_message = "parser: syntax error. wrong 'DELETE' request: 'FROM' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case DELETE_2:
            error_message = "parser: syntax error. wrong 'DELETE' request: table name expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case DELETE_3:
            error_message = "parser: syntax error. wrong 'DELETE' request: 'WHERE' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case UPDATE_1:
            error_message = "parser: syntax error. wrong 'UPDATE' request: table name expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case UPDATE_2:
            error_message = "parser: syntax error. wrong 'UPDATE' request: 'SET' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case UPDATE_3:
            error_message = "parser: syntax error. wrong 'UPDATE' request: field name expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case UPDATE_4:
            error_message = "parser: syntax error. wrong 'UPDATE' request: no such field in this table.";
            break;
        case UPDATE_5:
            error_message = "parser: syntax error. wrong 'UPDATE' request: '=' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case UPDATE_6:
            error_message = "parser: syntax error. wrong 'UPDATE' request: 'WHERE' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case EXPR_1:
            error_message = "parser: syntax error. wrong expression: no such field in this table.";
            break;
        case EXPR_2:
            error_message = "parser: syntax error. wrong expression: wrong field type.";
            break;
        case EXPR_3:
            error_message = "parser: syntax error. wrong 'expression: too long text field.";
            break;
        case EXPR_4:
            error_message = "parser: syntax error. wrong expression: text or text field name expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case MLT_1:
            error_message = "parser: syntax error. wrong expression: division by zero is unacceptable.";
            break;
        case BR_1:
            error_message = "parser: syntax error. wrong expression: ')' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case BR_2:
            error_message = "parser: syntax error. wrong expression: long number expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case BR_3:
            error_message = "parser: syntax error. wrong expression: no such field in this table.";
            break;
        case BR_4:
            error_message = "parser: syntax error. wrong expression: wrong field type.";
            break;
        case BR_5:
            error_message = "parser: syntax error. wrong expression: '(', long number or field name expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case WHERE_1:
            error_message = "parser: syntax error. wrong 'WHERE' request: end of request expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case WHERE_2:
            error_message = "parser: syntax error. wrong 'WHERE' request: 'IN' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case WHERE_3:
            error_message = "parser: syntax error. wrong 'WHERE' request: '(' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case WHERE_4:
            error_message = "parser: syntax error. wrong 'WHERE' request: text constant expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case WHERE_5:
            error_message = "parser: syntax error. wrong 'WHERE' request: ')' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case WHERE_6:
            error_message = "parser: syntax error. wrong 'WHERE' request: end of request expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case WHERE_7:
            error_message = "parser: syntax error. wrong 'WHERE' request: long constant expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case WHERE_8:
            error_message = "parser: syntax error. wrong 'WHERE' request: long number expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case WHERE_9:
            error_message = "parser: syntax error. wrong 'WHERE' request: 'IN' or 'LIKE' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case WHERE_10:
            error_message = "parser: syntax error. wrong 'WHERE' request: regular expresion expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case WHERE_11:
            error_message = "parser: syntax error. wrong 'WHERE' request: wrong regular expression.";
            break;
        case EXPR_W_1:
            error_message = "parser: syntax error. wrong expression: incompatible types.";
            break;
        case EXPR_W_2:
            error_message = "parser: syntax error. wrong expression: no such field in this table.";
            break;
        case MLT_W_1:
            error_message = "parser: syntax error. wrong expression: incompatible types.";
            break;
        case MLT_W_2:
            error_message = "parser: syntax error. wrong expression: division by zero is unacceptable.";
            break;
        case BR_W_1:
            error_message = "parser: syntax error. wrong expression: incompatible types.";
            break;
        case BR_W_2:
            error_message = "parser: syntax error. wrong expression: ')' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case BR_W_3:
            error_message = "parser: syntax error. wrong expression: long number expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case BR_W_4:
            error_message = "parser: syntax error. wrong expression: no such field in this table.";
            break;
        case BR_W_5:
            error_message = "parser: syntax error. wrong expression: incompatible types.";
            break;
        case BR_W_6:
            error_message = "parser: syntax error. wrong expression: '(', text, long number or field name expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case BOOL_EXPR_1:
            error_message = "parser: syntax error. wrong expression: incompatible types.";
            break;
        case BOOL_MLT_1:
            error_message = "parser: syntax error. wrong expression: incompatible types.";
            break;
        case BOOL_BR_1:
            error_message = "parser: syntax error. wrong bool expression: '(' or 'NOT' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case BOOL_BR_2:
            error_message = "parser: syntax error. wrong bool expression: bool relation expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case BOOL_BR_3:
            error_message = "parser: syntax error. wrong bool expression: ')' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
        case BOOL_BR_4:
            error_message = "parser: syntax error. wrong expression: incompatible types.";
            break;
        case BOOL_BR_5:
            error_message = "parser: syntax error. wrong expression: ')' expected, got '";
            error_message = error_message + Lexer::cur_lex + "'.";
            break;
    }
}

Parser::ParserException::~ParserException() {}

void Parser::ParserException::print_message() {
    std::cout << error_message << std::endl << std::endl;
}

void Parser::init(std::string s) {
    Lexer::init(s);
    Lexer::get_lex();
}

void Parser::S() {
    switch(Lexer::cur_lex_type) {
        case CREATE:
            Lexer::get_lex();
            CRT();
            break;
        case DROP:
            Lexer::get_lex();
            DRP();
            break;
        case SELECT:
            Lexer::get_lex();
            SLCT();
            break;
        case UPDATE:
            Lexer::get_lex();
            UPDT();
            break;
        case DELETE:
            Lexer::get_lex();
            DLT();
            break;
        case INSERT:
            Lexer::get_lex();
            INSRT();
            break;
        default:
            throw ParserException(ParserException::E);
    }
}

void Parser::CRT() {
    DataBase::Table t;
    struct DataBase::TableStruct t_struct;
    char* filename = NULL;
    long sz = sizeof(struct DataBase::FieldStruct);
    t_struct.num_fields = 0;
    t_struct.fields = NULL;

    try {
        if(Lexer::cur_lex_type != TABLE)
            throw ParserException(ParserException::CREATE_1);
        Lexer::get_lex();
        if(Lexer::cur_lex_type != IDENT)
            throw ParserException(ParserException::CREATE_2);
        filename = new char [Lexer::cur_lex.size() + 1];
        strncpy(filename, Lexer::cur_lex.c_str(), Lexer::cur_lex.size() + 1);
        Lexer::get_lex();
        if(Lexer::cur_lex_type != ROUND_OPEN)
            throw ParserException(ParserException::CREATE_3);
        Lexer::get_lex();
        long i = 0, j;
        char* buf;
        while(Lexer::cur_lex_type != ROUND_CLOSE) {
            if((t_struct.num_fields != 0) && (Lexer::cur_lex_type != COMMA)) {
                throw ParserException(ParserException::CREATE_4);
            }
            else if (Lexer::cur_lex_type == COMMA) {
                Lexer::get_lex();
            }
            if(Lexer::cur_lex_type != IDENT)
                throw ParserException(ParserException::CREATE_5);
            t_struct.num_fields++;
            if (Lexer::cur_lex.size() > DataBase::max_name_len)
                throw ParserException(ParserException::CREATE_6);
            t_struct.fields = (struct DataBase::FieldStruct*) realloc(t_struct.fields, sz * t_struct.num_fields);
            buf = new char [Lexer::cur_lex.size() + 1];
            strncpy(buf, Lexer::cur_lex.c_str(), Lexer::cur_lex.size() + 1);
            for(j = 0; j < Lexer::cur_lex.size(); j++)
                t_struct.fields[i].field_name[j] = buf[j];
            t_struct.fields[i].field_name[Lexer::cur_lex.size()] = '\0';
            delete[] buf;

            Lexer::get_lex();

            if((Lexer::cur_lex_type != LONG) && (Lexer::cur_lex_type != TEXT))
                throw ParserException(ParserException::CREATE_7);
            if(Lexer::cur_lex_type == LONG) {
                t_struct.fields[i].type = DataBase::LONG;
            }
            else {
                t_struct.fields[i].type = DataBase::TEXT;
                Lexer::get_lex();
                if(Lexer::cur_lex_type != ROUND_OPEN)
                    throw ParserException(ParserException::CREATE_3);
                Lexer::get_lex();
                if(Lexer::cur_lex_type != NUMBER)
                    throw ParserException(ParserException::CREATE_8);
                try {
                    t_struct.fields[i].len = stol(Lexer::cur_lex);
                }
                catch(...) {
                    throw ParserException(ParserException::CREATE_8);
                }
                Lexer::get_lex();
                if(Lexer::cur_lex_type != ROUND_CLOSE)
                    throw ParserException(ParserException::CREATE_9);
            }
            Lexer::get_lex();
            i++;
        }
        if(i == 0)
            throw ParserException(ParserException::CREATE_11);

        Lexer::get_lex();
        if(Lexer::cur_lex_type != END)
            throw ParserException(ParserException::CREATE_10);

        for(i = 0; i < t_struct.num_fields; i++)
            for(j = i + 1; j < t_struct.num_fields; j++)
                if(strcmp(t_struct.fields[i].field_name, t_struct.fields[j].field_name) == 0)
                    throw ParserException(ParserException::CREATE_12);

        t.create_table(filename, (struct DataBase::TableStruct *)&t_struct);
        t.print_table();
        t.close_table();
        free(t_struct.fields);
        delete[] filename;
    }
    catch(...) {
        if(t_struct.fields != NULL)
            free(t_struct.fields);
        if (filename != NULL)
            delete[] filename;
        t.close_table();
        throw;
    }
}

void Parser::DRP() {
    char* filename = NULL;
    try {
        if (Lexer::cur_lex_type != TABLE)
            throw ParserException(ParserException::DROP_1);
        Lexer::get_lex();
        if(Lexer::cur_lex_type != IDENT)
            throw ParserException(ParserException::DROP_2);
        filename = new char [Lexer::cur_lex.size() + 1];
        strncpy(filename, Lexer::cur_lex.c_str(), Lexer::cur_lex.size() + 1);
        Lexer::get_lex();
        if(Lexer::cur_lex_type != END)
            throw ParserException(ParserException::DROP_3);
        DataBase::Table t;
        t.open_table(filename);
        t.delete_table();
        delete[] filename;
        std::cout << std::endl;
    }
    catch(...) {
        if (filename != NULL)
            delete[] filename;
        throw;
    }
}

void Parser::INSRT() {
    struct DataBase::CellStruct* pcell = NULL;
    char* filename = NULL;
    DataBase::Table t;
    long counter = 0, i;
    try {
        if(Lexer::cur_lex_type != INTO)
            throw ParserException(ParserException::INSERT_1);
        Lexer::get_lex();
        if(Lexer::cur_lex_type != IDENT)
            throw ParserException(ParserException::INSERT_2);
        filename = new char [Lexer::cur_lex.size() + 1];
        strncpy(filename, Lexer::cur_lex.c_str(), Lexer::cur_lex.size() + 1);
        Lexer::get_lex();
        try {
            t.open_table(filename);
        }
        catch(DataBase::DataBaseException e) {
            throw;
        }
        if(Lexer::cur_lex_type != ROUND_OPEN)
            throw ParserException(ParserException::INSERT_3);
        Lexer::get_lex();
        long sz = sizeof(struct DataBase::CellStruct);

        while(Lexer::cur_lex_type != ROUND_CLOSE) {
            if((counter != 0) && (Lexer::cur_lex_type != COMMA)) {
                throw ParserException(ParserException::INSERT_4);
            }
            else if(Lexer::cur_lex_type == COMMA) {
                Lexer::get_lex();
            }
            counter++;
            pcell = (struct DataBase::CellStruct*) realloc(pcell, sz * counter);
            if(Lexer::cur_lex_type == STRING) {
                pcell[counter - 1].type = DataBase::TEXT;
                pcell[counter - 1].text_value = new char[Lexer::cur_lex.size() + 1];
                strncpy(pcell[counter - 1].text_value, Lexer::cur_lex.c_str(), Lexer::cur_lex.size() + 1);
            }
            else if(Lexer::cur_lex_type == NUMBER) {
                pcell[counter - 1].type = DataBase::LONG;
                pcell[counter - 1].text_value = NULL;
                try {
                    pcell[counter - 1].value = stol(Lexer::cur_lex);
                }
                catch(...) {
                    throw ParserException(ParserException::INSERT_7);
                }
            }
            else {
                throw ParserException(ParserException::INSERT_8);
            }
            Lexer::get_lex();
        }

        Lexer::get_lex();
        if (Lexer::cur_lex_type != END)
            throw ParserException(ParserException::INSERT_9);

        if(counter != t.get_num_field())
            throw ParserException(ParserException::INSERT_10);

        for (i = 0; i < counter; i++) {
            if (pcell[i].type != t.get_field_type(i))
                throw ParserException(ParserException::INSERT_11);
            if (pcell[i].type == DataBase::TEXT)
                if (strlen(pcell[i].text_value) > t.get_field_size(i))
                    throw ParserException(ParserException::INSERT_12);
        }

        t.insert(pcell);
        t.print_table();

        for (i = 0; i < counter; i++)
            if (pcell[i].text_value != NULL)
                delete [] pcell[i].text_value;

        free(pcell);
        t.close_table();
        delete[] filename;
    }
    catch (...) {
        if(pcell != NULL) {
            for (i = 0; i < counter; i++)
                if (pcell[i].text_value != NULL)
                    delete[] pcell[i].text_value;
            free(pcell);
        }
        if(filename != NULL) {
            delete[] filename;
        }
        t.close_table();
        throw;
    }
}

void Parser::SLCT() {
    struct DataBase::FieldStruct* p = NULL;
    char* filename = NULL;
    DataBase::Table t;
    try {
        if((Lexer::cur_lex_type != IDENT) && (Lexer::cur_lex_type != MULT))
            throw ParserException(ParserException::SELECT_1);
        int all_flag = 0; // * in request
        int field_counter = 0; // counter for feelds needed

        std::vector<std::string> fields;
        if(Lexer::cur_lex_type == IDENT) {
            field_counter++;
            fields.push_back(Lexer::cur_lex);
            Lexer::get_lex();
            while(Lexer::cur_lex_type == COMMA) {
                Lexer::get_lex();
                if(Lexer::cur_lex_type != IDENT)
                    throw ParserException(ParserException::SELECT_2);
                field_counter++;
                fields.push_back(Lexer::cur_lex);
                Lexer::get_lex();
            }
        }
        else {
            all_flag = 1;
            Lexer::get_lex();
        }
        if (Lexer::cur_lex_type != FROM)
            throw ParserException(ParserException::SELECT_3);
        Lexer::get_lex();
        if (Lexer::cur_lex_type != IDENT)
            throw ParserException(ParserException::SELECT_4);
        filename = new char[Lexer::cur_lex.size() + 1];
        strncpy(filename, Lexer::cur_lex.c_str(), Lexer::cur_lex.size() + 1);
        t.open_table(filename);

        long i, j;

        if(all_flag == 0) {
            long num_field = t.get_num_field();
            int flag = 0;
            std::vector<long> nums;

            for(i = 0; i < field_counter; i++) {
                for(j = 0; j < num_field; j++) {
                    if(strcmp(t.get_field_name(j), fields[i].c_str()) == 0) {
                        nums.push_back(j);
                        flag = 1;
                        break;
                    }
                }
                if(flag == 0)
                    throw ParserException(ParserException::SELECT_5);
                flag = 0;
            }

            for(i = 0; i < field_counter; i++)
                for(j = i + 1; j < field_counter; j++)
                    if(nums[i] == nums[j])
                        throw ParserException(ParserException::SELECT_6);

            std::sort(nums.rbegin(), nums.rend(), std::greater<long>());

            p = new struct DataBase::FieldStruct [field_counter];
            char* buf;
            for(i = 0; i < field_counter; i++) {
                p[i].type = t.get_field_type(nums[i]);
                buf = t.get_field_name(nums[i]);
                for(j = 0; j < strlen(buf); j++)
                    p[i].field_name[j] = buf[j];
                p[i].field_name[strlen(buf)] = '\0';
                if(p[i].type == DataBase::TEXT)
                    p[i].len = t.get_field_size(nums[i]);
            }
        }
        else {
            field_counter = t.get_num_field();
            p = new struct DataBase::FieldStruct [t.get_num_field()];
            char* buf;
            for(i = 0; i < t.get_num_field(); i++) {
                p[i].type = t.get_field_type(i);
                buf = t.get_field_name(i);
                for(j = 0; j < strlen(buf); j++)
                    p[i].field_name[j] = buf[j];
                p[i].field_name[strlen(buf)] = '\0';
                if(p[i].type == DataBase::TEXT)
                    p[i].len = t.get_field_size(i);
            }
        }

        std::vector<long> nums;
        Lexer::get_lex();
        if(Lexer::cur_lex_type != WHERE)
            throw ParserException(ParserException::SELECT_7);
        Lexer::get_lex();

        nums = WHR(filename);

        t.select(p, field_counter, nums);
        t.close_table();
        delete[] p;
        delete[] filename;
    }
    catch(...) {
        t.close_table();
        if (p != NULL)
            delete[] p;
        if (filename != NULL)
            delete[] filename;
        throw;
    }
}

void Parser::UPDT() {
    char* filename = NULL;
    DataBase::Table t;
    struct DataBase::CellStruct* p = NULL;
    long i;
    try {
        if(Lexer::cur_lex_type != IDENT)
            throw ParserException(ParserException::UPDATE_1);
        filename = new char[Lexer::cur_lex.size() + 1];
        strncpy(filename, Lexer::cur_lex.c_str(), Lexer::cur_lex.size() + 1);
        try {
            t.open_table(filename);
        }
        catch (...) {
            throw;
        }
        Lexer::get_lex();
        if(Lexer::cur_lex_type != SET)
            throw ParserException(ParserException::UPDATE_2);
        Lexer::get_lex();
        if(Lexer::cur_lex_type != IDENT)
            throw ParserException(ParserException::UPDATE_3);

        long num_field = t.get_num_field();
        int flag = 0, num;
        for(i = 0; i < num_field; i++) {
            if(strcmp(t.get_field_name(i), Lexer::cur_lex.c_str()) == 0) {
                flag = 1;
                num = i;
            }
        }
        if(flag == 0)
            throw ParserException(ParserException::UPDATE_4);

        Lexer::get_lex();
        if(Lexer::cur_lex_type != EQUAL)
            throw ParserException(ParserException::UPDATE_5);

        Lexer::get_lex();
        p = new struct DataBase::CellStruct[t.get_num_record()];
        for(i = 0; i < t.get_num_record(); i++)
            p[i].text_value = NULL;

        EXPR(filename, num, p);

        if(Lexer::cur_lex_type != WHERE)
            throw ParserException(ParserException::UPDATE_6);

        Lexer::get_lex();
        std::vector<long> nums;
        nums = WHR(filename);

        t.update(nums, num, p);
        delete[] filename;
        for(i = 0; i < t.get_num_record(); i++)
            if(p[i].text_value != NULL)
                delete[] p[i].text_value;
        delete[] p;
        t.close_table();
    }
    catch (...) {
        if (filename != 0)
            delete[] filename;

        if(p != NULL) {
            for(i = 0; i < t.get_num_record(); i++)
                if(p[i].text_value != NULL)
                    delete[] p[i].text_value;
            delete[] p;
        }
        t.close_table();
        throw;
    }
}

void Parser::DLT() {
    DataBase::Table t;
    char* filename = NULL;
    try {
        if(Lexer::cur_lex_type != FROM)
            throw ParserException(ParserException::DELETE_1);
        Lexer::get_lex();
        if (Lexer::cur_lex_type != IDENT)
            throw ParserException(ParserException::DELETE_2);

        filename = new char[Lexer::cur_lex.size() + 1];
        strncpy(filename, Lexer::cur_lex.c_str(), Lexer::cur_lex.size() + 1);
        try {
            t.open_table(filename);
        }
        catch (...) {
            throw;
        }

        Lexer::get_lex();
        if (Lexer::cur_lex_type != WHERE)
            throw ParserException(ParserException::DELETE_3);
        Lexer::get_lex();
        std::vector<long> nums;
        nums = WHR(filename);

        t.remove(nums);
        t.close_table();
        delete[] filename;
    }
    catch(...) {
        t.close_table();
        if (filename != NULL)
            delete [] filename;
        throw;
    }
}


void Parser::EXPR(char* filename, long num, struct DataBase::CellStruct* p) {
    DataBase::Table t;
    long i, sign;
    char* buf = NULL;
    struct DataBase::CellStruct* p1 = NULL;
    try {
        t.open_table(filename);
        if(t.get_field_type(num) == DataBase::TEXT) {
            if(Lexer::cur_lex_type == STRING) {
                if(strlen(Lexer::cur_lex.c_str()) > t.get_field_size(num))
                    throw ParserException(ParserException::EXPR_3);
                for(i = 0; i < t.get_num_record(); i++) {
                    p[i].type = DataBase::TEXT;
                    p[i].text_value = new char[Lexer::cur_lex.size() + 1];
                    strncpy(p[i].text_value, Lexer::cur_lex.c_str(), Lexer::cur_lex.size() + 1);
                }
                Lexer::get_lex();
            }
            else if(Lexer::cur_lex_type == IDENT) {
                int flag = 0;
                long num1;
                for(i = 0; i < t.get_num_field(); i++) {
                    if(strcmp(t.get_field_name(i), Lexer::cur_lex.c_str()) == 0) {
                        flag = 1;
                        num1 = i;
                        break;
                    }
                }
                if(flag == 0)
                    throw ParserException(ParserException::EXPR_1);
                if(t.get_field_type(num) != t.get_field_type(num1))
                    throw ParserException(ParserException::EXPR_2);

                for(i = 0; i < t.get_num_record(); i++) {
                    p[i].type = DataBase::TEXT;
                    buf = t.get_text_value(i, num1);
                    long j = strlen(buf);
                    while(((buf[j] == ' ') || (buf[j] == '\0'))  && (j >= 0)) {
                        buf[j] = '\0';
                        j--;
                    }
                    if(strlen(buf) > t.get_field_size(num))
                        throw ParserException(ParserException::EXPR_3);
                    p[i].text_value = new char[strlen(buf) + 1];
                    strncpy(p[i].text_value, buf, strlen(buf) + 1);
                    delete[] buf;
                }
                Lexer::get_lex();
            }
            else {
                throw ParserException(ParserException::EXPR_4);
            }
            t.close_table();
            return;
        }
        p1 = new struct DataBase::CellStruct [t.get_num_record()];
        MLT(filename, num, p1);
        memcpy(p, p1, sizeof(struct DataBase::CellStruct) * t.get_num_record());

        while((Lexer::cur_lex_type == PLUS) || (Lexer::cur_lex_type == MINUS)) {
            if(Lexer::cur_lex_type == PLUS) {
                sign = 1;
            }
            else {
                sign = -1;
            }
            Lexer::get_lex();
            MLT(filename, num, p1);
            for(i = 0; i < t.get_num_record(); i++)
                p[i].value = p[i].value + sign * p1[i].value;
        }

        t.close_table();
        if(buf != NULL)
            delete[] buf;

        if(p1 != NULL)
            delete[] p1;

    }
    catch(...) {
        t.close_table();
        if(buf != NULL)
            delete[] buf;
        if(p1 != NULL)
            delete[] p1;
        throw;
    }
}

void Parser::MLT(char* filename, long num, struct DataBase::CellStruct* p) {
    DataBase::Table t;
    long i;
    struct DataBase::CellStruct* p1 = NULL;
    try {
        t.open_table(filename);
        p1 = new struct DataBase::CellStruct [t.get_num_record()];
        BR_EXPR(filename, num, p1);
        memcpy(p, p1, sizeof(struct DataBase::CellStruct) * t.get_num_record());
        int flag;

        while((Lexer::cur_lex_type == MULT) || (Lexer::cur_lex_type == SLASH) || (Lexer::cur_lex_type == PERCENT)) {
            if(Lexer::cur_lex_type == MULT) {
                flag = 0;
            }
            else if (Lexer::cur_lex_type == SLASH) {
                flag = 1;
            }
            else {
                flag = 2;
            }
            Lexer::get_lex();
            BR_EXPR(filename, num, p1);
            if(flag == 0) {
                for(i = 0; i < t.get_num_record(); i++)
                    p[i].value = p[i].value * p1[i].value;
            }
            else if(flag == 1) {
                for(i = 0; i < t.get_num_record(); i++) {
                    if(p1[i].value == 0)
                        throw ParserException(ParserException::MLT_1);
                    p[i].value = p[i].value / p1[i].value;
                }
            }
            else {
                for(i = 0; i < t.get_num_record(); i++) {
                    if(p1[i].value == 0)
                        throw ParserException(ParserException::MLT_1);
                    p[i].value = p[i].value % p1[i].value;
                }
            }
        }

        t.close_table();
        if(p1 != NULL)
            delete[] p1;

    }
    catch(...) {
        t.close_table();
        if(p1 != NULL)
            delete[] p1;
        throw;
    }
}

void Parser::BR_EXPR(char* filename, long num, struct DataBase::CellStruct* p) {
    DataBase::Table t;
    long i;
    struct DataBase::CellStruct* p1 = NULL;
    try {
        t.open_table(filename);
        p1 = new struct DataBase::CellStruct[t.get_num_record()];
        if(Lexer::cur_lex_type == ROUND_OPEN) {
            Lexer::get_lex();
            EXPR(filename, num, p1);
            if(Lexer::cur_lex_type != ROUND_CLOSE)
                throw ParserException(ParserException::BR_1);
            memcpy(p, p1, sizeof(struct DataBase::CellStruct) * t.get_num_record());
            Lexer::get_lex();
        }
        else if(Lexer::cur_lex_type == NUMBER) {
            try {
                for(i = 0; i < t.get_num_record(); i++)
                    p[i].value = stol(Lexer::cur_lex);
            }
            catch(...) {
                throw ParserException(ParserException::BR_2);
            }
            Lexer::get_lex();
        }
        else if(Lexer::cur_lex_type == IDENT) {
            int flag = 0;
            long num1;
            for(i = 0; i < t.get_num_field(); i++) {
                if(strcmp(t.get_field_name(i), Lexer::cur_lex.c_str()) == 0) {
                    flag = 1;
                    num1 = i;
                    break;
                }
            }
            if (flag == 0)
                throw ParserException(ParserException::BR_3);
            if(t.get_field_type(num1) != t.get_field_type(num))
                throw ParserException(ParserException::BR_4);
            for(i = 0; i < t.get_num_record(); i++)
                p[i].value = t.get_long_value(i, num1);
            Lexer::get_lex();
        }
        else {
            throw ParserException(ParserException::BR_5);
        }

        t.close_table();
        if(p1 != NULL)
            delete[] p1;
    }
    catch (...) {
        if(p1 != NULL)
            delete[] p1;
        t.close_table();
        throw;
    }
}

std::vector<long> Parser::WHR(char* filename) {
    std::vector<long> v;
    DataBase::Table t;
    long i, j, k;
    struct DataBase::CellStruct* p = NULL;
    std::vector<std::string> lex;
    std::vector<enum lex_type_t> types;
    int where_type;
    int not_flag = 0;

    try {
        t.open_table(filename);
        p = new struct DataBase::CellStruct[t.get_num_record()];
        for(i = 0; i < t.get_num_record(); i++)
            p[i].text_value = NULL;

        if (Lexer::cur_lex_type == ALL) {
            for(i = 0; i < t.get_num_record(); i++)
                v.push_back(i);
            Lexer::get_lex();
            if(Lexer::cur_lex_type != END)
                throw ParserException(ParserException::WHERE_1);
            delete[] p;
            t.close_table();
            return v;
        }
        where_type = -1;
        BOOL_EXPR(filename, p, where_type);

        if(where_type == 1) {
            if(Lexer::cur_lex_type == NOT) {
                not_flag = 1;
                Lexer::get_lex();
            }
            if(Lexer::cur_lex_type == LIKE) {
                Lexer::get_lex();
                if(Lexer::cur_lex_type != STRING)
                    throw ParserException(ParserException::WHERE_10);
                std::string::iterator pointer = Lexer::cur_lex.begin();
                std::string s;

                while(pointer != Lexer::cur_lex.end()) {
                    if(*pointer == '_') {
                        s += '.';
                    }
                    else if(*pointer == '%') {
                        s += '.';
                        s += '*';
                    }
                    else if(*pointer == 92) { // 92 = '\'
                        s = s + (char)92 + (char)92;
                    }
                    else if(*pointer == '$') {
                        s = s + (char)92 + '$';
                    }
                    else if(*pointer == '.') {
                        s = s + (char)92 + '.';
                    }
                    else if(*pointer == '|') {
                        s = s + (char)92 + '|';
                    }
                    else if(*pointer == '?') {
                        s = s + (char)92 + '?';
                    }
                    else if(*pointer == '*') {
                        s = s + (char)92 + '*';
                    }
                    else if(*pointer == '+') {
                        s = s + (char)92 + '+';
                    }
                    else if(*pointer == '(') {
                        s = s + (char)92 + '(';

                    }
                    else if(*pointer == ')') {
                        s = s + (char)92 + ')';
                    }
                    else {
                        s += *pointer;
                    }
                    pointer++;
                }
                std::string str;
                try {
                    std::regex reg(s);
                    for(i = 0; i < t.get_num_record(); i++) {
                        str.assign(p[i].text_value, strlen(p[i].text_value));
                        if((regex_match(str.begin(), str.end(), reg) == 1) || (str == Lexer::cur_lex)) {
                            if (not_flag == 0)
                                v.push_back(i);
                        }
                        else if(not_flag == 1) {
                            v.push_back(i);
                        }
                    }
                }
                catch(...) {
                    throw ParserException(ParserException::WHERE_11);
                }
                Lexer::get_lex();
                if(Lexer::cur_lex_type != END)
                    throw ParserException(ParserException::WHERE_1);
            }
            else if(Lexer::cur_lex_type == IN) {
                Lexer::get_lex();
                if(Lexer::cur_lex_type != ROUND_OPEN)
                    throw ParserException(ParserException::WHERE_3);
                Lexer::get_lex();
                std::vector<std::string> s;
                if(Lexer::cur_lex_type != STRING)
                    throw ParserException(ParserException::WHERE_4);
                s.push_back(Lexer::cur_lex);
                Lexer::get_lex();
                while(Lexer::cur_lex_type == COMMA) {
                    Lexer::get_lex();
                    if(Lexer::cur_lex_type != STRING)
                        throw ParserException(ParserException::WHERE_4);
                    s.push_back(Lexer::cur_lex);
                    Lexer::get_lex();
                }
                if(Lexer::cur_lex_type != ROUND_CLOSE)
                    throw ParserException(ParserException::WHERE_5);
                Lexer::get_lex();
                if(Lexer::cur_lex_type != END)
                    throw ParserException(ParserException::WHERE_6);

                if(not_flag == 0) {
                    for (i = 0; i < t.get_num_record(); i++) {
                        for (j = 0; j < s.size(); j++) {
                            if (strcmp(p[i].text_value, s[j].c_str()) == 0) {
                                v.push_back(i);
                                break;
                            }
                        }
                    }
                }
                else {
                    for(i = 0; i < t.get_num_record(); i++) {
                        k = 0;
                        for(j = 0; j < s.size(); j++) {
                            if(strcmp(p[i].text_value, s[j].c_str()) == 0) {
                                k = 1;
                                break;
                            }
                        }
                        if(k == 0) {
                            v.push_back(i);
                        }
                    }
                }

            }
            else {
                throw ParserException(ParserException::WHERE_9);
            }
        }
        else if(where_type == 2) {
            if(Lexer::cur_lex_type == NOT) {
                not_flag = 1;
                Lexer::get_lex();
            }
            if(Lexer::cur_lex_type != IN)
                throw ParserException(ParserException::WHERE_2);
            Lexer::get_lex();
            if(Lexer::cur_lex_type != ROUND_OPEN)
                throw ParserException(ParserException::WHERE_3);
            Lexer::get_lex();
            std::vector<std::string> s;
            if(Lexer::cur_lex_type != STRING)
                throw ParserException(ParserException::WHERE_4);
            s.push_back(Lexer::cur_lex);
            Lexer::get_lex();

            while(Lexer::cur_lex_type == COMMA) {
                Lexer::get_lex();
                if(Lexer::cur_lex_type != STRING)
                    throw ParserException(ParserException::WHERE_4);
                s.push_back(Lexer::cur_lex);
                Lexer::get_lex();
            }
            if(Lexer::cur_lex_type != ROUND_CLOSE)
                throw ParserException(ParserException::WHERE_5);
            Lexer::get_lex();
            if(Lexer::cur_lex_type != END)
                throw ParserException(ParserException::WHERE_6);

            if(not_flag == 0) {
                for(i = 0; i < t.get_num_record(); i++) {
                    for(j = 0; j < s.size(); j++) {
                        if(strcmp(p[i].text_value, s[j].c_str()) == 0) {
                            v.push_back(i);
                            break;
                        }
                    }
                }
            }
            else {
                for(i = 0; i < t.get_num_record(); i++) {
                    k = 0;
                    for(j = 0; j < s.size(); j++) {
                        if(strcmp(p[i].text_value, s[j].c_str()) == 0) {
                            k = 1;
                            break;
                        }
                    }
                    if(k == 0)
                        v.push_back(i);
                }
            }
        }
        else if(where_type == 0) {
            if(Lexer::cur_lex_type == NOT) {
                not_flag = 1;
                Lexer::get_lex();
            }
            if(Lexer::cur_lex_type != IN)
                throw ParserException(ParserException::WHERE_2);
            Lexer::get_lex();
            if(Lexer::cur_lex_type != ROUND_OPEN)
                throw ParserException(ParserException::WHERE_3);
            Lexer::get_lex();

            std::vector<long> s;
            if(Lexer::cur_lex_type != NUMBER)
                throw ParserException(ParserException::WHERE_7);
            try {
                j = stol(Lexer::cur_lex);
            }
            catch (...) {
                throw ParserException(ParserException::WHERE_8);
            }
            s.push_back(j);
            Lexer::get_lex();
            while(Lexer::cur_lex_type == COMMA) {
                Lexer::get_lex();
                if(Lexer::cur_lex_type != NUMBER)
                    throw ParserException(ParserException::WHERE_7);
                try {
                    j = stol(Lexer::cur_lex);
                }
                catch(...) {
                    throw ParserException(ParserException::WHERE_8);
                }
                s.push_back(j);
                Lexer::get_lex();
            }
            if(Lexer::cur_lex_type != ROUND_CLOSE)
                throw ParserException(ParserException::WHERE_5);
            Lexer::get_lex();
            if(Lexer::cur_lex_type != END)
                throw ParserException(ParserException::WHERE_6);
            if(not_flag == 0) {
                for(i = 0; i < t.get_num_record(); i++) {
                    for(j = 0; j < s.size(); j++) {
                        if(p[i].value == s[j]) {
                            v.push_back(i);
                            break;
                        }
                    }
                }
            }
            else {
                for(i = 0; i < t.get_num_record(); i++) {
                    k = 0;
                    for(j = 0; j < s.size(); j++) {
                        if (p[i].value == s[j]) {
                            k = 1;
                            break;
                        }
                    }
                    if(k == 0)
                        v.push_back(i);
                }
            }
        }
        else {
            if(Lexer::cur_lex_type != END)
                throw ParserException(ParserException::WHERE_6);
            for(i = 0; i < t.get_num_record(); i++)
                if(p[i].value != 0)
                    v.push_back(i);
        }
        if(p != NULL) {
            for(i = 0; i < t.get_num_record(); i++)
                if(p[i].text_value != NULL)
                    delete[] p[i].text_value;
            delete[] p;
        }
        t.close_table();
        return v;
    }
    catch(...) {
        if(p != NULL) {
            for(i = 0; i < t.get_num_record(); i++) {
                if(p[i].text_value != NULL) {
                    delete[] p[i].text_value;
                }
            }
            delete[] p;
        }
        t.close_table();
        throw;
    }
}

void Parser::EXPR_W(char* filename, struct DataBase::CellStruct* p, int& flag) {
    DataBase::Table t;
    long i, sign;
    struct DataBase::CellStruct* p1 = NULL;
    char* buf;

    try {
        t.open_table(filename);
        p1 = new struct DataBase::CellStruct[t.get_num_record()];
        for(i = 0; i < t.get_num_record(); i++)
            p1[i].text_value = NULL;

        int flag1 = flag;
        if(Lexer::cur_lex_type == IDENT) {
            long num = -1;
            for(i = 0; i < t.get_num_field(); i++) {
                if(strcmp(t.get_field_name(i), Lexer::cur_lex.c_str()) == 0) {
                    num = i;
                    break;
                }
            }
            if(num == -1)
                throw ParserException(ParserException::EXPR_W_2);
            if(t.get_field_type(num) == DataBase::TEXT) {
                flag = 1;
                for(i = 0; i < t.get_num_record(); i++) {
                    buf = t.get_text_value(i, num);
                    long j = strlen(buf);
                    while(((buf[j] == ' ') || (buf[j] == '\0'))  && (j >= 0)) {
                        buf[j] = '\0';
                        j--;
                    }
                    p[i].text_value = new char [strlen(buf) + 1];
                    strncpy(p[i].text_value, buf, strlen(buf) + 1);
                    delete[] buf;
                }
                Lexer::get_lex();
                t.close_table();
                return;
            }
        }
        else if(Lexer::cur_lex_type == STRING) {
            flag = 2;
            for(i = 0; i < t.get_num_record(); i++) {
                p[i].text_value = new char [strlen(Lexer::cur_lex.c_str()) + 1];
                strncpy(p[i].text_value, Lexer::cur_lex.c_str(), strlen(Lexer::cur_lex.c_str()) + 1);
            }
            Lexer::get_lex();
            t.close_table();
            return;
        }

        MLT_W(filename, p1, flag1);
        memcpy(p, p1, sizeof(struct DataBase::CellStruct) * t.get_num_record());
        flag = flag1;
        if ((flag == 1) || (flag == 2)) {
            t.close_table();
            if (p1 != NULL)
                delete[] p1;
            return;
        }

        while((Lexer::cur_lex_type == PLUS) || (Lexer::cur_lex_type == MINUS)) {
            if(Lexer::cur_lex_type == PLUS) {
                sign = 1;
                flag = 0;
            }
            else {
                sign = -1;
                flag = 0;
            }
            Lexer::get_lex();
            MLT_W(filename, p1, flag1);
            if(flag1 == 1) {
                for(i = 0; i < t.get_num_record(); i++)
                    if(p1[i].text_value != NULL)
                        delete[] p1[i].text_value;
                throw ParserException(ParserException::EXPR_W_1);
            }
            for(i = 0; i < t.get_num_record(); i++)
                p[i].value = p[i].value + sign * p1[i].value;
        }
        t.close_table();
        if(p1 != NULL)
            delete[] p1;
    }
    catch(...) {
        t.close_table();
        if(p1 != NULL)
            delete[] p1;
        throw;
    }
}

void Parser::MLT_W(char* filename, struct DataBase::CellStruct* p, int& flag) {
    DataBase::Table t;
    long i, f;
    struct DataBase::CellStruct* p1 = NULL;

    try {
        t.open_table(filename);
        p1 = new struct DataBase::CellStruct[t.get_num_record()];
        for(i = 0; i < t.get_num_record(); i++)
            p1[i].text_value = NULL;

        int flag1 = flag;
        BR_EXPR_W(filename, p1, flag1);
        memcpy(p, p1, sizeof(struct DataBase::CellStruct) * t.get_num_record());
        flag = flag1;
        if((flag == 1) || (flag == 2)) {
            t.close_table();
            if(p1 != NULL)
                delete[] p1;
            return;
        }
        while((Lexer::cur_lex_type == MULT) || (Lexer::cur_lex_type == SLASH) || (Lexer::cur_lex_type == PERCENT)) {
            if(Lexer::cur_lex_type == MULT) {
                flag = 0;
                f = 0;
            }
            else if(Lexer::cur_lex_type == SLASH) {
                flag = 0;
                f = 1;
            }
            else {
                flag = 0;
                f = 2;
            }
            Lexer::get_lex();
            BR_EXPR_W(filename, p1, flag1);
            if(flag1 == 1) {
                for(i = 0; i < t.get_num_record(); i++)
                    if(p1[i].text_value != NULL)
                        delete [] p1[i].text_value;
                throw ParserException(ParserException::MLT_W_1);
            }
            if(f == 0) {
                for(i = 0; i < t.get_num_record(); i++)
                    p[i].value = p[i].value * p1[i].value;
            }
            else if(f == 1) {
                for (i = 0; i < t.get_num_record(); i++) {
                    if (p1[i].value == 0)
                        throw ParserException(ParserException::MLT_W_2);
                    p[i].value = p[i].value / p1[i].value;
                }
            }
            else {
                for(i = 0; i < t.get_num_record(); i++) {
                    if (p1[i].value == 0)
                        throw ParserException(ParserException::MLT_W_2);
                    p[i].value = p[i].value % p1[i].value;
                }
            }
        }
        t.close_table();
        if(p1 != NULL)
            delete[] p1;
    }
    catch(...) {
        t.close_table();
        if(p1 != NULL)
            delete[] p1;
        throw;
    }
}

void Parser::BR_EXPR_W(char* filename, struct DataBase::CellStruct* p, int& flag) {
    DataBase::Table t;
    long i;
    char* buf = NULL;
    struct DataBase::CellStruct* p1 = NULL;

    try {
        t.open_table(filename);
        int flag1 = flag;
        p1 = new struct DataBase::CellStruct[t.get_num_record()];
        for(i = 0; i < t.get_num_record(); i++)
            p1[i].text_value = NULL;

        if(Lexer::cur_lex_type == ROUND_OPEN) {
            Lexer::get_lex();
            BOOL_EXPR(filename, p1, flag1);

            if((flag1 == 3) && ((flag != 3) && (flag != -1)))
                throw ParserException(ParserException::BR_W_1);
            if((flag == 3) && ((flag1 != 3) && (flag1 != -1)))
                throw ParserException(ParserException::BR_W_1);
            if(Lexer::cur_lex_type != ROUND_CLOSE)
                throw ParserException(ParserException::BR_W_2);
            if((flag1 == 1) && (flag == 0)) {
                for(i = 0; i < t.get_num_record(); i++) {
                    if(p1[i].text_value == NULL)
                        delete[] p1[i].text_value;
                    throw ParserException(ParserException::BR_W_1);
                }
            }
            flag = flag1;

            memcpy(p, p1, sizeof(struct DataBase::CellStruct) * t.get_num_record());
            if(flag == 1) {
                Lexer::get_lex();
                t.close_table();
                if(buf != NULL)
                    delete[] buf;
                if(p1 != NULL)
                    delete[] p1;
                return;
            }
            Lexer::get_lex();
        }
        else if (Lexer::cur_lex_type == NUMBER) {
            flag = 0;
            try {
                for(i = 0; i < t.get_num_record(); i++)
                    p[i].value = stol(Lexer::cur_lex);
            }
            catch (...) {
                throw ParserException(ParserException::BR_W_3);
            }
            Lexer::get_lex();
        }
        else if(Lexer::cur_lex_type == IDENT) {
            long num = -1;
            for(i = 0; i < t.get_num_field(); i++) {
                if(strcmp(t.get_field_name(i), Lexer::cur_lex.c_str()) == 0) {
                    num = i;
                    break;
                }
            }
            if(num == -1)
                throw ParserException(ParserException::BR_W_4);

            if(t.get_field_type(num) == DataBase::TEXT) {
                if(flag == 0)
                    throw ParserException(ParserException::BR_W_5);
                flag = 1;
                for(i = 0; i < t.get_num_record(); i++) {
                    buf = t.get_text_value(i, num);
                    long j = strlen(buf);
                    while(((buf[j] == ' ') || (buf[j] == '\0'))  && (j >= 0)) {
                        buf[j] = '\0';
                        j--;
                    }
                    p[i].text_value = new char[strlen(buf) + 1];
                    strncpy(p[i].text_value, buf, strlen(buf) + 1);
                    delete[] buf;
                }
                Lexer::get_lex();
                t.close_table();
                if(p1 != NULL)
                    delete[] p1;
                return;
            }
            flag = 0;
            for (i = 0; i < t.get_num_record(); i++)
                p[i].value = t.get_long_value(i, num);
            Lexer::get_lex();
        }
        else if(Lexer::cur_lex_type == STRING) {
            if(flag == 0)
                throw ParserException(ParserException::BR_W_5);
            flag = 1;
            for(i = 0; i < t.get_num_record(); i++) {
                p[i].text_value = new char [Lexer::cur_lex.size() + 1];
                strncpy(p[i].text_value, Lexer::cur_lex.c_str(), Lexer::cur_lex.size() + 1);
            }
            Lexer::get_lex();
            t.close_table();
            if(p1 != NULL)
                delete[] p1;
            if (buf != NULL)
                delete[] buf;
            return;
        }
        else {
            throw ParserException(ParserException::BR_W_6);
        }
        t.close_table();
        if(p1 != NULL)
            delete[] p1;
        if(buf != NULL)
            delete[] buf;
    }
    catch(...) {
        if(p1 != NULL)
            delete[] p1;
        if(buf != NULL)
            delete[] buf;
        t.close_table();
        throw;
    }
}

void Parser::BOOL_EXPR(char* filename, struct DataBase::CellStruct* p, int& flag) {
    DataBase::Table t;
    long i;
    int flag1;
    struct DataBase::CellStruct* p1 = NULL;

    try {
        t.open_table(filename);
        p1 = new struct DataBase::CellStruct [t.get_num_record()];
        BOOL_MLT(filename, p1, flag);
        memcpy(p, p1, sizeof(struct DataBase::CellStruct) * t.get_num_record());
        if((flag == 0) || (flag == 1) || (flag == 2)) {
            if(p1 != NULL)
                delete[] p1;
            t.close_table();
            return;
        }
        while(Lexer::cur_lex_type == OR) {
            Lexer::get_lex();
            BOOL_MLT(filename, p1, flag1);
            if(flag1 != 3)
                throw ParserException(ParserException::BOOL_EXPR_1);
            flag = 3;
            for(i = 0; i < t.get_num_record(); i++)
                p[i].value = (p[i].value || p1[i].value);
        }
        if(p1 != NULL)
            delete[] p1;
        t.close_table();

    }
    catch(...) {
        if(p1 != NULL)
            delete[] p1;
        t.close_table();
        throw;
    }
}

void Parser::BOOL_MLT(char* filename, struct DataBase::CellStruct* p, int& flag) {
    DataBase::Table t;
    long i;
    int flag1;
    struct DataBase::CellStruct* p1 = NULL;

    try {
        t.open_table(filename);
        p1 = new struct DataBase::CellStruct[t.get_num_record()];
        BOOL_BR_EXPR(filename, p1, flag);
        memcpy(p, p1, sizeof(struct DataBase::CellStruct) * t.get_num_record());

        if((flag == 0) || (flag == 1) || (flag == 2)) {
            if(p1 != NULL)
                delete[] p1;
            t.close_table();
            return;
        }
        while(Lexer::cur_lex_type == AND) {
            Lexer::get_lex();
            BOOL_BR_EXPR(filename, p1, flag1);
            if(flag1 != 3)
                throw ParserException(ParserException::BOOL_MLT_1);
            flag = 3;
            for(i = 0; i < t.get_num_record(); i++)
                p[i].value = (p[i].value && p1[i].value);
        }
        if(p1 != NULL)
            delete[] p1;
        t.close_table();
    }
    catch (...) {
        if(p1 != NULL)
            delete[] p1;
        t.close_table();
        throw;
    }
}

void Parser::BOOL_BR_EXPR(char* filename, struct DataBase::CellStruct* p, int& flag) {
    DataBase::Table t;
    long i;
    struct DataBase::CellStruct * p1 = NULL;

    try {
        t.open_table(filename);
        p1 = new struct DataBase::CellStruct[t.get_num_record()];
        for (i = 0; i < t.get_num_record(); i++)
            p1[i].text_value = NULL;

        if(Lexer::cur_lex_type == NOT) {
            if((flag != 3) && (flag != -1))
                throw ParserException(ParserException::BOOL_BR_4);
            flag = 3;
            int flag1 = flag;
            Lexer::get_lex();
            BOOL_BR_EXPR(filename, p1, flag1);
            if(flag1 != 3)
                throw ParserException(ParserException::BOOL_BR_4);
            for(i = 0; i < t.get_num_record(); i++)
                p[i].value = !p1[i].value;
            delete[] p1;
            t.close_table();
            return;
        }

        int flag1 = -1;
        EXPR_W(filename, p, flag1);

        if((flag1 == 3) && ((Lexer::cur_lex_type >= 27) && (Lexer::cur_lex_type <= 32)))
            throw ParserException(ParserException::BOOL_BR_4);
        if(((flag1 != 3) && (flag == 3)) && ((Lexer::cur_lex_type < 27) || (Lexer::cur_lex_type > 32)))
            throw ParserException(ParserException::BOOL_BR_2);
        if((Lexer::cur_lex_type < 27) || (Lexer::cur_lex_type > 32)) {
            flag = flag1;
            delete[] p1;
            t.close_table();
            return;
        }
        else {
            if ((flag != 3) && (flag != -1))
                throw ParserException(ParserException::BOOL_BR_4);
            enum lex_type_t j = Lexer::cur_lex_type;
            Lexer::get_lex();
            flag = 3;
            int flag2 = -1;
            EXPR_W(filename, p1, flag2);
            if((flag1 == 0) && ((flag2 == 1) || (flag2 == 2)))
                throw ParserException(ParserException::BOOL_BR_4);
            if((flag2 == 0) && ((flag1 == 1) || (flag1 == 2)))
                throw ParserException(ParserException::BOOL_BR_4);
            if(flag2 == 3)
                throw ParserException(ParserException::BOOL_BR_4);
            if(flag1 == 0) {
                if(j == EQUAL) {
                    for (i = 0; i < t.get_num_record(); i++)
                        p[i].value = (p[i].value == p1[i].value);
                }
                else if(j == NOT_EQUAL) {
                    for(i = 0; i < t.get_num_record(); i++)
                        p[i].value = (p[i].value != p1[i].value);
                }
                else if(j == LESS) {
                    for (i = 0; i < t.get_num_record(); i++)
                        p[i].value = (p[i].value < p1[i].value);
                }
                else if(j == LESS_EQUAL) {
                    for (i = 0; i < t.get_num_record(); i++)
                        p[i].value = (p[i].value <= p1[i].value);
                }
                else if(j == GREATER) {
                    for(i = 0; i < t.get_num_record(); i++)
                        p[i].value = (p[i].value > p1[i].value);
                }
                else {
                    for(i = 0; i < t.get_num_record(); i++)
                        p[i].value = (p[i].value >= p1[i].value);
                }
            }
            else {
                if(j == EQUAL) {
                    for (i = 0; i < t.get_num_record(); i++)
                        p[i].value = !strcmp(p[i].text_value, p1[i].text_value);
                }
                else if (j == NOT_EQUAL) {
                    for (i = 0; i < t.get_num_record(); i++) {
                        if (strcmp(p[i].text_value, p1[i].text_value) != 0) {
                            p[i].value = 1;
                        }
                        else {
                            p[i].value = 0;
                        }
                    }
                }
                else if(j == LESS) {
                    for(i = 0; i < t.get_num_record(); i++) {
                        if(strcmp(p[i].text_value, p1[i].text_value) < 0) {
                            p[i].value = 1;
                        }
                        else {
                            p[i].value = 0;
                        }
                    }
                }
                else if(j == LESS_EQUAL) {
                    for(i = 0; i < t.get_num_record(); i++) {
                        if (strcmp(p[i].text_value, p1[i].text_value) <= 0) {
                            p[i].value = 1;
                        }
                        else {
                            p[i].value = 0;
                        }
                    }
                }
                else if(j == GREATER) {
                    for(i = 0; i < t.get_num_record(); i++) {
                        if(strcmp(p[i].text_value, p1[i].text_value) > 0) {
                            p[i].value = 1;
                        }
                        else {
                            p[i].value = 0;
                        }
                    }
                }
                else {
                    for(i = 0; i < t.get_num_record(); i++) {
                        if(strcmp(p[i].text_value, p1[i].text_value) >= 0) {
                            p[i].value = 1;
                        }
                        else {
                            p[i].value = 0;
                        }
                    }
                }
                for(i = 0; i < t.get_num_record(); i++) {
                    delete[] p[i].text_value;
                    p[i].text_value = NULL;
                    delete[] p1[i].text_value;
                    p1[i].text_value = NULL;
                }
            }
            flag = 3;
        }
        delete[] p1;
        t.close_table();
    }
    catch(...) {
        if(p1 != NULL) {
            for(i = 0; i < t.get_num_record(); i++)
                if(p1[i].text_value != NULL)
                    delete[] p1[i].text_value;
            delete[] p1;
        }
        t.close_table();
        throw;
    }
}
