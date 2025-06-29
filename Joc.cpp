//
// Created by cioba on 4/7/2025.
//

#include "Joc.h"

#include "Exceptii_Joc.h"


Joc::Joc(): dificultate(0),castigator(nullptr) {}

Joc::Joc(const int dif,Player* castigator_): dificultate(dif),castigator(castigator_) {}

Joc::~Joc() =default;

int Joc::Set_Dificultate() {
    int nr_playeri;
    bool ok=false;
    do {
        try {
            std::cout<<"Numarul de rusi cu care vrei sa te joci este:";
            std::cin>>nr_playeri;
            if (nr_playeri<1 || nr_playeri>3) {
                throw Eroare_Numar_Playeri("Poti juca maxim cu 3 rusi si minim cu 1\n");
            }

            ok=true;
        }
        catch (const Eroare_Numar_Playeri& e){
            std::cout << "Eroare: " << e.what()<< " Incearca din nou! ";
        }

    }while (!ok);

    this->dificultate=nr_playeri;

    return dificultate;
}

void Joc::Set_Castigator(Player *j) {
    castigator = j;
}

Player * Joc::Get_Castigator() const {
    return castigator;
}


