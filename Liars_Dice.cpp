//
// Created by cioba on 5/5/2025.
//

#include "Liars_Dice.h"
#include "Exceptii_Joc.h"
#include <algorithm>
#include <limits>


Liars_Dice::Liars_Dice(const std::vector<std::string> &nume_jucatori_, Zaruri &mana_zaruri): Joc(nume_jucatori_.size(),nullptr), zaruri(mana_zaruri) {
    for (const auto& nume : nume_jucatori_) {
        jucatori_initiali.emplace_back(std::make_unique<Player_Dice>(nume,mana_zaruri));
    }
}

Liars_Dice::Liars_Dice(const Liars_Dice &x): Joc(x.dificultate,x.castigator), zaruri{x.zaruri} {}

Liars_Dice & Liars_Dice::operator=(const Liars_Dice &x_) {

    this->zaruri=x_.zaruri;
    return *this;
}

Liars_Dice::~Liars_Dice() = default;

std::unique_ptr<Joc> Liars_Dice::clone() const {
    return std::make_unique<Liars_Dice>(*this);
}

std::vector<Player_Dice *> Liars_Dice::Jucatori_Activi(
    const std::vector<std::unique_ptr<Player_Dice>> &jucatori_initiali, const int dif) {
    std::vector<Player_Dice*> activi;

    for (auto i=0;i<=dif;i++) {
        auto& jucator = jucatori_initiali[i];
        if (jucator->Alive()) {
            jucator->Reset_Zaruri();
            activi.push_back(jucator.get());
        }
    }

    return activi;
}

bool Liars_Dice::Licitatie_Valida(const int valoare_veche, const int numar_vechi, const int valoare_noua,
    const int numar_nou) {
    if (valoare_noua < 1 || valoare_noua > 6 || numar_nou < 1) {
        return false;
    }

    return (valoare_noua > valoare_veche) ||
           (valoare_noua == valoare_veche && numar_nou > numar_vechi);
}

void Liars_Dice::Initializare_Jucatori() {
    for (int i=0;i<=dificultate;i++) {
        // std::cout<<jucatori_initiali[i]->Get_Nume()<<": ";
        jucatori_initiali[i]->Reset_Zaruri();
    }
}

int Liars_Dice::Get_Numar_Zaruri_Egale(const Player_Dice *p, const std::string &val) const {
    return p->Numar_Zaruri_Egale(val);
}

