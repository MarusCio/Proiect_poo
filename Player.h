//
// Created by cioba on 4/7/2025.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <algorithm>
#include <ostream>

#include "Pachet_Carti.h"


class Player {
    std::string nume;
    std::vector<std::string> mana;
    int sansa{};
    std::vector<int> carti_alese;
    int glont{};

public:
    Player();
    Player(const std::string &nume,Pachet_Carti& mana, const int viata);
    Player(const Player& x);
    Player &operator=(const Player &x);
    ~Player();

    void Index_Pt_Carti(int nr, std::vector<int>& indecsi) const;
    bool Alege_Carti();
    void Mana_Ramasa(std::vector<int> indecsi);
    [[nodiscard]] const std::vector<int>& Get_CartiAlese() const;
    [[nodiscard]] const std::vector<std::string>& Get_Carti() const;
    [[nodiscard]] bool Fara_Carti() const;
    void Reset_Carti(Pachet_Carti& pachet);
    void Creste_Sansa_Glont();
    [[nodiscard]] int Get_Sansa() const;
    [[nodiscard]] const std::string& Get_Nume() const;
    [[nodiscard]] bool Alive() const;
    void Invarte_Revolver(int alt_glont);
    [[nodiscard]] std::string Get_Padding(size_t lungime) const;


    friend std::ostream& operator<<(std::ostream& os,const Player& player);
};



#endif //PLAYER_H
