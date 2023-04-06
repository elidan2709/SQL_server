----------------------------MODEL-SQL-SERVER-BY-DANIEL-ELISHAKOV--------------------------
|				                                                         |
|                                    version 2.0 beta                                    |
|                                                                                        |
-----------------------------------all rights reserved------------------------------------
	
______________________________WELCOME TO README OF MY PROGRAM_____________________________

This ReadMe refers to the second stage of Model SQL web-server MSU task. Check previous part readme describing dbms.hpp and sockets.hpp, if you haven't yet. This part requires lexical analyzer, parser and executer. My code is based on examples from http://cmcmsu.info/2course/

This part contains: lexical_analyzer.hpp, parser.hpp.

First header-file lexical_analyzer.hpp is used for analysis of the input string requested by the client. The main task of this module is to read the lexeme and identify its type for further manipulations.

Another header-file parser.hpp analyses the syntax of the input string and executes client request if it is grammatically and logically correct. Parser is fully based on recursive descent method. This method requires some features for the grammar it is written for. I mean the grammar for model SQL language given in the manual isn't suitable for this method and it should be partly rewritten. I'm talking about WHERE-clause, for which RD-method can't be implemented due to several specifications. One of them is the fact that in some cases it's not possible to say for sure if the string belongs to the language or not without further analysis.

Here is the grammar for WHERE-clause which can be parsed by RD-method:

   BOOL_EXPR --> BOOL_MLT {'OR' BOOL_MLT}
    BOOL_MLT --> BOOL_BR_EXPR {'AND' BOOL_BR_EXPR}
BOOL_BR_EXPR --> 'NOT' BOOL_MLT | EXPR_W [OP EXPR_W]
          OP --> '<' | '>' | '<=' | '>=' | '=' | '!='
      EXPR_W --> MLT_W {'+' MLT_W} | TEXT
       MLT_W --> BR_EXPR_W { '*' BR_EXPR_W }
   BR_EXPR_W --> 'long-field name' | 'num' | (BOOL_EXPR)
        TEXT --> 'text-field name' | 'text'



void S(); - start function for syntax analysis
void CRT(); - CREATE request
void DRP(); - DROP request
void INSRT(); - INSERT request
void SLCT(); - SELECT request
void UPDT(); - UPDATE request
void DLT(); - DELETE request

void EXPR(char* filename, long num, struct DataBase::CellStruct* p);  -expression for UPDATE request. calculates target value for every record and puts it into array.

void MLT(char* filename, long num, struct DataBase::CellStruct* p); -multiplication for UPDATE request. calculates target value for every record and puts it into array.

void BR_EXPR(char* filename, long num, struct DataBase::CellStruct* p); -expression in brackets, number or id for UPDATE request. calculates target value for every record and puts it into array. 

std::vector<long> WHR(char* filename); -processing WHERE-clause, returns vector of numbers of records, which fit under the WHERE-clause.

void EXPR_W(char* filename, struct DataBase::CellStruct* p, int& flag); -expression for WHERE-clause, type of expression (text or long) may be unknown yet, calculates target value for every record and puts it into array.

void MLT_W(char* filename, struct DataBase::CellStruct* p, int& flag); -multiplication for WHERE-clause, type of expression (text or long) may be unknown yet, calculates target value for every record and puts it into array.

void BR_EXPR_W(char* filename, struct DataBase::CellStruct* p, int& flag); -expression in brackets, number or id for WHERE-clause, type of expression (text or long) may be unknown yet. calculates target value for every record and puts it into array.

void BOOL_EXPR(char* filename, struct DataBase::CellStruct* p, int& flag); -bool expression for WHERE-clause, calculates target value for every record and puts it into array.

void BOOL_MLT(char* filename, struct DataBase::CellStruct* p, int& flag); -bool multiplication for WHERE-clause, calculates target value for every record and puts it into array.

void BOOL_BR_EXPR(char* filename, struct DataBase::CellStruct* p, int& flag); -bool expression in brackets, relation or bool factor for WHERE-clause, calculates target value for every record and puts it into array. 

flag is a mode for expression type (-1- unknown, 0- long, 1- text field, 2- string, 3- bool)

I also use regular expressions for one of the WHERE-alternatives, so some symbols need changing to regex type '%' ~ '.*', '_' ~ '.' and '\' before other

RD-method can be implemented, because all conditions of implementation are fulfilled.
There are no two rules for eps.  Nor first conflicts. Nor first-follow conflicts in the grammar

Grammar for other regular expressions of model SQL is given in the manual. RD-method is OK for it.

To test my program use makefile, which is attached with the code. Move to the directory with the code in console and type make all. Then ./server and ./client in different console windows. You can find several tests in task manual here: http://cmcmsu.info/2course/

Due to the time constraints and final exams I made the easiest version of the program, in which server and client are executed in one computer, but it is not hard to upgrade it using sockets.

Thank you for using my program and reading this.

P.S. Will be glad to answer your questions or getting the feedback on mail: s02190256.gse.cs.msu.ru

----------------------------MODEL-SQL-SERVER-BY-DANIEL-ELISHAKOV--------------------------
|				                                                         |
|                                    version 2.0 beta                                    |
|                                                                                        |
-----------------------------------all rights reserved------------------------------------
