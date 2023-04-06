#include "dbms.hpp"

const char* DataBase::FILE_SIGNATURE = "\033\032DataFile\033\032~~~";

DataBase::Table::Table() {
    fd = 0;
}

DataBase::Table::~Table() {}

int DataBase::Table::get_fd() {
    return fd;
}

long DataBase::Table::get_data_offset() {
    return tableInfo.data_offset;
}

long DataBase::Table::get_num_field() {
    return tableInfo.num_field;
}

long DataBase::Table::get_num_record() {
    return tableInfo.num_record;
}

long DataBase::Table::getfirst_offset() {
    return tableInfo.first_offset;
}

enum DataBase::FieldType DataBase::Table::get_field_type(long i) {
    return pfield_struct[i].type;
}

char * DataBase::Table::get_field_name(long i) {
    return (char*) &pfield_struct[i].field_name;
}

long DataBase::Table::get_field_size(long i) {
    return pfield_struct[i].len;
}

char* DataBase::Table::get_text_value(long num_rec, long num_field) {
    struct FieldStruct* p = pfield_struct;
    long pos = 0;

    for(long i = 0; i < num_field; i++) {
        if(p->type == LONG) {
            pos += sizeof(long);
        }
        else {
            pos += sizeof(char) * p->len;
        }
        p++;
    }

    lseek(fd, tableInfo.first_offset + num_rec * tableInfo.data_offset + pos, SEEK_SET);

    char* buf;
    buf = new char [pfield_struct[num_field].len + 1];

    read(fd, buf, sizeof (char) * pfield_struct[num_field].len);
    buf[pfield_struct[num_field].len] = '\0';

    return buf;
}

long DataBase::Table::get_long_value(long num_rec, long num_field) {
    struct FieldStruct* p = pfield_struct;
    long pos = 0;

    for(long i = 0; i < num_field; i++) {
        if(p->type == LONG) {
            pos += sizeof(long);
        }
        else {
            pos += sizeof(char) * p->len;
        }
        p++;
    }

    lseek(fd, tableInfo.first_offset + num_rec * tableInfo.data_offset + pos, SEEK_SET);

    long k;
    read(fd, (char *)&k, sizeof(long));

    return k;
}

void DataBase::Table::create_table(const char* filename, struct TableStruct* t_struct) {

    fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if(fd == -1)
        throw DataBaseException(DataBaseException::CREATE_TABLE);

    path = new char[strlen(filename) + 1];
    strncpy(path, filename, strlen(filename) + 1);

    tableInfo.num_field = t_struct->num_fields;
    pfield_struct = new struct FieldStruct[tableInfo.num_field];

    memcpy(pfield_struct, t_struct->fields, sizeof(struct FieldStruct) * tableInfo.num_field);

    tableInfo.data_offset = 0;
    struct FieldStruct* p = t_struct->fields;

    for(long i = 0; i < t_struct->num_fields; i++) {
        if(p->type == LONG) {
            tableInfo.data_offset += sizeof(long);
        }
        else {
            tableInfo.data_offset += p->len * sizeof(char);
        }
        p++;
    }

    tableInfo.num_record = 0;
    tableInfo.first_offset = sizeof(char) * strlen(FILE_SIGNATURE) + sizeof(struct TableInfo) + t_struct->num_fields * sizeof(struct FieldStruct);
    tableInfo.last_offset = sizeof(char) * strlen(FILE_SIGNATURE) + sizeof(struct TableInfo) + t_struct->num_fields * sizeof(struct FieldStruct);

    write(fd, FILE_SIGNATURE, sizeof(char) * strlen(FILE_SIGNATURE));
    write(fd, (char*) &tableInfo, sizeof(struct TableInfo));
    write(fd, t_struct->fields, sizeof(struct FieldStruct) * t_struct->num_fields);
    lseek(fd, tableInfo.first_offset, SEEK_SET);
}

void DataBase::Table::open_table(const char* filename) {
    fd = open(filename, O_RDWR);
    if(fd == -1)
        throw DataBaseException(DataBaseException::OPEN_TABLE);

    path = new char [strlen(filename) + 1];
    strncpy(path, filename, strlen(filename) + 1);

    char* p = new char [sizeof(char) * strlen(FILE_SIGNATURE) + 1];
    read(fd, p, sizeof(char) * strlen(FILE_SIGNATURE));

    p[sizeof(char) * strlen(FILE_SIGNATURE)] = '\0';

    if(strcmp(p, FILE_SIGNATURE) != 0)
        throw DataBaseException(DataBaseException::OPEN_TABLE1);

    delete[] p;

    read(fd, (char*) &tableInfo, sizeof(struct TableInfo));
    pfield_struct = new struct FieldStruct [tableInfo.num_field];

    for(int i = 0; i < tableInfo.num_field; i++)
        read(fd, (char*) &pfield_struct[i], sizeof(struct FieldStruct));

    if (tableInfo.num_record != 0)
        lseek(fd, tableInfo.last_offset + tableInfo.data_offset, SEEK_SET);
}

