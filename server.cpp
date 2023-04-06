#include <iostream>
#include "sockets.hpp"
#include "dbms.hpp"
#include "lexical_analyzer.hpp"
#include "parser.hpp"

using namespace SQLServer;

const char* addr = "SQLServer.txt";

class MyServerSocket : public UnServerSocket {
public:
    MyServerSocket() : UnServerSocket (addr) {} // конструктор
    ~MyServerSocket() = default; // деструктор

    void on_accept (BaseSocket* p) { // обработка информации

        dup2(p->get_descr(), 1);
        std::string message;
        std::string ex = "exit";
        ex += '\n';
        message = p->get_string();
        while (message != ex) {
            try {
                Parser::init(message);
                Parser::S();
            } catch (Lexer::LexerException e) {
                e.print_message();
            } catch (Parser::ParserException e) {
                e.print_message();
            } catch (DataBase::DataBaseException e) {
                e.print_message();
            }
            message = p->get_string();
        }
        p->finish();
        delete p;
    }
};

int main(int argc, char** argv) {
    try {
        MyServerSocket sock;
        SQLServer::BaseSocket* p;
        sock.listen_sock(1);
        std::cout << "welcome to model SQL web-server. waiting for request..." << std::endl;
        p = sock.accept_sock();
        sock.on_accept(p);
        unlink(addr);
        sock.finish();
    } catch (SocketException & e) {
        e.print_message();
    }
    exit(0);
}
