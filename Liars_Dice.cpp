//
// Created by cioba on 5/5/2025.
//

#include "Liars_Dice.h"
#include "Exceptii_Joc.h"
#include <algorithm>

Liars_Dice::Liars_Dice(const std::vector<std::string> &nume_jucatori_, Zaruri &mana_zaruri): Joc(nume_jucatori_.size()), zaruri(mana_zaruri) {

    for (const auto& nume : nume_jucatori_) {
        players.emplace_back(nume, mana_zaruri, 0);
    }
}

Liars_Dice::Liars_Dice(const Liars_Dice &x): Joc(x.dificultate), zaruri{x.zaruri} {}

Liars_Dice & Liars_Dice::operator=(const Liars_Dice &x_) {

    this->zaruri=x_.zaruri;
    return *this;
}

Liars_Dice::~Liars_Dice() = default;

std::unique_ptr<Joc> Liars_Dice::clone() const {
    return std::make_unique<Liars_Dice>(*this);
}

std::string Liars_Dice::Get_To_String(const int x) {
    return To_String_Custom(x);
}

bool Liars_Dice::Este_Numar(const std::string &s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

std::vector<Player *> Liars_Dice::Jucatori_Activi(std::vector<Player *> &jucatori_initiali) {
    std::vector<Player*> activi;

    for (auto& jucator : jucatori_initiali) {
        if (jucator->Is_Alive()) {
            jucator->Reset_Zaruri();
            activi.push_back(jucator);
        }
    }

    return activi;
}

void Liars_Dice::Incepe_Joc() {
    int dif = Set_Dificultate();

    std::vector<Player*> jucatori_initiali;
    for (int i = 0; i <= dif; ++i)
        jucatori_initiali.push_back(&players[i]);

    while (true) {
        std::vector<Player*> jucatori_la_masa =Jucatori_Activi(jucatori_initiali);

        size_t idx = 0;

        if (jucatori_la_masa.size() == 1) {
            if (jucatori_la_masa[0]->Get_Nume()=="Marius") std::cout<<std::endl<<"Felicitari!🥂 Ai reusit sa bati rusii la jocul lor!"<<std::endl;
            else std::cout<<std::endl<<"Din pacate ai murit...🕊️💔😢😭"<<std::endl<<"Data viitoare nu mai intra in baruri dubioase din Rusia!"<<std::endl;
            break;
        }

        std::string numar = "0", valoare="0";
        bool runda_terminata = false;

        while (!runda_terminata) {
            Player* crt = jucatori_la_masa[idx];
            std::cout<<*this << std::endl;

            if (valoare == "0" && numar == "0") {
                std::cout <<crt->Get_Nume()<<", scrie un numar de zaruri si o valoare pentru acestea (numar de zaruri >=1, iar valoarea intre 1 si 6): ";
                int noua_valoare, nou_numar;
                std::cin >> nou_numar >> noua_valoare;

                if (noua_valoare < 1 || noua_valoare > 6 || nou_numar < 1) {
                    throw Eroare_Inceput_Liars_Dice("Ti-am zis mai sus... numarul de zaruri >=1, iar valoarea intre 1 si 6 ");
                    // std::cout << "Valori invalide. Incearca din nou: ";
                    // std::cin >> nou_numar >> noua_valoare;
                }

                numar = Get_To_String(nou_numar);
                valoare = Get_To_String(noua_valoare);

            }
            else {
                std::string comanda;
                std::cout<<crt->Get_Nume()<<", poti scrie (numar de zaruri si valoarea lor / liar / spot): ";
                std::cin >> comanda;

                if (comanda == "liar") {
                    Player* anterior = jucatori_la_masa[(idx + jucatori_la_masa.size() - 1) % jucatori_la_masa.size()];
                    int total = 0;
                    for (const auto* p : jucatori_la_masa)
                        total += p->Numar_Zaruri_Egale(valoare);

                    std::cout << "Total zaruri cu valoarea " << valoare << ": " << total << "\n";

                    if (total < std::stoi(numar)) {
                        std::cout <<anterior->Get_Nume()<<" a mintit! Pe masa este un numar de zaruri < "<<std::stoi(numar)<<". "<<anterior->Get_Nume()<<" trebuie sa dai un shot.\n";
                        anterior->Bea_Shot();
                    } else {
                        std::cout << crt->Get_Nume() << " a acuzat gresit! Pe masa este un numar de zaruri >= "<<std::stoi(numar)<<"\n";
                        crt->Bea_Shot();
                    }

                    runda_terminata = true;
                    break;
                }
                else if (comanda == "spot") {
                    int total = 0;
                    for (const auto* p : jucatori_la_masa)
                        total += p->Numar_Zaruri_Egale(valoare);

                    std::cout << "Verificare SPOT ON (necesar: " << numar << ", total: " << total << ")\n";

                    if (total == std::stoi(numar)) {
                        std::cout << "SPOT ON! Toti ceilalti trebuie sa dea un shot.\n";
                        for (auto* p : jucatori_la_masa)
                            if (p != crt)
                                p->Bea_Shot();
                    } else {
                        std::cout << "Spot gresit! " << crt->Get_Nume() << " bea un shot.\n";
                        crt->Bea_Shot();
                    }

                    runda_terminata = true;
                    break;
                }
                else if (Este_Numar(comanda)) {

                    int nou_numar;
                    int noua_valoare = std::stoi(comanda);

                    std::cin >> nou_numar;

                    int num_curent = std::stoi(numar);
                    int val_curenta = std::stoi(valoare);


                    bool valid = false;
                    if ((nou_numar > num_curent && noua_valoare == val_curenta) || (noua_valoare > val_curenta))
                        valid = true;

                    if (!valid) {
                        std::cout << "Licitatie invalida! Trebuie sa cresti numarul de zaruri sau valoarea acestora.\n";
                        continue;
                    }

                    numar = Get_To_String(nou_numar);
                    valoare = Get_To_String(noua_valoare);

                } else {
                    throw Eroare_Comanda_LD_Invalida("Scrie un numar de zaruri cu o anumita valoare, 'liar' sau 'spot'.\n");
                    // std::cout << "Comanda invalida! Scrie un numar de zaruri cu o anumita valoare, 'liar' sau 'spot'.\n";
                    continue;
                }
            }
            idx = (idx + 1) % jucatori_la_masa.size();


        }

        std::vector<Player*> de_eliminat;

        for (const auto& p : jucatori_la_masa) {
            if (!p->Is_Alive()) {
                de_eliminat.push_back(p);
            }

        }

        for (const auto* p : jucatori_la_masa) {
            if (!p->Is_Alive()) {
                std::cout <<"\n🥴🥴🥴 DUFFFFFFFFFFFFFFFFFFFFFF 🥴🥴🥴"<<std::endl<<p->Get_Nume()<< " a intrat in coma alcoolica si a murit!";
                std::cout<<std::endl;
            }
        }

        std::erase_if(jucatori_la_masa, [&](const auto& jucator) {
            return std::find(de_eliminat.begin(), de_eliminat.end(), jucator) != de_eliminat.end();
        });

        std::cout<<std::endl;
        std::cout<<"------------------"<<std::endl;
        std::cout<<"Runda s-a terminat"<<std::endl;
        std::cout<<"------------------"<<std::endl;

    }
}

int Liars_Dice::Get_Lungime_Max() const {
    int lungime_max = 0;
    for (int i = 0; i <= dificultate; ++i) {
        const Player& player = players[i];
        if (player.Is_Alive()) {
            lungime_max = std::max(lungime_max, static_cast<int>(player.Get_Nume().length()));
        }
    }
    return lungime_max;
}

std::ostream & operator<<(std::ostream &os, const Liars_Dice &joc) {
    os<<std::endl<<"---------------------"<<std::endl;

    const size_t max_nume_length = joc.Get_Lungime_Max();

    for (int i = 0; i <= joc.dificultate; ++i) {
        const Player& player = joc.players[i];
        if (player.Is_Alive()) {
            os << player.Get_Padding(max_nume_length)<<" | Shot-uri: "<<player.Get_Shot()<<"/2 | Zaruri: ";

            for (const auto& zar : player.Get_Zaruri()) {
                os << zar << " ";
            }
            os << std::endl;
        }
    }
    os << "---------------------" << std::endl;
    return os;
}
