//
// Created by cioba on 4/7/2025.
//

#ifndef JOC_H
#define JOC_H
#include <vector>

#include "Player.h"


class Joc {
protected:
    int dificultate;
    std::vector<Player> players;

public:
    Joc();
    Joc(int dif);
    virtual ~Joc();

    virtual void Incepe_Joc() =0;
    int Set_Dificultate();
    [[nodiscard]] virtual int Get_Lungime_Max() const;
};


#endif //JOC_H