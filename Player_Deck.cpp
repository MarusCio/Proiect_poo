//
// Created by cioba on 5/21/2025.
//

#include "Player_Deck.h"
#include <limits>

Player_Deck::Player_Deck() = default;

Player_Deck::Player_Deck(const std::string &nume_, Pachet_Carti &mana_, const int sansa_): Player(nume_), sansa(sansa_) {
    mana = mana_.Extrage_Mana();
    glont = rand() % 6 + 1;
}

Player_Deck::Player_Deck(const Player_Deck &x): Player(x), sansa{x.sansa}, carti_alese{x.carti_alese}, glont{x.glont} {}

Player_Deck & Player_Deck::operator=(const Player_Deck &x) {
    Player::operator=(x);
    this->sansa=x.sansa;
    this->carti_alese=x.carti_alese;
    this->glont=x.glont;

    return *this;
}

Player_Deck::~Player_Deck() = default;

const std::vector<int> & Player_Deck::Get_Carti_Alese() const {
    return carti_alese;
}

void Player_Deck::Index_Pt_Carti(const int nr, std::vector<int> &indecsi) const {
    bool ok = false;

    do {
        try {
            indecsi.clear();
            int index;
            if (nr == 1) std::cout << "Indexul cartii este: ";
            else std::cout << "Indexii celor " << nr << " carti sunt: ";

            for (int i=0;i<nr;i++) {
                std::cin >> index;

                if (index<1 || index>static_cast<int>(mana.size())) {
                    // std::cout<<"Vezi cate carti ai in mana! Numerotarea cartilor incepe de la 1"<<std::endl;
                    // std::cin>>index;
                    throw Eroare_Index_Invalid("Vezi cate carti ai in mana! Numerotarea cartilor incepe de la 1!\n");
                }
                indecsi.push_back(index - 1);
            }
            ok = true;
        } catch (const Eroare_Index_Invalid &e) {
            std::cout << "Eroare: " << e.what() << " Incearca din nou! ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!ok);
}

void Player_Deck::Mana_Ramasa(std::vector<int> indecsi) {
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

bool Player_Deck::Alege_Carti() {
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

bool Player_Deck::Alive() const {
    return sansa < glont;
}

void Player_Deck::Reset_Carti(Pachet_Carti &pachet) {
    mana = pachet.Extrage_Mana();
}

void Player_Deck::Invarte_Revolver(const int alt_glont) {
    glont=alt_glont;
}

void Player_Deck::Creste_Sansa_Glont() {
    sansa++;
}

int Player_Deck::Get_Sansa() const {
    return sansa;
}

bool Player_Deck::Fara_Carti() const {
    return mana.empty();
}

std::unique_ptr<Player> Player_Deck::clone() const {
    return std::make_unique<Player_Deck>(*this);
}
