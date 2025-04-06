#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <random>
#include <algorithm>

// #include "cmake-build-debug/_deps/sfml-src/src/SFML/Window/CursorImpl.hpp"
// #include <SFML/Graphics.hpp>
// #include <chrono>
// #include <thread>

class Pachet_Carti {
    std::vector<std::string>carti;
    inline static const std::vector<std::string> pachet={
        "A", "A", "A", "A", "A", "A",
        "K", "K", "K", "K", "K", "K",
        "Q", "Q", "Q", "Q", "Q", "Q",
        "JOKER", "JOKER"
    };

public:
    Pachet_Carti() :
        carti{pachet} {}

    Pachet_Carti(const Pachet_Carti &x): carti{x.carti} {}

    ~Pachet_Carti() = default;

    Pachet_Carti& operator=(const Pachet_Carti &x) {
        carti = x.carti;
        return *this;
    }

    void Amesteca_Pachet() {
        carti= pachet;
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(carti.begin(), carti.end(), g);
    }

    std::vector<std::string> Extrage_Mana() {
        std::vector<std::string> mana;
        for(int i=0;i<5;i++) {
            mana.push_back(carti.back());
            carti.pop_back();
        }
        return mana;
    }

    friend std::ostream& operator<<(std::ostream& os,const std::vector<std::string>& mana);

};

std::ostream& operator<<(std::ostream& os,const std::vector<std::string>& mana) {
    os<<"Mana: ";
    for(const auto & i : mana) {
        std::cout<<i<<" ";
    }
    return os;

}

class Player {
    std::string nume;
    std::vector<std::string> mana;
    int viata{};
    std::vector<int> carti_alese;
    int glont{};


public:

    Player()= default;

    Player(const std::string &nume,Pachet_Carti& mana, const int viata)
    {
    // Player(){
        this->nume=nume;
        this->mana=mana.Extrage_Mana();
        this->viata=viata;
        this->carti_alese={};
        this->glont=rand()%6+1;
    }

    Player(const Player& x): nume{x.nume},mana{x.mana},viata{x.viata},carti_alese{x.carti_alese},glont{x.glont} {}


    Player &operator=(const Player &x) {
        this->nume=x.nume;
        this->mana=x.mana;
        this->viata=x.viata;
        this->carti_alese=x.carti_alese;
        this->glont=x.glont;
        return *this;
    }

    ~Player() = default;

    void Index_Pt_Carti(int nr, std::vector<int>& indecsi) const {
        int index;
        for (int i=0;i<nr;i++) {
            std::cin>>index;

            while (index < 1 || index>static_cast<int>(mana.size())) {
                std::cout<<"vezi cate carti ai in mana + numerotarea cartilor incepe de la 1"<<std::endl;
                std::cin>>index;
            }

            indecsi.push_back(index - 1);
        }
    }

    bool Alege_Carti() {
        std::vector<int> indecsi;
        int nr_carti;

        if (mana.empty()) {
            return false;
        }

        std::cout<<nume<<", alege un numar de carti intre 1 si "<<std::min(3,static_cast<int>(mana.size()))<< ": ";
        std::cin>>nr_carti;

        while (nr_carti > static_cast<int>(mana.size())){
            std::cout<<"Mai ai doar "<<mana.size()<<" carti in mana"<<std::endl;
            std::cin>>nr_carti;
        }

        while (nr_carti <1 || nr_carti >3) {
            std::cout<<"Ai voie sa selectezi minim o carte si maxim "<< std::min(3, static_cast<int>(mana.size()))<<std::endl;
            std::cin>>nr_carti;
        }

        if (nr_carti==1){ std::cout<<"indexul cartii este: ";
            Index_Pt_Carti(nr_carti,indecsi);
            std::cout<<std::endl;
        }
        else {std::cout<<"indexul celor "<<nr_carti<<" carti este: ";
            Index_Pt_Carti(nr_carti,indecsi);
            std::cout<<std::endl;

        }

        carti_alese.clear();
        for (const int idx : indecsi) {
            if (mana[idx]=="A") carti_alese.push_back(1);
            else if (mana[idx]=="K") carti_alese.push_back(2);
            else if (mana[idx]=="Q") carti_alese.push_back(3);
            else carti_alese.push_back(4);
        }

        Mana_Ramasa(indecsi);

        return !mana.empty();
    }

    void Mana_Ramasa(std::vector<int> indecsi) {
        std::sort(indecsi.rbegin(), indecsi.rend());

        for (int idx : indecsi) {
            mana.erase(mana.begin() + idx);
        }

        std::cout<<nume<<": ";
        for (size_t i=0;i<mana.size();i++) {
            std::cout<<i + 1<<")"<<mana[i]<< " ";
        }
        std::cout<<std::endl;
    }

