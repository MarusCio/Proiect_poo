//
// Created by cioba on 5/5/2025.
//

#ifndef LIARS_DICE_H
#define LIARS_DICE_H
#include <string>
#include <sstream>

#include "Joc.h"
#include "Liars_Deck.h"
#include "Zaruri.h"

template<typename T>
std::string To_String(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

class Liars_Dice: public Joc {
    //std::vector<Player> players;
    Zaruri zaruri;

public:

    Liars_Dice(const std::vector<std::string>& nume_jucatori_, Zaruri& mana_zaruri);
    Liars_Dice(const Liars_Dice& x);
    Liars_Dice& operator=(const Liars_Dice& x_);
    ~Liars_Dice() override;

    static std::string Get_To_String(const int x);

    bool Este_Numar(const std::string& s);
    static std::vector<Player*> Jucatori_Activi(std::vector<Player*>& jucatori_initiali);
    void Incepe_Joc() override;
    [[nodiscard]] int Get_Lungime_Max() const override;
    friend std::ostream& operator<<(std::ostream& os, const Liars_Dice& joc);
};

std::ostream& operator<<(std::ostream& os, const Liars_Dice& joc);


#endif //LIARS_DICE_H
