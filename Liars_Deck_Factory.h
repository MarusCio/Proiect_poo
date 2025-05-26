//
// Created by cioba on 5/26/2025.
//

#ifndef LIARS_DECK_FACTORY_H
#define LIARS_DECK_FACTORY_H
#include <memory>

#include "Joc.h"
#include "Joc_Factory.h"
#include "Liars_Deck.h"


class Liars_Deck_Factory:public Joc_Factory{
public:
    std::unique_ptr<Joc> Creaza_joc() override;
};



#endif //LIARS_DECK_FACTORY_H
