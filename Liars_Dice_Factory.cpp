//
// Created by cioba on 5/26/2025.
//

#include "Liars_Dice_Factory.h"

std::unique_ptr<Joc> Liars_Dice_Factory::Creaza_joc() {
    Zaruri zaruri;
    return std::make_unique<Liars_Dice>(std::vector<std::string>{"Marius", "Ivan", "Aleksei", "Dimitri"} ,zaruri);
}
