#ifndef _DBMS_HPP_
#define _DBMS_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

namespace DataBase {

    extern const char * FILE_SIGNATURE; // специальная аббревиатура для файла бд
    const long max_name_len = 30; // максимальный размер имени

    class DataBaseException { // класс исключений
        std::string error_message; // сообщение

    public:
        enum DataBaseExceptionCode { // виды ошибок
            CREATE_TABLE, // создание
            OPEN_TABLE, // открытие
            OPEN_TABLE1 // открытие не бд
        };

        DataBaseException(DataBaseExceptionCode code); // контсруктор с параметром кода исключения
        ~DataBaseException(); // деструктор

        void print_message(); // печать сообщения об ошибке
    };

    enum FieldType {TEXT, LONG}; // тип поля

    struct FieldStruct { // структура поля таблицы
        char field_name[max_name_len]; // имя поля
        enum FieldType type; // тип поля
        long len; // длина поля
    };

    struct CellStruct { // структура ячейки таблицы
        enum FieldType type; // тип
        long value; // значение
        char* text_value; // текстовое значение
    };

    struct TableStruct { // структура таблицы
      unsigned num_fields; // количество полей
      struct FieldStruct* fields; // массив полей
    };

    class Table { // класс таблицы
        int fd; // файловый дескриптор таблицы
        char* path; // путь до таблицы

        struct FieldStruct * pfield_struct; // описание полей таблицы

        struct TableInfo { // информация о таблице
            long data_offset; // размер записи
            long num_field; // номер поля
            long num_record; // номер записи
            long first_offset; // смещение в записи
            long last_offset; // смещение в записи
        } tableInfo;

    public:
        Table(); // конструктор
        ~Table(); // деструктор

        int get_fd(); // получение дескриптора
        long get_data_offset(); // получение смещения
        long get_num_field(); // получение количества записей
        long get_num_record(); // получение количества записей
        long getfirst_offset(); // получение смещения
        enum FieldType get_field_type(long i); // получение типа поля
        char* get_field_name(long i); // получение имени поля
        long get_field_size(long i); // получение размера поля
        char* get_text_value(long num_rec, long num_field); // получение текстового значения
        long get_long_value(long num_rec, long num_field); // получение численного значения

        void create_table(const char* filename, struct TableStruct* t_struct); // создание таблицы
        void open_table(const char* filename); // открытие таблицы
        void delete_table(); // удаление таблицы
        void close_table(); // закрытие таблицы
        void print_table(); // печать таблицы

        void insert(struct CellStruct* pcell); // вставка записи в таблицу
        void remove(std::vector<long> nums); // удаление записи из таблицы
        void update(std::vector<long> nums, long num_field, struct CellStruct * pcell); // обновление таблицы
        void select(struct FieldStruct* fields, long fields_num, std::vector<long> nums); // выбор из таблицы
    };

}

#endif

