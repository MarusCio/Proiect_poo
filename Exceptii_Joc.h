//
// Created by cioba on 5/17/2025.
//

#ifndef EXCEPTII_JOC_H
#define EXCEPTII_JOC_H
#include <stdexcept>


class Exceptii_Joc : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class Eroare_Numar_Playeri : public Exceptii_Joc {
public:
    explicit  Eroare_Numar_Playeri(const std::string& msg);
};

class Eroare_Index_Invalid : public Exceptii_Joc {
public:
    explicit Eroare_Index_Invalid(const std::string& msg);
};

class Eroare_Declarare_Minciuna : public Exceptii_Joc {
public:
    explicit Eroare_Declarare_Minciuna(const std::string& msg);
};

class Eroare_Inceput_Liars_Dice : public Exceptii_Joc {
public:
    explicit Eroare_Inceput_Liars_Dice(const std::string& msg);
};

class Eroare_Comanda_LD_Invalida: public Exceptii_Joc {
public:
    explicit Eroare_Comanda_LD_Invalida(const std::string& msg);
};

#endif //EXCEPTII_JOC_H
