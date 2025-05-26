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

    void Incepe_Joc(const std::unique_ptr<Joc_Factory>& f);
    void Afiseaza_Istoric() const;
    static void Afis_Moduri();
    static void Avertismente(int x);

public:
    void Porneste_Joc();
};




#endif //MANAGER_JOC_H
