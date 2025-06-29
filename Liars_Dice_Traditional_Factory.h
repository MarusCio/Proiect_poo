//
// Created by cioba on 6/15/2025.
//

#ifndef LIARS_DICE_TRADITIONAL_FACTORY_H
#define LIARS_DICE_TRADITIONAL_FACTORY_H
#include "Joc_Factory.h"
#include "Liars_Dice_Traditional.h"

class Liars_Dice_Traditional_Factory:public Joc_Factory{
public:
    std::unique_ptr<Joc> Creeaza_joc() override;
};


#endif //LIARS_DICE_TRADITIONAL_FACTORY_H
