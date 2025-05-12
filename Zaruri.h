//
// Created by cioba on 5/5/2025.
//

#ifndef ZARURI_H
#define ZARURI_H
#include <iostream>
#include <vector>
#include "convertire_string.h"


class Zaruri{
    std::vector<std::string>zaruri;

public:
    Zaruri();
    explicit Zaruri(const std::vector<std::string> &zaruri);
    Zaruri(const Zaruri &x);
    ~Zaruri();

    Zaruri& operator=(const Zaruri &x);
    static std::vector<std::string> Extrage_Mana();

    static std::string Get_To_String2(const int x) {
        return To_String_Custom(x);
    }

    friend std::ostream& operator<<(std::ostream& os,const std::vector<std::string>& mana);
};

#endif //ZARURI_H
