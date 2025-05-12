//
// Created by cioba on 4/7/2025.
//

#ifndef TABLE_H
#define TABLE_H
#include <ostream>


class Table{
    std::string table_name;
    int index_table{};

public:
    Table();
    Table(const std::string& table_name, const int& index_table);
    Table(const Table& x);
    ~Table();

    Table& operator=(const Table& x);
    void Set_TableName();
    [[nodiscard]] int Table_Index() const;
    friend std::ostream& operator<<(std::ostream& os,const Table& table);
};

std::ostream& operator<<(std::ostream& os,const Table& table);


#endif //TABLE_H
