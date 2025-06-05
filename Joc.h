//
// Created by cioba on 4/7/2025.
//

#ifndef JOC_H
#define JOC_H
#include <memory>
#include <vector>

#include "Player.h"


class Joc {
public:
    void Joaca_Joc_Template_Method() {
        this->Set_Dificultate();
        this->Initializare_Jucatori();
        this->Ruleaza_Joc();
    }
protected:
    int dificultate;
    // std::vector<std::unique_ptr<Player>> players;
    Player* castigator;

public:
    Joc();
    Joc(int dif);
    virtual ~Joc();

    [[nodiscard]] virtual std::unique_ptr<Joc> clone() const = 0;
    // virtual void Joaca_Joc() =0;
    int Set_Dificultate();
    virtual void Ruleaza_Joc()=0;
    virtual void Initializare_Jucatori()=0;
    [[nodiscard]] virtual std::string Get_Nume_Joc() const = 0;
    [[nodiscard]] virtual int Get_Lungime_Max() const = 0;
    void Set_Castigator(Player* j);
    [[nodiscard]] Player* Get_Castigator() const;
};


#endif //JOC_H