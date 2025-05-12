//
// Created by cioba on 5/5/2025.
//

#ifndef LIARS_DECK_H
#define LIARS_DECK_H
#include <vector>

#include "Joc.h"
#include "Pachet_Carti.h"
#include "Player.h"
#include "Table.h"


class Liars_Deck : public Joc {
        //int dificultate;
        //std::vector<Player> players;
        Table table;
        Pachet_Carti carti;

    public:

        Liars_Deck(const std::vector<std::string>& nume_jucatori, Pachet_Carti& pachet);
        Liars_Deck(const Liars_Deck& x);
        Liars_Deck& operator=(const Liars_Deck& x);
        ~Liars_Deck() override;

        static void Reset_Revolver(const std::vector<Player*>& players_);
        static bool Minte(Player& jucator_crt, Player& adversar, const Table& masa);
        static std::vector<Player*> Jucatori_Activi(std::vector<Player*>& jucatori_initiali, Pachet_Carti& carti_);
        void Incepe_Joc() override;
        friend std::ostream& operator<<(std::ostream& os, const Liars_Deck& joc);
    };

std::ostream& operator<<(std::ostream& os, const Liars_Deck& joc);


#endif //LIARS_DECK_H
