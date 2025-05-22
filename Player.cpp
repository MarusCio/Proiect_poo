//
// Created by cioba on 4/7/2025.
//

#include "Player.h"
#include "Exceptii_Joc.h"
#include <algorithm>

Player::Player() = default;

Player::Player(const std::string &nume) {
    // Player(){
    this->nume=nume;
    // this->mana=mana;
}

Player::Player(const Player &x): nume{x.nume},mana{x.mana} {}

Player & Player::operator=(const Player &x) {
    this->nume=x.nume;
    this->mana=x.mana;
    return *this;
}

Player::~Player() = default;

const std::vector<std::string> & Player::Get_Mana() const {
    return mana;
}

const std::string & Player::Get_Nume() const {
    return nume;
}

std::string Player::Get_Padding(const size_t lungime) const {
    std::string nume_player = Get_Nume();
    if (nume_player.length() < lungime) {
        nume_player += std::string(lungime - nume.length(), ' ');
    }
    return nume_player;
}

std::ostream& operator<<(std::ostream& os,const Player& player) {
    os<<player.nume<<": ";
    for (size_t i = 0; i < player.mana.size(); i++) {
        os<<i+1<<")"<<player.mana[i]<<" ";
    }
    os<<std::endl;
    return os;
}