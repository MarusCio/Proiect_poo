//
// Created by cioba on 5/5/2025.
//

#ifndef LIARS_DECK_H
#define LIARS_DECK_H
#include <vector>
#include <memory>
#include "Joc.h"
#include "Pachet_Carti.h"
#include "Player.h"
#include "Player_Deck.h"
#include "Table.h"


class Liars_Deck : public Joc {
    //int dificultate;
    //std::vector<Player> players;
    Table table;
    Pachet_Carti<std::string> carti;
    std::vector<std::unique_ptr<Player_Deck>> jucatori_initiali;

public:
    Liars_Deck(const std::vector<std::string>& nume_jucatori, Pachet_Carti<std::string>& pachet);
    Liars_Deck(const Liars_Deck& x);
    Liars_Deck& operator=(const Liars_Deck& x);
    ~Liars_Deck() override;
    [[nodiscard]] std::unique_ptr<Joc> clone() const override;

    static void Reset_Revolver(const std::vector<std::unique_ptr<Player_Deck>>& players_);
    [[nodiscard]] std::string Get_Nume_Joc() const override;
    static bool Minte(Player_Deck& jucator_crt, Player_Deck& adversar, const Table& masa);
    static std::vector<Player_Deck*> Jucatori_Activi(const std::vector<std::unique_ptr<Player_Deck>>& jucatori_initiali, Pachet_Carti<std::string>& carti_, int dif);

    // void Initializare_Jucatori() override {
    //     for (auto& j : jucatori_initiali) {
    //         j->Reset_Carti(carti);
    //     }
    //     Reset_Revolver(jucatori_initiali);
    // }

    void Initializare_Jucatori() override;
    void Ruleaza_Joc() override;
    [[nodiscard]] int Get_Lungime_Max() const override;
    friend std::ostream& operator<<(std::ostream& os, const Liars_Deck& joc);
};

std::ostream& operator<<(std::ostream& os, const Liars_Deck& joc);


#endif //LIARS_DECK_H
