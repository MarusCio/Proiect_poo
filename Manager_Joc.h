//
// Created by cioba on 5/21/2025.
//

#ifndef MANAGER_JOC_H
#define MANAGER_JOC_H
#include <memory>

#include "Joc.h"
#include "Joc_Factory.h"
#include "Liars_Deck.h"
#include "Liars_Deck_Factory.h"
#include "Liars_Dice.h"
#include "Liars_Dice_Factory.h"


class Manager_Joc {
    std::unique_ptr<Joc> joc_crt;
    std::vector<std::unique_ptr<Joc>> jocuri_jucate;
    std::vector<std::unique_ptr<Player>> castigatori;

    Manager_Joc();
    void Incepe_Joc(const std::unique_ptr<Joc_Factory>& f);
    static void Afis_Moduri();
    static void Avertismente(int x);
    static std::string Alege_Mod();
    static std::unique_ptr<Joc_Factory> Creeaza_Factory(const std::string& mod);
    void Afiseaza_Istoric() const;

protected:
    static Manager_Joc* instanta;

public:
    Manager_Joc(Manager_Joc &m) =delete;
    void operator=(const Manager_Joc &) = delete;
    static Manager_Joc *Get_Instanta();
    void Porneste_Joc();
};


#endif //MANAGER_JOC_H
