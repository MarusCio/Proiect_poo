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

void Joc::Set_Castigator(Player *j) {
    castigator = j;
}

Player * Joc::Get_Castigator() const {
    return castigator;
}


