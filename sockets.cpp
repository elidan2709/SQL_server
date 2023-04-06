#include "sockets.hpp"

SQLServer::SocketException::SocketException (error_code code) {
    switch(code) {
        case CREATE:
            error_message = "socket: unsuccessful creating";
            break;
        case CONNECT:
            error_message = "socket: unsuccessful connecting";
            break;
        case SEND:
            error_message = "socket: unsuccessful sending";
            break;
        case RECV:
            error_message = "socket: unsuccessful receiving";
            break;
        case BIND:
            error_message = "socket: unsuccessful binding by server";
            break;
        case LISTEN:
            error_message = "socket: unsuccessful listening by server";
            break;
        case ACCEPT:
            error_message = "socket: unsuccessful accepting by server";
            break;
    }
}

void SQLServer::SocketException::print_message() {
    std::cout << error_message << ", errno = " << errno << '.' << std::endl;
}

SQLServer::BaseSocket::BaseSocket(int sd, const char* name) {
    sock_d = sd;
    if(name != NULL) {
        sock_addr.sun_family = AF_UNIX;
        strcpy(sock_addr.sun_path, name);
    }
}

void SQLServer::BaseSocket::write(void* buf, int len) {
    if(send(sock_d, buf, len, 0) == -1)
        throw SocketException(SocketException::SEND);
}

void SQLServer::BaseSocket::put_char(int c) {
    if(send(sock_d, (char *) &c, sizeof(char), 0) == -1)
        throw SocketException(SocketException::SEND);
}

void SQLServer::BaseSocket::put_string(const char* str) {
    if(send(sock_d, str, strlen(str) * sizeof(char), 0) == -1)
        throw SocketException(SocketException::SEND);
    if(str[strlen(str) - 1] != '\n')
        BaseSocket::put_char('\n');
}

void SQLServer::BaseSocket::put_string(const std::string& s) {
    if(send(sock_d, s.c_str(), s.length() * sizeof(char), 0) == -1)
        throw SocketException(SocketException::SEND);
    if (s[s.length() - 1] != '\n')
        BaseSocket::put_char('\n');
}

int SQLServer::BaseSocket::read(void* buf, int len) {
    int quantity = recv(sock_d, buf, len, 0);
    while(quantity == 0)
        quantity = recv(sock_d, buf, len, 0);
    if(quantity == -1)
        throw SocketException(SocketException::RECV);
    return quantity;
}

char SQLServer::BaseSocket::get_char() {
    char c;
    int quantity = recv(sock_d, (char*) &c, sizeof(char), 0);
    while(quantity == 0)
        quantity = recv(sock_d, (char*) &c, sizeof(char), 0);
    if(quantity == -1)
        throw SocketException(SocketException::RECV);
    return c;
}

std::string SQLServer::BaseSocket::get_string() {
    char c = ' ';
    std::string s;
    while((c != '\n') && (c != EOF)) {
        c = BaseSocket::get_char();
        s.push_back(c);
    }
    return s;
}

int SQLServer::BaseSocket::get_descr() {
    return sock_d;
}

void SQLServer::BaseSocket::finish() {
    shutdown(sock_d, 2);
    close(sock_d);
}

SQLServer::UnClientSocket::UnClientSocket(const char* addr) {
    int sd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sd == -1)
        throw SocketException(SocketException::CREATE);
    sock_d = sd;
    sock_addr.sun_family = AF_UNIX;
    strcpy(sock_addr.sun_path, addr);
}

void SQLServer::UnClientSocket::connect_sock() {
    if(connect(sock_d, (struct sockaddr*) &sock_addr, sizeof(sock_addr)) == -1)
        throw SocketException(SocketException::CONNECT);
}

SQLServer::UnServerSocket::UnServerSocket(const char* addr) {
    int sd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sd == -1)
        throw SocketException(SocketException::CREATE);
    sock_d = sd;
    sock_addr.sun_family = AF_UNIX;
    strcpy(sock_addr.sun_path, addr);
    unlink(addr);
    bind_sock();
}

void SQLServer::UnServerSocket::bind_sock() {
    if(bind(sock_d, (struct sockaddr *) &sock_addr, sizeof(sock_addr)) == -1)
        throw SocketException(SocketException::BIND);
}

void SQLServer::UnServerSocket::listen_sock(int backlog) {
    if(listen(sock_d, backlog) == -1)
        throw SocketException(SocketException::LISTEN);
}

SQLServer::BaseSocket * SQLServer::UnServerSocket::accept_sock() {
    int new_sd = accept(sock_d, NULL, NULL);
    if(new_sd == -1)
        throw SocketException(SocketException::ACCEPT);
    BaseSocket* p = new BaseSocket(new_sd);
    return p;
}
