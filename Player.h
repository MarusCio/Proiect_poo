//
// Created by cioba on 4/7/2025.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "Pachet_Carti.h"
#include "Zaruri.h"

class Player {
    std::string nume;
    std::vector<std::string> mana;
    //std::vector<int> zaruri;
    int sansa{};
    std::vector<int> carti_alese;
    int glont{};
    int shot{};

public:

    Player();
    Player(const std::string &nume,Zaruri& mana, int shot);
    Player(const std::string &nume,Pachet_Carti& mana, int sansa);
    Player(const Player& x);
    Player &operator=(const Player &x);
    ~Player();

    void Index_Pt_Carti(int nr, std::vector<int>& indecsi) const;
    bool Alege_Carti();
    void Mana_Ramasa(std::vector<int> indecsi);
    [[nodiscard]] const std::vector<int>& Get_CartiAlese() const;
    [[nodiscard]] const std::vector<std::string>& Get_Carti() const;
    [[nodiscard]] const std::vector<std::string>& Get_Zaruri() const;
    [[nodiscard]] bool Fara_Carti() const;
    void Reset_Carti(Pachet_Carti& pachet);
    void Reset_Zaruri();
    void Creste_Sansa_Glont();
    [[nodiscard]] int Get_Sansa() const;
    [[nodiscard]] const std::string& Get_Nume() const;
    void Bea_Shot();
    [[nodiscard]] int Get_Shot() const;
    [[nodiscard]] bool Alive() const;
    bool Is_Alive() const;
    void Invarte_Revolver(int alt_glont);
    int Numar_Zaruri_Egale(const std::string& valoare) const;
    [[nodiscard]] std::string Get_Padding(size_t lungime) const;

    friend std::ostream& operator<<(std::ostream& os,const Player& player);
};

std::ostream& operator<<(std::ostream& os,const Player& player);


#endif //PLAYER_H
