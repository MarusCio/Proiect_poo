//
// Created by cioba on 4/7/2025.
//

#include "Player.h"

#include <algorithm>

Player::Player() = default;

Player::Player(const std::string &nume, Zaruri &mana, const int sansa) {
    // Player(){
    this->nume=nume;
    this->mana=mana.Extrage_Mana();
    this->sansa=sansa;
}

Player::Player(const std::string &nume, Pachet_Carti &mana, const int sansa) {
    // Player(){
    this->nume=nume;
    this->mana=mana.Extrage_Mana();
    this->sansa=sansa;
    this->carti_alese={};
    this->glont=rand()%6+1;
}

Player::Player(const Player &x): nume{x.nume},mana{x.mana},sansa{x.sansa},carti_alese{x.carti_alese},glont{x.glont} {}

Player & Player::operator=(const Player &x) {
    this->nume=x.nume;
    this->mana=x.mana;
    this->sansa=x.sansa;
    this->carti_alese=x.carti_alese;
    this->glont=x.glont;
    return *this;
}

Player::~Player() = default;

void Player::Index_Pt_Carti(const int nr, std::vector<int> &indecsi) const {
    int index;
    for (int i=0;i<nr;i++) {
        std::cin>>index;

        while (index < 1 || index>static_cast<int>(mana.size())) {
            std::cout<<"vezi cate carti ai in mana + numerotarea cartilor incepe de la 1"<<std::endl;
            std::cin>>index;
        }

        indecsi.push_back(index - 1);
    }
}

bool Player::Alege_Carti() {
    std::vector<int> indecsi;
    int nr_carti;

    if (mana.empty()) {
        return false;
    }

    std::cout<<nume<<", alege un numar de carti intre 1 si "<<std::min(3,static_cast<int>(mana.size()))<< ": ";
    std::cin>>nr_carti;

    while (nr_carti > static_cast<int>(mana.size())){
        std::cout<<"Mai ai doar "<<mana.size()<<" carti in mana"<<std::endl;
        std::cin>>nr_carti;
    }

    while (nr_carti <1 || nr_carti >3) {
        std::cout<<"Ai voie sa selectezi minim o carte si maxim "<< std::min(3, static_cast<int>(mana.size()))<<std::endl;
        std::cin>>nr_carti;
    }

    if (nr_carti==1){ std::cout<<"indexul cartii este: ";
        Index_Pt_Carti(nr_carti,indecsi);
        std::cout<<std::endl;
    }
    else {std::cout<<"indexul celor "<<nr_carti<<" carti este: ";
        Index_Pt_Carti(nr_carti,indecsi);
        std::cout<<std::endl;

    }

    carti_alese.clear();
    for (const int idx : indecsi) {
        if (mana[idx]=="A") carti_alese.push_back(1);
        else if (mana[idx]=="K") carti_alese.push_back(2);
        else if (mana[idx]=="Q") carti_alese.push_back(3);
        else carti_alese.push_back(4);
    }

    Mana_Ramasa(indecsi);

    return !mana.empty();
}

void Player::Mana_Ramasa(std::vector<int> indecsi) {
    std::sort(indecsi.rbegin(), indecsi.rend());

    for (int idx : indecsi) {
        mana.erase(mana.begin() + idx);
    }

    std::cout<<nume<<": ";
    for (size_t i=0;i<mana.size();i++) {
        std::cout<<i + 1<<")"<<mana[i]<< " ";
    }
    std::cout<<std::endl;
}

const std::vector<int> & Player::Get_CartiAlese() const {
    return carti_alese;
}

const std::vector<std::string> & Player::Get_Carti() const {
    return mana;
}

const std::vector<std::string> & Player::Get_Zaruri() const {
    return mana;
}

bool Player::Fara_Carti() const {
    return mana.empty();
}

void Player::Reset_Carti(Pachet_Carti &pachet) {
    mana = pachet.Extrage_Mana();
}

void Player::Reset_Zaruri() {
    mana=Zaruri::Extrage_Mana();
}

void Player::Creste_Sansa_Glont() {
    sansa++;
}

int Player::Get_Sansa() const {
    return sansa;
}

const std::string & Player::Get_Nume() const {
    return nume;
}

bool Player::Alive() const {
    return sansa < glont;
}

bool Player::Is_Alive() const { return sansa<2; }

void Player::Invarte_Revolver(int alt_glont) {
    glont=alt_glont;
}

int Player::Numar_Zaruri_Egale(const std::string &valoare) const {
    int count = 0;
    for (const std::string& z : mana)
        if (z == valoare || z == "1")
            ++count;
    return count;
}

std::string Player::Get_Padding(const size_t lungime) const {
    std::string nume_player = Get_Nume();
    if (nume_player.length() < lungime) {
        nume_player += std::string(lungime - nume.length(), ' ');
    }
    return nume_player;
}

std::ostream & operator<<(std::ostream &os, const Player &player) {
    os<<player.nume<<": ";
    for (size_t i = 0; i < player.mana.size(); i++) {
        os<<i+1<<")"<<player.mana[i]<<" ";
    }
    os<<std::endl;
    return os;
}
