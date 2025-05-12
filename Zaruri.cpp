//
// Created by cioba on 5/5/2025.
//

#include "Zaruri.h"

Zaruri::Zaruri() = default;

Zaruri::Zaruri(std::vector<std::string> zaruri): zaruri{zaruri} {}

Zaruri::Zaruri(const Zaruri &x): zaruri{x.zaruri} {}

Zaruri::~Zaruri() = default;

Zaruri & Zaruri::operator=(const Zaruri &x) {
    zaruri = x.zaruri;
    return *this;
}

std::vector<std::string> Zaruri::Extrage_Mana() {
    std::vector<std::string> mana;
    for(int i=0;i<5;i++) {
        int zar = rand() % 6 + 1;
        mana.push_back(std::to_string(zar));
    }
    return mana;
}
