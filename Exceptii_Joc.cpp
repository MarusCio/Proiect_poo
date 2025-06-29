//
// Created by cioba on 5/17/2025.
//

#include "Exceptii_Joc.h"

Eroare_Numar_Playeri::Eroare_Numar_Playeri(const std::string &msg): Exceptii_Joc(std::string("Numar playeri: ") + msg) {}

Eroare_Index_Invalid::Eroare_Index_Invalid(const std::string &msg): Exceptii_Joc(std::string("Index invalid: ") + msg) {}

// Eroare_Declarare_Minciuna::Eroare_Declarare_Minciuna(const std::string &msg): Exceptii_Joc(std::string("Minciuna invalida: ") + msg) {}

Eroare_Inceput_Liars_Dice::Eroare_Inceput_Liars_Dice(const std::string &msg): Exceptii_Joc(std::string("Valori invalide: ") + msg) {}

Eroare_Comanda_LD_Invalida::Eroare_Comanda_LD_Invalida(const std::string &msg): Exceptii_Joc(std::string("Comanda invalida: ") + msg) {}


