//
// Created by cioba on 4/7/2025.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

#include "Pachet_Carti.h"
#include "Zaruri.h"

class Player {
protected:
    std::string nume;
    std::vector<std::string> mana;
    //std::vector<int> zaruri;
    //int sansa{};
    //std::vector<int> carti_alese;
    //int glont{};
    //int shot{};

public:

    Player();

    explicit Player(const std::string &nume);

    Player(const Player& x);

    Player &operator=(const Player &x);

    virtual ~Player();

    [[nodiscard]] const std::vector<std::string>& Get_Mana() const;

    // [[nodiscard]] const std::vector<std::string>& Get_Zaruri() const {
    //     return mana;
    // }

    [[nodiscard]] const std::string& Get_Nume() const;

    [[nodiscard]] virtual bool Alive() const=0;

    [[nodiscard]] std::string Get_Padding(size_t lungime) const;

    virtual std::unique_ptr<Player> clone() const =0;


    friend std::ostream& operator<<(std::ostream& os,const Player& player);
};


#endif //PLAYER_H
