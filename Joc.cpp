//
// Created by cioba on 4/7/2025.
//

#include "Joc.h"

#include "Exceptii_Joc.h"


Joc::Joc(): dificultate(0) {}

Joc::Joc(int dif): dificultate(dif) {}

Joc::~Joc() {}

int Joc::Set_Dificultate() {
    int nr_playeri;
    std::cout<<"Numarul de rusi cu care vrei sa te joci este:";
    std::cin>>nr_playeri;
    std::cout<<std::endl;

    if (nr_playeri<1 || nr_playeri>3) {
        throw Eroare_Numar_Playeri("Poti juca maxim cu 3 rusi si minim cu 1. Scrie un numar intre 1 si 3");
        // if (nr_playeri<1) {
        //     std::cout<<"Daca refuzi sa te joci te omoara oricum..."<<std::endl;
        //     std::cout<<"Deci numarul de rusi cu care vrei sa te joci este:";
        //     std::cin>>nr_playeri;
        //     std::cout<<std::endl;
        // }
        // else{
        //     std::cout<<"Poti juca maxim cu 3 rusii... NU ii enerva!"<<std::endl;
        //     std::cout<<"Deci numarul de rusi cu care vrei sa te joci este:";
        //     std::cin>>nr_playeri;
        //     std::cout<<std::endl;
        // }
    }

    this->dificultate=nr_playeri;

    return dificultate;
}

int Joc::Get_Lungime_Max() const {
    int lungime_max = 0;
    for (int i = 0; i <= dificultate; ++i) {
        const Player& player = players[i];
        if (player.Alive() && !player.Fara_Carti()) {
            lungime_max = std::max(lungime_max, static_cast<int>(player.Get_Nume().length()));
        }
    }
    return lungime_max;
}