void DataBase::Table::delete_table() {
    delete[] pfield_struct;
    unlink(path);
    delete[] path;
    fd = 0;
}

void DataBase::Table::close_table() {
    if ((fd != 0)  && (fd != -1)) {
        delete[] pfield_struct;
        delete[] path;
        close(fd);
    }
}

void DataBase::Table::print_table() {
    int len = 0;
    long k = LONG_MAX;

    while (k != 0) {
        len++;
        k = k / 10;
    }
    k += 2;

    struct FieldStruct* p = pfield_struct;
    for(long i = 0; i < tableInfo.num_field; i++) {
        std::cout << p->field_name;
        long j = strlen(p->field_name);

        if(p->type == TEXT) {
            while(j < p->len) {
                std::cout << ' ';
                j++;
            }
            std::cout << ' ';
        }
        else {
            while(j <= len) {
                std::cout << ' ';
                j++;
            }
            std::cout << ' ';
        }
        p++;
    }
    std::cout << std::endl;

    char* buf;
    long tmp;

    lseek(fd, tableInfo.first_offset, SEEK_SET);

    for(long i = 1; i <= tableInfo.num_record; i++) {
        p = pfield_struct;
        for(long j = 0; j < tableInfo.num_field; j++) {
            if(p->type == TEXT) {
                buf = new char [p->len + 1];
                read(fd, buf, sizeof(char) * p->len);
                buf[p->len] = '\0';

                std::cout << buf;
                k = strlen(buf);
                while(k <= strlen(p->field_name)) {
                    std::cout << ' ';
                    k++;
                }
                std::cout << ' ';
                delete[] buf;
            }
            else {
                read(fd, (long*) &tmp, sizeof(long));
                std::cout << tmp;

                if(tmp > 0) {
                    k = 0;
                }
                else {
                    k = 1;
                }
                if(tmp != 0) {
                    while(tmp != 0) {
                    k++;
                    tmp = tmp / 10;
                    }
                }
                else {
                    k = 1;
                }

                while((k <= strlen(p->field_name)) || (k <= len)) {
                    std::cout << ' ';
                    k++;
                }
                std::cout << ' ';
            }
            p++;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void DataBase::Table::insert(struct CellStruct* pcell) {
    struct CellStruct* p1 = pcell;
    struct FieldStruct* p2 = pfield_struct;
    char* buf;

    for(int i = 0; i < tableInfo.num_field; i++) {
        if(p1->type == TEXT) {
            buf = new char[p2->len + 1];
            strncpy(buf, p1->text_value, strlen(p1->text_value) + 1);

            for(int j = strlen(p1->text_value); j < p2->len; j++)
                buf[j] = ' ';

            write(fd, buf, sizeof(char) * p2->len);
            delete[] buf;
        }
        else {
            write(fd, &p1->value, sizeof(long));
        }
        p1++;
        p2++;
    }

    if (tableInfo.num_record != 0)
        tableInfo.last_offset += tableInfo.data_offset;
    tableInfo.num_record++;

    lseek(fd, sizeof(char) * strlen(FILE_SIGNATURE), SEEK_SET);
    write(fd, (char*) &tableInfo, sizeof(struct TableInfo));
    lseek(fd, tableInfo.last_offset + tableInfo.data_offset, SEEK_SET);
}

void DataBase::Table::remove(std::vector<long> nums) {
    char* buf;

    std::sort(nums.rbegin(), nums.rend(), std::greater<long>());

    buf = new char[sizeof(char) * tableInfo.data_offset];
    for(long i = nums.size() - 1; i >= 0; i--) {
        for(long j = nums[i] + 1; j <= tableInfo.num_record - 1; j++) {
            lseek(fd, tableInfo.first_offset + j * tableInfo.data_offset, SEEK_SET);
            read(fd, buf, sizeof(char) * tableInfo.data_offset);
            lseek(fd, tableInfo.first_offset + (j - 1) * tableInfo.data_offset, SEEK_SET);
            write(fd, buf, sizeof(char) * tableInfo.data_offset);
        }
        tableInfo.num_record--;
        tableInfo.last_offset -= tableInfo.data_offset;
    }

    delete[] buf;

    lseek(fd, sizeof(char) * strlen(FILE_SIGNATURE), SEEK_SET);
    write(fd, (char*) &tableInfo, sizeof(struct TableInfo));
    print_table();
    lseek(fd, tableInfo.last_offset + tableInfo.data_offset, SEEK_SET);
}

void DataBase::Table::update(std::vector<long> nums, long num_field, struct CellStruct* pcell) {
    char* buf;

    std::sort(nums.rbegin(), nums.rend(), std::greater<long>());
    struct FieldStruct* p = pfield_struct;
    long pos = 0;

    for(long i = 0; i < num_field; i++) {
        if(p->type == LONG) {
            pos += sizeof(long);
        }
        else {
            pos += sizeof(char) * p->len;
        }
        p++;
    }

    p = pfield_struct;
    p += num_field;

    if(p->type == LONG) {
        for(long i = 0; i < nums.size(); i++) {
            lseek(fd, tableInfo.first_offset + nums[i] * tableInfo.data_offset + pos, SEEK_SET);
            write(fd, (char *)&pcell[nums[i]].value, sizeof(long));
        }
    }
    else {
        buf = new char [p->len + 1];

        for(long i = 0; i < nums.size(); i++) {
            strncpy(buf, pcell[nums[i]].text_value, strlen(pcell[nums[i]].text_value) + 1);
            for(long j = strlen(buf); j < p->len; j++)
                buf[j] = ' ';
            lseek(fd, tableInfo.first_offset + nums[i] * tableInfo.data_offset + pos, SEEK_SET);
            write(fd, buf, sizeof(char) * p->len);
        }
        delete[] buf;
    }
    print_table();
    lseek(fd, tableInfo.last_offset + tableInfo.data_offset, SEEK_SET);
}

void DataBase::Table::select(struct FieldStruct* fields, long fields_num, std::vector<long> nums) {
    char* tmp = new char [7];
    tmp[0] = 'X';
    tmp[1] = 'X';
    tmp[2] = 'X';
    tmp[3] = 'X';
    tmp[4] = 'X';
    tmp[5] = 'X';
    tmp[6] = '\0';
    mkstemp(tmp);

    Table a;
    struct TableStruct t_struct;
    t_struct.num_fields = fields_num;
    t_struct.fields = fields;
    a.create_table(tmp, (struct TableStruct *)&t_struct);

    long k;

    std::sort(nums.rbegin(), nums.rend(), std::greater<long>());

    struct CellStruct* pole;
    pole = new struct CellStruct [fields_num];
    struct FieldStruct* p1 = pfield_struct;
    struct FieldStruct* p2 = fields;
    std::vector<long> offsets;
    std::vector<long> sizes;

    for(long i = 0; i < fields_num; i++) {
        k = 0;
        p1 = pfield_struct;
        for(long j = 0; j < tableInfo.num_field; j++) {
            if(strcmp(p1->field_name, p2->field_name) == 0) {
                pole[i].type = p1->type;
                if(p1->type == LONG) {
                    sizes.push_back(sizeof(long));
                }
                else {
                    sizes.push_back(sizeof(char) * p1->len);
                }
                break;
            }
            if(p1->type == LONG) {
                k += sizeof(long);
            }
            else {
                k += sizeof(char) * p1->len;
            }
            p1++;
        }
        offsets.push_back(k);
        p2++;
    }

    long first_offset = a.getfirst_offset();
    lseek(a.get_fd(), first_offset, SEEK_SET);

    for(long i = 0; i < nums.size(); i++) {
        for(long j = 0; j < fields_num; j++) {
            pole[j].text_value = NULL;
            lseek(fd, tableInfo.first_offset + nums[i] * tableInfo.data_offset + offsets[j], SEEK_SET);
            if(pole[j].type == TEXT) {
                pole[j].text_value = new char [sizes[j] + 1];
                read(fd, (char *)pole[j].text_value, sizes[j]);
                pole[j].text_value[sizes[j]] = '\0';
            }
            else {
                read(fd, (char *)&k, sizes[j]);
                pole[j].value = k;
            }
        }
        a.insert(pole);
        for(long j = 0; j < fields_num; j++) {
            if(pole[j].text_value != NULL) {
                delete[] pole[j].text_value;
            }
        }
    }

    delete[] pole;
    delete[] tmp;

    a.print_table();
    a.delete_table();
}

DataBase::DataBaseException::DataBaseException(DataBaseExceptionCode code) {
    switch(code) {
        case CREATE_TABLE:
            error_message = "dbms: error creating table with such name.";
            break;
        case OPEN_TABLE:
            error_message = "dbms: no such table";
            break;
        case OPEN_TABLE1:
            error_message = "dbms: file is not a table.";
            break;
    }
}

DataBase::DataBaseException::~ DataBaseException() {}

void DataBase::DataBaseException::print_message() {
    std::cout << error_message << std::endl << std::endl;
}

