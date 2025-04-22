//
// Created by cioba on 4/7/2025.
//

#include "Joc.h"

Joc::Joc(const std::vector<std::string> &nume_jucatori, Pachet_Carti &pachet): dificultate(nume_jucatori.size()), carti(pachet) {
    for (const auto& nume : nume_jucatori) {
        players.emplace_back(nume, pachet, 0);
    }
}

Joc::Joc(const Joc &x): dificultate{x.dificultate}, players {x.players}, table {x.table}, carti {x.carti} {}

Joc & Joc::operator=(const Joc &x) {
    this->dificultate=x.dificultate;
    this->players=x.players;
    this->table=x.table;
    this->carti=x.carti;
    return *this;
}

Joc::~Joc() = default;

int Joc::Set_Dificultate() {
    int nr_playeri;
    std::cout<<"Numarul de rusi cu care vrei sa te joci este:";
    std::cin>>nr_playeri;
    std::cout<<std::endl;

    while (nr_playeri<1 || nr_playeri>3) {

        if (nr_playeri<1) {
            std::cout<<"Daca refuzi sa te joci, ei o sa te omoare oricum... Macar incearca!"<<std::endl;
        }

        else{
            std::cout<<"Poti juca maxim cu 3 rusi... NU ii enerva!"<<std::endl;
        }

        std::cout<<"Deci, numarul de rusi cu care vrei sa te joci este:";
        std::cin>>nr_playeri;
        std::cout<<std::endl;
    }

    this->dificultate=nr_playeri;

    return dificultate;
}

void Joc::Reset_Revolver(const std::vector<Player *> &players_) {
    for (const auto& player : players_)
        player->Invarte_Revolver(rand() % 6 + 1);
}

bool Joc::Minte(Player &jucator_crt, Player &adversar, const Table &masa) {
    int minciuna;

    std::cout<<adversar.Get_Nume()<<", daca crezi ca "<<jucator_crt.Get_Nume()<<" minte, scrie 1, altfel scrie 0: ";
    std::cin>>minciuna;

    while (minciuna!=0 && minciuna!=1) {std::cout<<"poti scrie doar 0 si 1 aici: "; std::cin>>minciuna;}
    if (minciuna==1) {
        std::vector<int> carti_jucator = jucator_crt.Get_CartiAlese();
        int masa_aleasa = masa.Table_Index();
        bool toate_corecte = std::all_of(carti_jucator.begin(), carti_jucator.end(),
                                         [masa_aleasa](int carte) { return carte == masa_aleasa || carte==4; });

        if (!toate_corecte) {
            std::cout<<jucator_crt.Get_Nume()<<" a mintit! "<<std::endl;
            jucator_crt.Creste_Sansa_Glont();
            std::cout<<jucator_crt.Get_Nume()<<": "<<jucator_crt.Get_Sansa()<<"/6"<<std::endl;
            std::cout<<std::endl;

            return true;
        }
        else {
            std::cout<<jucator_crt.Get_Nume()<<" nu a mintit! "<<std::endl;
            adversar.Creste_Sansa_Glont();
            std::cout<<adversar.Get_Nume()<<": "<<adversar.Get_Sansa()<<"/6"<<std::endl;
            std::cout<<std::endl;
            return true;

        }
    }
    std::cout<<std::endl;
    return false;
}

std::vector<Player *> Joc::Jucatori_Activi(std::vector<Player *> &jucatori_initiali, Pachet_Carti &carti_) {
    std::vector<Player*> activi;

    for (auto& jucator : jucatori_initiali) {
        if (jucator->Alive()) {
            jucator->Reset_Carti(carti_);
            activi.push_back(jucator);
        }
    }

    return activi;
}

