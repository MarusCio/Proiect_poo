//
// Created by cioba on 5/21/2025.
//

#ifndef MANAGER_JOC_H
#define MANAGER_JOC_H
#include <memory>

#include "Joc.h"
#include "Joc_Factory.h"
#include "Liars_Deck.h"
#include "Liars_Dice.h"


class Manager_Joc {
    std::unique_ptr<Joc> joc_crt;
    std::vector<std::unique_ptr<Joc>> jocuri_jucate;
    std::vector<std::unique_ptr<Player>> castigatori;

    void Incepe_Joc(int mod);
    static void Afis_Moduri();
    static void Avertismente(int x);
    void Afiseaza_Istoric() const;

public:
    void Porneste_Joc();
};





#endif //MANAGER_JOC_H
