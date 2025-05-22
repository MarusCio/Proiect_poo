//
// Created by cioba on 5/5/2025.
//


#include "Liars_Deck.h"
#include "Exceptii_Joc.h"
#include <algorithm>


Liars_Deck::Liars_Deck(const std::vector<std::string> &nume_jucatori, Pachet_Carti &pachet): Joc(nume_jucatori.size()), carti(pachet) {
    for (const auto& nume : nume_jucatori) {
        players.emplace_back(std::make_unique<Player_Deck>(nume,pachet,0));
    }
}

Liars_Deck::Liars_Deck(const Liars_Deck &x): Joc(x.dificultate), table {x.table}, carti {x.carti} {}

Liars_Deck & Liars_Deck::operator=(const Liars_Deck &x) {
    this->dificultate=x.dificultate;
    this->table=x.table;
    this->carti=x.carti;
    return *this;
}

Liars_Deck::~Liars_Deck() {
}

std::unique_ptr<Joc> Liars_Deck::clone() const {
    return std::make_unique<Liars_Deck>(*this);
}

void Liars_Deck::Reset_Revolver(const std::vector<Player_Deck *> &players_) {
    for (const auto& player : players_)
        player->Invarte_Revolver(rand() % 6 + 1);
}

std::string Liars_Deck::Get_Nume_Joc() const {return "LIAR'S DECK";}

bool Liars_Deck::Minte(Player_Deck &jucator_crt, Player_Deck &adversar, const Table &masa) {
    std::string minciuna;

    std::cout<<adversar.Get_Nume()<<", daca crezi ca "<<jucator_crt.Get_Nume()<<" minte, scrie 1, altfel scrie 0: ";
    std::cin>>minciuna;

    if (minciuna!="0" && minciuna!="1") {
        throw Eroare_Declarare_Minciuna("Poti scrie doar 0 si 1 aici!");
        // std::cout<<"poti scrie doar 0 si 1 aici: "; std::cin>>minciuna;
    }

    if (minciuna=="1") {
        std::vector<int> carti_jucator = jucator_crt.Get_Carti_Alese();
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

std::vector<Player_Deck *> Liars_Deck::Jucatori_Activi(std::vector<Player_Deck *> &jucatori_initiali,
    Pachet_Carti &carti_) {
    std::vector<Player_Deck*> activi;

    for (auto& jucator : jucatori_initiali) {
        if (jucator->Alive()) {
            jucator->Reset_Carti(carti_);
            activi.push_back(jucator);
        }
    }

    return activi;
}

void Liars_Deck::Joaca_Joc() {
    const int dif = Set_Dificultate();
    constexpr bool final_joc = true;
    static const std::string eu="Marius";

    std::vector<Player_Deck*> jucatori_initiali;
    for (int i=0;i<=dif;i++) {
        if (auto* deck_player = dynamic_cast<Player_Deck*>(players[i].get())) {
            jucatori_initiali.push_back(deck_player);
        }
    }
    Reset_Revolver(jucatori_initiali);


    // std::cout << *this << std::endl;


    while (final_joc) {
        std::vector<Player_Deck*> jucatori_la_masa =Jucatori_Activi(jucatori_initiali, carti);

        if (jucatori_la_masa.size() == 1) {
            if (jucatori_la_masa[0]->Get_Nume()==eu) std::cout<<std::endl<<"Felicitari!🥂 Ai reusit sa bati rusii la jocul lor!"<<std::endl;
            else std::cout<<std::endl<<"Din pacate ai murit...🕊️💔😢😭"<<std::endl<<"Data viitoare nu mai intra in baruri dubioase din Rusia!"<<std::endl;
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

            Player_Deck& jucator_curent = *jucatori_la_masa[i];
            Player_Deck& jucator_urmator = *jucatori_la_masa[(i + 1) % jucatori_la_masa.size()];


            if (!jucator_curent.Alege_Carti()) {
                std::cout << std::endl;

                if (!jucator_urmator.Get_Mana().empty() && Minte(jucator_curent, jucator_urmator, table)) {
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

            if (!jucator_urmator.Get_Mana().empty() && Minte(jucator_curent, jucator_urmator, table)) {
                break;
            }

            std::vector<Player_Deck*> de_eliminat;

            for (const auto& p : jucatori_la_masa) {
                if (!p->Alive()) {
                    de_eliminat.push_back(p);
                }
                else if (p->Fara_Carti()) {
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
                std::cout <<"🔥🔥🔥 BOOOOOO0000000000000000000000000000000000000000OM 🔥🔥🔥"<<std::endl<<p->Get_Nume()<< " a murit!";
                std::cout<<std::endl;
            }
        }

        std::cout<<std::endl;
        std::cout<<"------------------"<<std::endl;
        std::cout<<"Runda s-a terminat"<<std::endl;
        std::cout<<"------------------"<<std::endl;
        // std::cout <<"Se genereaza o masa noua"<< std::endl;
    }
}

int Liars_Deck::Get_Lungime_Max() const {
    int lungime_max = 0;
    for (int i = 0; i <= dificultate; ++i) {
        const auto& player = players[i];
        if (const auto* p=dynamic_cast<Player_Deck*>(player.get())) {
            if (p->Alive() && !p->Fara_Carti()) {
                lungime_max = std::max(lungime_max, static_cast<int>(p->Get_Nume().length()));
            }
        }
    }
    return lungime_max;
}

std::ostream& operator<<(std::ostream& os, const Liars_Deck& joc) {
    os<<std::endl<<"---------------------"<<std::endl;
    os << joc.table << std::endl;


    const size_t max_nume_length = joc.Get_Lungime_Max();

    for (int i = 0; i <= joc.dificultate; ++i) {
        // const Player* player = joc.players[i].get();
        const auto* player_deck = dynamic_cast<const Player_Deck*>(joc.players[i].get());
        if (player_deck->Alive() && !player_deck->Fara_Carti()) {
            os << player_deck->Get_Padding(max_nume_length)<<" | Glont: "<<player_deck->Get_Sansa()<<"/6 | Mana: ";

            for (const auto& carte : player_deck->Get_Mana()) {
                os << carte << " ";
            }
            os << std::endl;
        }
    }
    os << "---------------------" << std::endl;
    return os;
}
