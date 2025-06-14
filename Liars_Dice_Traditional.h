//
// Created by cioba on 6/14/2025.
//

#ifndef LIARS_DICE_TRADITIONAL_H
#define LIARS_DICE_TRADITIONAL_H
#include "Liars_Dice.h"


class Liars_Dice_Traditional: public Liars_Dice {

public:
    Liars_Dice_Traditional(const std::vector<std::string>& nume_jucatori_, Zaruri& mana_zaruri);

    [[nodiscard]] std::unique_ptr<Joc> clone() const override;
    int Get_Numar_Zaruri_Egale(const Player_Dice* p, const std::string& val) const override;
    [[nodiscard]] std::string Get_Nume_Joc() const override;
};



#endif //LIARS_DICE_TRADITIONAL_H
