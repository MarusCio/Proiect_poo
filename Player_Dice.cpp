//
// Created by cioba on 5/21/2025.
//

#include "Player_Dice.h"

Player_Dice::Player_Dice() = default;

Player_Dice::Player_Dice(const std::string &nume_, Zaruri &mana_, const int shot_): Player(nume_), shot(shot_) {
    mana = mana_.Extrage_Mana();
}

Player_Dice & Player_Dice::operator=(const Player_Dice &x) {
    Player::operator=(x);
    this->shot=x.shot;

    return *this;
}

Player_Dice::~Player_Dice() = default;

int Player_Dice::Numar_Zaruri_Egale(const std::string &valoare) const {
    int count = 0;
    for (const std::string& z : mana)
        if (z == valoare || z == "1")
            ++count;
    return count;
}

void Player_Dice::Reset_Zaruri() {
    mana=Zaruri::Extrage_Mana();
}

void Player_Dice::Bea_Shot() {
    shot++;
}

int Player_Dice::Get_Shot() const {
    return shot;
}

bool Player_Dice::Alive() const { return shot<2; }

std::unique_ptr<Player> Player_Dice::clone() const {
    return std::make_unique<Player_Dice>(*this);
}
