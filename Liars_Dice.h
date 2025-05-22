//
// Created by cioba on 5/5/2025.
//

#ifndef LIARS_DICE_H
#define LIARS_DICE_H
#include <memory>
#include <string>

#include "Joc.h"
#include "Liars_Deck.h"
#include "Zaruri.h"
#include "convertire_string.h"
#include "Exceptii_Joc.h"
#include "Player_Dice.h"


class Liars_Dice: public Joc {
    //std::vector<Player> players;
    Zaruri zaruri;

public:
    Liars_Dice(const std::vector<std::string>& nume_jucatori_, Zaruri& mana_zaruri);
    Liars_Dice(const Liars_Dice& x);
    Liars_Dice& operator=(const Liars_Dice& x_);
    ~Liars_Dice() override;
    [[nodiscard]] std::unique_ptr<Joc> clone() const override;

    // static bool Este_Numar(const std::string& s) {
    //     return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
    // }

    static std::vector<Player_Dice*> Jucatori_Activi(std::vector<Player_Dice*>& jucatori_initiali);
    static bool Licitatie_Valida(int valoare_veche,int numar_vechi,int valoare_noua,int numar_nou);
    void Joaca_Joc() override;
    [[nodiscard]] std::string Get_Nume_Joc() const override;
    [[nodiscard]] int Get_Lungime_Max() const override;
    friend std::ostream& operator<<(std::ostream& os, const Liars_Dice& joc);
};



#endif //LIARS_DICE_H
