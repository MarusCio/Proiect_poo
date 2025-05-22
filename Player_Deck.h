//
// Created by cioba on 5/21/2025.
//

#ifndef PLAYER_DECK_H
#define PLAYER_DECK_H
#include <algorithm>

#include "Exceptii_Joc.h"
#include "Player.h"


class Player_Deck : public Player {
    int sansa{};
    std::vector<int> carti_alese;
    int glont{};

public:

    Player_Deck();
    Player_Deck(const std::string& nume_, Pachet_Carti& mana_, int sansa_ = 0);
    Player_Deck(const Player_Deck& x);
    Player_Deck& operator=(const Player_Deck& x);
    ~Player_Deck() override;

    [[nodiscard]] const std::vector<int>& Get_Carti_Alese() const;
    void Index_Pt_Carti(const int nr, std::vector<int>& indecsi) const;
    void Mana_Ramasa(std::vector<int> indecsi);
    bool Alege_Carti();
    [[nodiscard]] bool Alive() const override;
    void Reset_Carti(Pachet_Carti& pachet);
    void Invarte_Revolver(int alt_glont);
    void Creste_Sansa_Glont();
    [[nodiscard]] int Get_Sansa() const;
    [[nodiscard]] bool Fara_Carti() const;
};




#endif //PLAYER_DECK_H
