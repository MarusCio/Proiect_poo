//
// Created by cioba on 6/14/2025.
//

#include "Liars_Dice_Traditional.h"

Liars_Dice_Traditional::Liars_Dice_Traditional(const std::vector<std::string> &nume_jucatori_, Zaruri &mana_zaruri): Liars_Dice(nume_jucatori_,mana_zaruri) {}

std::unique_ptr<Joc> Liars_Dice_Traditional::clone() const {
    return std::make_unique<Liars_Dice_Traditional>(*this);
}

int Liars_Dice_Traditional::Numar_Zaruri_Egale_Traditional(const std::vector<std::string> &mana, const std::string &valoare) {
    int count = 0;
    for (const std::string& z : mana)
        if (z == valoare)
            ++count;
    return count;
}

int Liars_Dice_Traditional::Get_Numar_Zaruri_Egale(const Player_Dice *p, const std::string &val) const {
    return Numar_Zaruri_Egale_Traditional(p->Get_Mana(),val);
}

std::string Liars_Dice_Traditional::Get_Nume_Joc() const {return "LIAR'S DICE TRADITIONAL";}
