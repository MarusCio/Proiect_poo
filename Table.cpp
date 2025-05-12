//
// Created by cioba on 4/7/2025.
//

#include "Table.h"

Table::Table() = default;

Table::Table(const std::string &table_name, const int &index_table) {
    this->table_name=table_name;
    this->index_table=index_table;
}

Table::Table(const Table &x): table_name{x.table_name}, index_table{x.index_table} {}

Table & Table::operator=(const Table &x) {
    table_name=x.table_name;
    index_table=x.index_table;
    return *this;
}

Table::~Table() = default;

void Table::Set_TableName() {
    int masa=rand()%3+1;
    if (masa==1) {this->table_name="ACE'S TABLE", index_table=1;}
    else if (masa==2) {this->table_name="KING'S TABLE",index_table=2;}
    else {this->table_name="QUEEN'S TABLE", index_table=3;}
}

int Table::Table_Index() const {
    return index_table;
}

std::ostream & operator<<(std::ostream &os, const Table &table) {
    os<<"Masa aleasa: "<<table.table_name<<" ";
    return os;
}
