//
// Created by cioba on 4/7/2025.
//

#ifndef JOC_H
#define JOC_H
#include <vector>

#include "Pachet_Carti.h"
#include "Player.h"
#include "Table.h"


class Joc {
        int dificultate;
        std::vector<Player> players;
        Table table;
        Pachet_Carti carti;

    public:
        Joc(const std::vector<std::string>& nume_jucatori, Pachet_Carti& pachet);
        Joc(const Joc& x);
        Joc& operator=(const Joc& x);
        ~Joc();

        int Set_Dificultate();
        static void Reset_Revolver(const std::vector<Player*>& players);
        static bool Minte(Player& jucator_crt, Player& adversar, const Table& masa);
        static std::vector<Player*> Jucatori_Activi(std::vector<Player*>& jucatori_initiali, Pachet_Carti& carti);
        void Incepe_Joc();

        friend std::ostream& operator<<(std::ostream& os, const Joc& joc);

    };


#endif //JOC_H
