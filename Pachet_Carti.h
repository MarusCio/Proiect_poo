//
// Created by cioba on 4/7/2025.
//

#ifndef PACHET_CARTI_H
#define PACHET_CARTI_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>


template <typename T>
class Pachet_Carti {
    std::vector<T>carti;
    inline static const std::vector<T> pachet={
        T("A"), T("A"), T("A"), T("A"), T("A"), T("A"),
        T("K"), T("K"), T("K"), T("K"), T("K"), T("K"),
        T("Q"), T("Q"), T("Q"), T("Q"), T("Q"), T("Q"),
        T("JOKER"), T("JOKER")
    };

public:
    Pachet_Carti() :
        carti{pachet} {}

    Pachet_Carti(const Pachet_Carti &x): carti{x.carti} {}

    ~Pachet_Carti() = default;

    Pachet_Carti<T>& operator=(const Pachet_Carti<T> &x) {
        carti = x.carti;
        return *this;
    }
    void Amesteca_Pachet() {
        carti= pachet;
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(carti.begin(), carti.end(), g);
    }

    std::vector<T> Extrage_Mana() {

        std::vector<T> mana;
        for(int i=0;i<5;i++) {
            mana.push_back(carti.back());
            carti.pop_back();
        }

        return mana;
    }

    friend std::ostream& operator<<(std::ostream& os,const std::vector<T>& mana) {
        os<<"Mana: ";
        for(const auto & i : mana) {
            os<<i<<" ";
        }
        return os;


    }

};

std::ostream& operator<<(std::ostream& os,const std::vector<std::string>& mana);

#endif //PACHET_CARTI_H
