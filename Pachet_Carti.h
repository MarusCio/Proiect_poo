//
// Created by cioba on 4/7/2025.
//

#ifndef PACHET_CARTI_H
#define PACHET_CARTI_H
#include <iostream>
#include <vector>


class Pachet_Carti {
    std::vector<std::string>carti;
    inline static const std::vector<std::string> pachet={
        "A", "A", "A", "A", "A", "A",
        "K", "K", "K", "K", "K", "K",
        "Q", "Q", "Q", "Q", "Q", "Q",
        "JOKER", "JOKER"
    };

public:
    Pachet_Carti();
    Pachet_Carti(const Pachet_Carti &x);
    ~Pachet_Carti();

    Pachet_Carti& operator=(const Pachet_Carti &x);
    void Amesteca_Pachet();
    std::vector<std::string> Extrage_Mana();

    friend std::ostream& operator<<(std::ostream& os,const std::vector<std::string>& mana);
};

std::ostream& operator<<(std::ostream& os,const std::vector<std::string>& mana);

#endif //PACHET_CARTI_H
