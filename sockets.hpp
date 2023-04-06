#ifndef _SOCKETS_HPP_
#define _SOCKETS_HPP_

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

namespace SQLServer {

    class SocketException { // класс исключений
        std::string error_message; // сообщение об ошибке

    public:
        enum error_code { // виды ошибок
            CREATE, // создание
            CONNECT, // связь
            SEND, // отправка
            RECV, // получение
            BIND, // привязка
            LISTEN, // приём
            ACCEPT, // разрешение на приём
        };

        SocketException(error_code code); // конструктор с параметром кода исключения
        ~SocketException() = default; // деструктор 

        void print_message(); // вывод сообщения
    };

    class BaseSocket { // интерфейс работы с сокетами
    protected:
        int sock_d; // дескриптор сокета
        struct sockaddr_un sock_addr; // структура сокета

    public:
        explicit BaseSocket(int sd = -1, const char* name = NULL); // конструктор сокета
        ~BaseSocket() = default; // деструктор

        void write(void* buf, int len); // запись сокета
        void put_char(int c); // запись символа в сокет
        void put_string(const char* str); // запись си-строки в сокет
        void put_string(const std::string& s); // запись строки в сокет

        int read(void* buf, int len); // чтение сокета

        char get_char(); // чтение символа
        std::string get_string(); // чтение строки
        int get_descr(); // получение дескриптора сокета

        void finish(); // конец работы с сокетом

    };

    class UnClientSocket: public BaseSocket { // клиент-сокет

    public:
        UnClientSocket(const char * addr); // конструктор с параметром адреса сокета
        ~UnClientSocket() = default; // деструктор

        void connect_sock();  // соединение
    };

    class UnServerSocket: public BaseSocket { // сервер-сокет

    public:
        UnServerSocket(const char* addr); // конструктор с параметром адреса сокета
        ~UnServerSocket() = default; // деструктор

        void bind_sock(); // привязка сокета
        void listen_sock(int backlog); // приём
        BaseSocket* accept_sock();

        virtual void on_accept(BaseSocket * pConn) = 0; // извлечение информации
    };

};

#endif
