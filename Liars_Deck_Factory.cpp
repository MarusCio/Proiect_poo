//
// Created by cioba on 5/26/2025.
//

#include "Liars_Deck_Factory.h"

std::unique_ptr<Joc> Liars_Deck_Factory::Creaza_joc() {
    Pachet_Carti pachet;
    pachet.Amesteca_Pachet();
    return std::make_unique<Liars_Deck>(std::vector<std::string>{"Marius", "Ivan", "Aleksei", "Dimitri"} ,pachet);
}
