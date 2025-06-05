//
// Created by cioba on 5/26/2025.
//

#ifndef LIARS_DICE_FACTORY_H
#define LIARS_DICE_FACTORY_H
#include <memory>

#include "Joc.h"
#include "Joc_Factory.h"
#include "Liars_Dice.h"


class Liars_Dice_Factory:public Joc_Factory{
public:
    std::unique_ptr<Joc> Creaza_joc() override;
};



#endif //LIARS_DICE_FACTORY_H