void Liars_Dice::Ruleaza_Joc() {
        // const int dif = Set_Dificultate();

        // std::vector<Player_Dice*> jucatori_initiali;
        // for (int i=0;i<=dif;i++) {
        //     if (auto* dice_player = dynamic_cast<Player_Dice*>(players[i].get())) {
        //         jucatori_initiali.push_back(dice_player);
        //     }
        // }
        static const std::string eu = "Marius";

        while (true) {
            std::vector<Player_Dice *> jucatori_la_masa = Jucatori_Activi(jucatori_initiali, dificultate);

            // for (const auto* jucator : jucatori_la_masa) {
            //     std::cout << jucator->Get_Nume() << " ";
            // }

            size_t idx = 0;


            if (jucatori_la_masa.size() == 1) {
                Player *castigator_joc = jucatori_la_masa[0];
                Set_Castigator(castigator_joc);
                if (jucatori_la_masa[0]->Get_Nume() == eu)
                    std::cout << std::endl << "Felicitari!🥂 Ai reusit sa bati rusii la jocul lor!" << std::endl;
                else
                    std::cout << std::endl << "Din pacate ai murit...🕊💔😢😭" << std::endl <<
                            "Data viitoare nu mai intra in baruri dubioase din Rusia!" << std::endl;
                break;
            }

            std::string valoare = "0", numar = "0";
            bool runda_terminata = false;

            while (!runda_terminata) {
                Player_Dice *crt = jucatori_la_masa[idx];
                std::cout << *this << std::endl;

                if (valoare == "0" && numar == "0") {
                    bool ok = false;

                    do {
                        try {
                            std::cout << crt->Get_Nume() <<", scrie un numar de zaruri si o valoare pentru acestea (numar de zaruri >=1, iar valoarea intre 1 si 6): ";
                            int noua_valoare, nou_numar;
                            std::cin >> nou_numar >> noua_valoare;

                            if (noua_valoare < 1 || noua_valoare > 6 || nou_numar < 1) {
                                throw Eroare_Inceput_Liars_Dice("Ti-am zis mai sus... numarul de zaruri >=1, iar valoarea intre 1 si 6 ");
                                // std::cout << "Valori invalide. Incearca din nou: ";
                                // std::cin >> nou_numar >> noua_valoare;
                            }

                            numar = To_String_Custom(nou_numar);
                            valoare = To_String_Custom(noua_valoare);

                            ok = true;
                        } catch (const Eroare_Inceput_Liars_Dice &e) {
                            std::cout << "Eroare: " << e.what() << "\n";
                        }
                    } while (!ok);
                }

                else {
                    std::string comanda;
                    bool comanda_ok = false;

                    do {
                        std::cout << crt->Get_Nume() << ", poti scrie (licitatie / liar / spot): ";
                        std::cin >> comanda;

                        if (comanda == "liar") {
                            Player_Dice *anterior = jucatori_la_masa[
                                (idx + jucatori_la_masa.size() - 1) % jucatori_la_masa.size()];
                            int total = 0;
                            for (const auto *p: jucatori_la_masa)
                                total += p->Numar_Zaruri_Egale(valoare);

                            std::cout << "Total zaruri cu valoarea " << valoare << ": " << total << "\n";

                            if (total < std::stoi(numar)) {
                                std::cout << anterior->Get_Nume() << " a mintit! Pe masa este un numar de zaruri < "<< std::stoi(numar) << ". " << anterior->Get_Nume() <<" trebuie sa dai un shot.\n";
                                anterior->Bea_Shot();
                            }
                            else {
                                std::cout << crt->Get_Nume() <<" a acuzat gresit! Pe masa este un numar de zaruri >= " << std::stoi(numar)<< "\n";
                                crt->Bea_Shot();
                            }

                            runda_terminata = true;
                            comanda_ok = true;
                            // break;
                        }
                        else if (comanda == "spot") {
                            int total = 0;
                            for (const auto *p: jucatori_la_masa)
                                total += Get_Numar_Zaruri_Egale(p, valoare);

                            std::cout << "Verificare SPOT ON (necesar: " << numar << ", total: " << total << ")\n";

                            if (total == std::stoi(numar)) {
                                std::cout << "SPOT ON! Toti ceilalti trebuie sa dea un shot.\n";
                                for (auto *p: jucatori_la_masa)
                                    if (p != crt)
                                        p->Bea_Shot();
                            } else {
                                std::cout << "Spot gresit! " << crt->Get_Nume() << " bea un shot.\n";
                                crt->Bea_Shot();
                            }

                            runda_terminata = true;
                            comanda_ok = true;
                            // break;
                        }

                        else if (comanda == "licitatie") {
                            bool valori_corecte=false;

                            do {
                                int nou_numar;
                                int noua_valoare;

                                std::cout << "Numarul de zaruri: ";
                                std::cin >> nou_numar;
                                std::cout << "Valoarea zarurilor: ";
                                std::cin >> noua_valoare;

                                const int nr_curent = std::stoi(numar);
                                const int val_curenta = std::stoi(valoare);

                                if (!Licitatie_Valida(val_curenta, nr_curent, noua_valoare, nou_numar)) {
                                    std::cout <<"\nLicitatie invalida! Trebuie sa cresti numarul de zaruri sau valoarea acestora.\n";
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                }
                                else {
                                    numar = To_String_Custom(nou_numar);
                                    valoare = To_String_Custom(noua_valoare);
                                    valori_corecte = true;
                                    comanda_ok = true;
                                }
                            }while (!valori_corecte);
                        }
                        else {
                            std::cout << "Comanda invalida: Comenzile sunt: 'licitatie', 'liar' sau 'spot'.\n";
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                    } while (!comanda_ok);
                }
                idx = (idx + 1) % jucatori_la_masa.size();
            }

            std::vector<Player *> de_eliminat;

            for (const auto &p: jucatori_la_masa) {
                if (!p->Alive()) {
                    de_eliminat.push_back(p);
                }
            }

            for (const auto *p: jucatori_la_masa) {
                if (!p->Alive()) {
                    std::cout << "\n🥴🥴🥴 DUFFFFFFFFFFFFFFFFFFFFFF 🥴🥴🥴" << std::endl << p->Get_Nume() <<
                            " a intrat in coma alcoolica si a murit!";
                    std::cout << std::endl;
                }
            }

            std::erase_if(jucatori_la_masa, [&](const auto &jucator) {
                return std::find(de_eliminat.begin(), de_eliminat.end(), jucator) != de_eliminat.end();
            });

            std::cout << std::endl;
            std::cout << "------------------" << std::endl;
            std::cout << "Runda s-a terminat" << std::endl;
            std::cout << "------------------" << std::endl;
        }
    }

std::string Liars_Dice::Get_Nume_Joc() const {return "LIAR'S DICE CLASIC";}

int Liars_Dice::Get_Lungime_Max() const {
    int lungime_max = 0;
    for (int i = 0; i <= dificultate; ++i) {
        const auto& player = jucatori_initiali[i];
        if (player->Alive()) {
            lungime_max = std::max(lungime_max, static_cast<int>(player->Get_Nume().length()));
        }
    }
    return lungime_max;
}

std::ostream & operator<<(std::ostream &os, const Liars_Dice &joc) {
    os<<std::endl<<"---------------------"<<std::endl;

    const size_t max_nume_length = joc.Get_Lungime_Max();

    for (int i = 0; i <= joc.dificultate; ++i) {
        // const Player& player = joc.players[i];
        const auto* player_dice = joc.jucatori_initiali[i].get();
        if (player_dice->Alive()) {
            os << player_dice->Get_Padding(max_nume_length)<<" | Shot-uri: "<<player_dice->Get_Shot()<<"/2 | Zaruri: ";

            for (const auto& zar : player_dice->Get_Mana()) {
                os << zar << " ";
            }
            os << std::endl;
        }
    }
    os << "---------------------" << std::endl;
    return os;
}
