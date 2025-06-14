//
// Created by cioba on 5/21/2025.
//

#ifndef PLAYER_DICE_H
#define PLAYER_DICE_H
#include "Player.h"


class Player_Dice : public Player {
    int shot{};

public:
    Player_Dice();
    Player_Dice(const std::string& nume_, Zaruri& mana_, int shot_ = 0);
    Player_Dice& operator=(const Player_Dice& x);
    ~Player_Dice() override;

    [[nodiscard]] int Numar_Zaruri_Egale(const std::string& valoare) const;
    [[nodiscard]] int Numar_Zaruri_Egale_Traditional(const std::string& valoare) const;
    void Reset_Zaruri();
    void Bea_Shot();
    [[nodiscard]] int Get_Shot() const;
    [[nodiscard]] bool Alive() const override;
    [[nodiscard]] std::unique_ptr<Player> clone() const override;
};



#endif //PLAYER_DICE_H