void Joc::Incepe_Joc() {
    const int dif = Set_Dificultate();
    constexpr bool final_joc = true;

    std::vector<Player*> jucatori_initiali;
    for (int i = 0; i <= dif; ++i) {
        jucatori_initiali.push_back(&players[i]);
    }
    Reset_Revolver(jucatori_initiali);


    // std::cout << *this << std::endl;


    while (final_joc) {
        std::vector<Player*> jucatori_la_masa =Jucatori_Activi(jucatori_initiali, carti);

        if (jucatori_la_masa.size() == 1) {
            std::cout<<std::endl<<"==== CASTIGATORUL ESTE: "<<jucatori_la_masa[0]->Get_Nume()<<" ===="<<std::endl;
            if (jucatori_la_masa[0]->Get_Nume()=="Marius") std::cout<<"Felicitari!🥂 Ai reusit sa bati rusii la jocul lor!"<<std::endl;
            else std::cout<<"Din pacate ai murit...🕊️💔😢😭"<<std::endl<<"Data viitoare nu mai intra in baruri dubioase din Rusia!"<<std::endl;
            break;
        }

        carti.Amesteca_Pachet();
        table.Set_TableName();
        // std::cout << table << std::endl;

        std::cout<<*this << std::endl;
        // for (const auto& player : jucatori_la_masa) {
        //     std::cout << *player;
        // }

        size_t i = 0;

        while (!jucatori_la_masa.empty()) {
            if (i >= jucatori_la_masa.size()) i = 0;

            Player& jucator_curent = *jucatori_la_masa[i];
            Player& jucator_urmator = *jucatori_la_masa[(i + 1) % jucatori_la_masa.size()];

            if (!jucator_curent.Alege_Carti()) {
                std::cout << std::endl;

                if (!jucator_urmator.Get_Carti().empty() && Minte(jucator_curent, jucator_urmator, table)) {
                    break;
                }

                if (jucatori_la_masa.size() == 2) {
                    std::cout << jucator_curent.Get_Nume() << " Nu mai are carti! ";
                    jucator_urmator.Creste_Sansa_Glont();
                    std::cout << jucator_urmator.Get_Nume() << ": " << jucator_urmator.Get_Sansa() << "/6" << std::endl << std::endl;
                    break;
                }

                if (jucator_curent.Fara_Carti()) {
                    std::cout << jucator_curent.Get_Nume() << " a ramas fara carti si a scapat momentan..."<< std::endl;
                    jucatori_la_masa.erase(jucatori_la_masa.begin() + i);
                    continue;
                }

                ++i;
                continue;
            }

            if (!jucator_urmator.Get_Carti().empty() && Minte(jucator_curent, jucator_urmator, table)) {
                break;
            }

            std::vector<Player*> de_eliminat;

            for (const auto& p : jucatori_la_masa) {
                if (!p->Alive()) {
                    // std::cout << "\n🔥🔥🔥 BOOOOOOOM 🔥🔥🔥\n" << p->Get_Nume() << " a murit!" << std::endl;
                    de_eliminat.push_back(p);
                }
                else if (p->Fara_Carti()) {
                    // std::cout << p->Get_Nume() << "A ramas fara carti si a scapat momentan..." << std::endl;
                    de_eliminat.push_back(p);
                }
            }

            std::erase_if(jucatori_la_masa, [&](const auto& jucator) {
            return std::find(de_eliminat.begin(), de_eliminat.end(), jucator) != de_eliminat.end();
        });

            if (jucatori_la_masa.size() <= 1) {
                break;
            }

            ++i;
            if (i >= jucatori_la_masa.size()) i = 0;
        }

        for (const auto* p : jucatori_la_masa) {
            if (!p->Alive()) {
                std::cout <<"🔥🔥🔥 BOOOOOO0000000000000000000000000000000000000000OM 🔥🔥🔥"<<std::endl<<p->Get_Nume()<< " a murit!"<< std::endl;
                std::cout<<std::endl;
            }
        }

        std::cout<<"------------------"<<std::endl;
        std::cout<<"Runda s-a terminat"<<std::endl;
        std::cout<<"------------------"<<std::endl;
        // std::cout <<"Se genereaza o masa noua"<< std::endl;

    }
}

int Joc::Get_Lungime_Max() const {
    int lungime_max = 0;
    for (int i = 0; i <= dificultate; ++i) {
        const Player& player = players[i];
        if (player.Alive() && !player.Fara_Carti()) {
            lungime_max = std::max(lungime_max, static_cast<int>(player.Get_Nume().length()));
        }
    }
    return lungime_max;
}

std::ostream& operator<<(std::ostream& os, const Joc& joc) {
    os<<std::endl<<"---------------------"<<std::endl;
    os << joc.table << std::endl;

    const size_t max_nume_length = joc.Get_Lungime_Max();

    for (int i = 0; i <= joc.dificultate; ++i) {
        const Player& player = joc.players[i];
        if (player.Alive() && !player.Fara_Carti()) {
            os << player.Get_Padding(max_nume_length)<<" | Glont: "<<player.Get_Sansa()<<"/6 | Mana: ";

            for (const auto& carte : player.Get_Carti()) {
                os << carte << " ";
            }
            os << std::endl;
        }
    }

    os << "---------------------" << std::endl;
    return os;
}


