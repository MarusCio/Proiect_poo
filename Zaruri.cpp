//
// Created by cioba on 5/5/2025.
//

#include "Zaruri.h"
#include "Liars_Dice.h"
#include "convertire_string.h"

Zaruri::Zaruri() = default;

Zaruri::Zaruri(const std::vector<std::string> &zaruri): zaruri{zaruri} {}

Zaruri::Zaruri(const Zaruri &x): zaruri{x.zaruri} {}

Zaruri::~Zaruri() = default;

Zaruri & Zaruri::operator=(const Zaruri &x) {
    zaruri = x.zaruri;
    return *this;
}

std::vector<std::string> Zaruri::Extrage_Mana() {
    std::vector<std::string> mana;
    for(int i=0;i<5;i++) {
        const int zar = rand() % 6 + 1;
        mana.push_back(Get_To_String2(zar));
    }
    return mana;
}
