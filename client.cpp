#include <iostream>
#include "sockets.hpp"

using namespace SQLServer;

const char * addr = "SQLServer.txt";

int main() {
    try {
        UnClientSocket sock(addr);
        sock.connect_sock();
        std::cout << "welcome to model SQL web-server. waiting for response..." << std::endl;
        std::cout << "type 'exit' or Ctrl+D to finish." << std::endl;

        std::string mes = " ";
        std::string ex = "exit";
        ex += '\n';
        std::string buf;

        char c;
        while (mes != ex) {
            c = getchar();
            if (c == EOF) {
                mes = ex;
            } else {
                if (c == '\n') {
                    mes = "\n";
                } else {
                    getline(std::cin, mes);
                    mes = c + mes + '\n';
                }
            }
            sock.put_string(mes);
            if (mes != ex) {
                buf = " ";
                while (buf != "\n") {
                    buf = sock.get_string();
                    std::cout << buf;
                }
            }
        }
        sock.finish();
    } catch (SocketException & e) {
        e.print_message();
    }
    return 0;
}
