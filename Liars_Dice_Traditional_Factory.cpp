//
// Created by cioba on 6/15/2025.
//

#include "Liars_Dice_Traditional_Factory.h"

std::unique_ptr<Joc> Liars_Dice_Traditional_Factory::Creeaza_joc() {
    Zaruri zaruri;
    return std::make_unique<Liars_Dice_Traditional>(std::vector<std::string>{"Marius", "Ivan", "Aleksei", "Dimitri"} ,zaruri);
}