    [[nodiscard]] const std::vector<int>& Get_CartiAlese() const {
        return carti_alese;
    }

    [[nodiscard]] const std::vector<std::string>& Get_Carti() const {
        return mana;
    }

    [[nodiscard]] bool Fara_Carti() const {
        return mana.empty();
    }

    void Reset_Carti(Pachet_Carti& pachet) {
        mana = pachet.Extrage_Mana();
    }

    void Creste_Viata() {
        viata++;
    }

    [[nodiscard]] int Get_Viata() const {
        return viata;
    }

    [[nodiscard]] const std::string& Get_Nume() const {
        return nume;
    }


    [[nodiscard]] bool Alive() const {
        return viata < glont;
    }

    void Invarte_Revolver(int alt_glont) {
        glont=alt_glont;
    }

    friend std::ostream& operator<<(std::ostream& os,const Player& player);
};

std::ostream& operator<<(std::ostream& os,const Player& player) {
    os<<player.nume<<": ";
    for (size_t i = 0; i < player.mana.size(); i++) {
        os<<i+1<<")"<<player.mana[i]<<" ";
    }
    os<<std::endl;
    return os;
}

class Table{
    std::string table_name;
    int index_table{};

public:
    Table() = default;

    Table(const std::string& table_name, const int& index_table){
        this->table_name=table_name;
        this->index_table=index_table;
    }

    Table(const Table& x) : table_name{x.table_name}, index_table{x.index_table}{}

    Table& operator=(const Table& x){
        table_name=x.table_name;
        index_table=x.index_table;
        return *this;
        }

    ~Table() = default;

    void Set_TableName() {
        int masa=rand()%3+1;
        if (masa==1) {this->table_name="ACE'S TABLE", index_table=1;}
        else if (masa==2) {this->table_name="KING'S TABLE",index_table=2;}
        else {this->table_name="QUEEN'S TABLE", index_table=3;}
    }

    [[nodiscard]] int Table_Index() const {
        return index_table;
    }

    friend std::ostream& operator<<(std::ostream& os,const Table& table);


};

    std::ostream& operator<<(std::ostream& os,const Table& table) {
    os<<"Masa aleasa: "<<table.table_name<<" ";
    return os;
    }


class Joc {
        int dificultate;
        std::vector<Player> players;
        Table table;
        Pachet_Carti carti;

    public:

        Joc(const std::vector<std::string>& nume_jucatori, Pachet_Carti& pachet): dificultate(nume_jucatori.size()), carti(pachet) {
            for (const auto& nume : nume_jucatori) {
                players.emplace_back(nume, pachet, 0);
            }
        }


        Joc(const Joc& x) : dificultate{x.dificultate}, players {x.players}, table {x.table}, carti {x.carti}{}

        Joc& operator=(const Joc& x) {
            this->dificultate=x.dificultate;
            this->players=x.players;
            this->table=x.table;
            this->carti=x.carti;
            return *this;
        }

        ~Joc() = default;

        int Set_Dificultate() {
            int nr_playeri;
            std::cout<<"Numarul de rusi cu care vrei sa te joci este:";
            std::cin>>nr_playeri;
            std::cout<<std::endl;

            while (nr_playeri<1 || nr_playeri>3) {
                if (nr_playeri<1) {
                    std::cout<<"Daca refuzi sa te joci te omoara oricum..."<<std::endl;
                    std::cout<<"Deci numarul de rusi cu care vrei sa te joci este:"<<std::endl;
                    std::cin>>nr_playeri;
                }
                else{
                    std::cout<<"Poti juca maxim cu 3 rusii... NU ii enerva!"<<std::endl;
                    std::cout<<"Deci numarul de rusi cu care vrei sa te joci este:"<<std::endl;
                    std::cin>>nr_playeri;
                }
            }

            this->dificultate=nr_playeri;

            return dificultate;
        }

        static void Reset_Revolver(std::vector<Player*>& players) {
            for (const auto& player : players)
                player->Invarte_Revolver(rand() % 6 + 1);
        }

