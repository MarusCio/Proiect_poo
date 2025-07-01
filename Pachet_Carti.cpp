//
// Created by cioba on 4/7/2025.
//

#include "Pachet_Carti.h"

#include <algorithm>
#include <random>

// Pachet_Carti::Pachet_Carti():
//     carti{pachet} {}
//
// Pachet_Carti::Pachet_Carti(const Pachet_Carti &x): carti{x.carti} {}
//
// Pachet_Carti::~Pachet_Carti() = default;
//
// Pachet_Carti & Pachet_Carti::operator=(const Pachet_Carti &x) {
//     carti = x.carti;
//     return *this;
// }
//
// void Pachet_Carti::Amesteca_Pachet() {
//     carti= pachet;
//     std::random_device rd;
//     std::mt19937 g(rd());
//     std::shuffle(carti.begin(), carti.end(), g);
// }
//
// std::vector<std::string> Pachet_Carti::Extrage_Mana() {
//     std::vector<std::string> mana;
//     for(int i=0;i<5;i++) {
//         mana.push_back(carti.back());
//         carti.pop_back();
//     }
//     return mana;
// }
//
// std::ostream & operator<<(std::ostream &os, const std::vector<std::string> &mana) {
//     os<<"Mana: ";
//     for(const auto & i : mana) {
//         std::cout<<i<<" ";
//     }
//     return os;
//
// }