        static bool Minte(Player& jucator_crt, Player& adversar, const Table& masa) {
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
                    jucator_crt.Creste_Viata();
                    std::cout<<jucator_crt.Get_Nume()<<": "<<jucator_crt.Get_Viata()<<"/6"<<std::endl;
                    std::cout<<std::endl;

                    return true;
                }
                else {
                    std::cout<<jucator_crt.Get_Nume()<<" nu a mintit! "<<std::endl;
                    adversar.Creste_Viata();
                    std::cout<<adversar.Get_Nume()<<": "<<adversar.Get_Viata()<<"/6"<<std::endl;
                    std::cout<<std::endl;
                    return true;

                }
            }
            std::cout<<std::endl;
            return false;
        }

        static std::vector<Player*> Jucatori_Activi(std::vector<Player*>& jucatori_initiali, Pachet_Carti& carti) {
            std::vector<Player*> activi;

            for (auto& jucator : jucatori_initiali) {
                if (jucator->Alive()) {
                    jucator->Reset_Carti(carti);
                    activi.push_back(jucator);
                }
            }

            return activi;
        }

        void Incepe_Joc() {
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
                    if (jucatori_la_masa[0]->Get_Nume()=="Marius") std::cout<<"Felicitari ai reusit sa bati rusii la jocul lor!"<<std::endl;
                    else std::cout<<"Din pacate ai murit... Data viitoare nu mai intra in baruri dubioase din Rusia!"<<std::endl;
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
                            jucator_urmator.Creste_Viata();
                            std::cout << jucator_urmator.Get_Nume() << ": " << jucator_urmator.Get_Viata() << "/6" << std::endl << std::endl;
                            break;
                        }

                        if (jucator_curent.Fara_Carti()) {
                            std::cout << jucator_curent.Get_Nume() << "A ramas fara carti si a scapat momentan..."<< std::endl;
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

                    for (auto& p : de_eliminat) {
                        auto it = std::find(jucatori_la_masa.begin(), jucatori_la_masa.end(), p);
                        if (it != jucatori_la_masa.end()) {
                            jucatori_la_masa.erase(it);
                        }
                    }

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
        friend std::ostream& operator<<(std::ostream& os, const Joc& joc);

    };



std::ostream& operator<<(std::ostream& os, const Joc& joc) {
    os<<std::endl<<"---------------------"<<std::endl;
    os << joc.table << std::endl;

    for (int i = 0; i <= joc.dificultate; ++i) {
        const Player& player = joc.players[i];
        if (player.Alive() && !player.Fara_Carti()) {
            os << player.Get_Nume() << " | Glont: " << player.Get_Viata() << "/6 | Mana: ";
            for (const auto& carte : player.Get_Carti()) {
                os << carte << " ";
            }
            os << std::endl;
        }
    }
    os << "---------------------" << std::endl;
    return os;
}

int main() {
    srand(time(nullptr));

    Pachet_Carti pachet;
    pachet.Amesteca_Pachet();

    Joc joc({"Marius","Ivan","Aleksei","Dimitri"},pachet);

    joc.Incepe_Joc();

    char joc_nou;
    std::cout<<std::endl<<"Vrei sa joci din nou? Apasa 0 daca da:";
    std::cin>>joc_nou;

    while (joc_nou == '0') {
        std::cout<<std::endl;

        Pachet_Carti pachet2;
        pachet2.Amesteca_Pachet();
        Joc joc2({"Marius","Ivan","Aleksei","Dimitri"},pachet2);
        joc2.Incepe_Joc();

        std::cout<<std::endl<<"Vrei sa joci din nou? Apasa 0 daca da";
        std::cin>>joc_nou;
    }

    std::cout<<std::endl<<"-----------------------------------------"<<std::endl;
    std::cout<<"Cand iti revine cheful stii unde sa revii"<<std::endl;
    std::cout<<"-----------------------------------------"<<std::endl;
}

// //     sf::RenderWindow window;
// //     ///////////////////////////////////////////////////////////////////////////
// //     /// NOTE: sync with env variable APP_WINDOW from .github/workflows/cmake.yml:31
// //     window.create(sf::VideoMode({800, 700}), "My Window", sf::Style::Default);
// //     ///////////////////////////////////////////////////////////////////////////
// //     //
// //     ///////////////////////////////////////////////////////////////////////////
// //     /// NOTE: mandatory use one of vsync or FPS limit (not both)            ///
// //     /// This is needed so we do not burn the GPU                            ///
// //     window.setVerticalSyncEnabled(true);                                    ///
// //     /// window.setFramerateLimit(60);                                       ///
// //     ///////////////////////////////////////////////////////////////////////////
// //     ///
// //     while(window.isOpen()) {
// //         bool shouldExit = false;
// //         sf::Event e{};
// //         while(window.pollEvent(e)) {
// //             switch(e.type) {
// //                 case sf::Event::Closed:
// //                     window.close();
// //                 break;
// //                 case sf::Event::Resized:
// //                     std::cout << "New width: " << window.getSize().x << '\n'
// //                               << "New height: " << window.getSize().y << '\n';
// //                 break;
// //                 case sf::Event::KeyPressed:
// //                     std::cout << "Received key " << (e.key.code == sf::Keyboard::X ? "X" : "(other)") << "\n";
// //                 if(e.key.code == sf::Keyboard::Escape)
// //                     shouldExit = true;
//                 break;
//                 default:
//                     break;
//             }
//         }
//         if(shouldExit) {
//             window.close();
//             break;
//         }
//         using namespace std::chrono_literals;
//         std::this_thread::sleep_for(300ms);
//
//         window.clear();
//         window.display();
//     }