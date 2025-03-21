#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <random>
#include <algorithm>
// #include <SFML/Graphics.hpp>
// #include <chrono>
// #include <thread>

class Pachet_carti {
    std::vector<std::string>carti;

public:
    Pachet_carti() :
        carti{"A", "A", "A", "A", "A", "A",
            "K", "K", "K", "K", "K", "K",
            "Q", "Q", "Q", "Q", "Q", "Q",
            "JOKER","JOKER"} {};


    Pachet_carti(const Pachet_carti &x): carti{x.carti} {};

    ~Pachet_carti() = default;

    Pachet_carti& operator=(const Pachet_carti &x) {
        carti = x.carti;
        return *this;
    }

    void Amesteca_pachet() {
        carti={"A", "A", "A", "A", "A", "A",
            "K", "K", "K", "K", "K", "K",
            "Q", "Q", "Q", "Q", "Q", "Q",
            "JOKER","JOKER"};
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(carti.begin(), carti.end(), g);
    }

    std::vector<std::string> Extrage_mana() {
        std::vector<std::string> mana;
        for(int i=0;i<5;i++) {
            mana.push_back(carti.back());
            carti.pop_back();
        }
        return mana;
    }

    static void Afis_Mana(const std::vector<std::string>& mana) {
        std::cout<<"Mana: ";
        for(const auto & i : mana) {
            std::cout<<i<<" ";
        }
    }

};


class Player {
    std::string nume;
    std::vector<std::string> mana;
    int viata;
    std::vector<int> carti_alese;


public:
    Player(const std::string& nume,Pachet_carti& mana, const int viata) {
        this->nume=nume;
        this->mana=mana.Extrage_mana();
        this->viata=viata;
        this->carti_alese={};
    }

    Player &operator=(const Player &x) {
        this->nume=x.nume;
        this->mana=x.mana;
        this->viata=x.viata;
        this->carti_alese=x.carti_alese;
        return *this;
    }

    ~Player() = default;

    void Afis_Mana() const {
        std::cout<<nume<<": ";
        for (size_t i = 0; i < mana.size(); i++) {
            std::cout<<i+1<<")"<<mana[i]<<" ";
        }
        std::cout<<std::endl;
    }

    void Index_pt_carti(int nr, std::vector<int>& indecsi) {
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

    bool Alege_carti() {
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
            std::cout<<"Ai voie sa selectezi minim o carte si maxim 3, respectiv numarul tau de carti din mana"<<std::endl;
            std::cin>>nr_carti;
        }

        if (nr_carti==1){ std::cout<<"indexul cartii este: "<<std::endl;
            Index_pt_carti(nr_carti,indecsi);
        }
        else {std::cout<<"indexul celor "<<nr_carti<<" carti este: ";
            Index_pt_carti(nr_carti,indecsi);
        }

        carti_alese.clear();
        for (const int idx : indecsi) {
            if (mana[idx]=="A") carti_alese.push_back(1);
            else if (mana[idx]=="K") carti_alese.push_back(2);
            else if (mana[idx]=="Q") carti_alese.push_back(3);
            else carti_alese.push_back(4);
        }

        Mana_ramasa(indecsi);

        return !mana.empty();
    }

    void Mana_ramasa(std::vector<int> indecsi) {
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

    [[nodiscard]] const std::vector<int>& getCartiAlese() const {
        return carti_alese;
    }

    [[nodiscard]] bool Fara_carti() const {
        return mana.empty();
    }

    void reset_carti(Pachet_carti& pachet) {
        mana = pachet.Extrage_mana();
        Afis_Mana();
    }

    void CresteViata() {
        viata++;
        if (viata>1) std::cout<<nume<<" acum are "<<viata<<" vieti"<<std::endl;
        else std::cout<<nume<<" acum are "<<viata<<" viata"<<std::endl;
    }

    [[nodiscard]] int Get_viata() const {
        return viata;
    }

    const std::string& Get_Nume() const {
        return nume;
    }

};

class Table{
    std::string table_name;
    int index_table{};

public:
    Table() = default;

    Table& operator=(const Table& x){
        table_name=x.table_name;
        index_table=x.index_table;
        return *this;
        }

    ~Table() = default;

    void setTableName() {
        int masa=rand()%3+1;
        if (masa==1) {this->table_name="ACE'S TABLE", index_table=1;}
        else if (masa==2) {this->table_name="KING'S TABLE",index_table=2;}
        else {this->table_name="QUEEN'S TABLE", index_table=3;}
    }

    void Afis_TableName() const {
        std::cout <<"Masa aleasa: " << table_name << std::endl;
    }

    int Table_index() const {
        return index_table;
    }

};


class Joc {
    // std::string nr_playeri;

public:

    // void Alege_nr_playeri() {
    //     std::cin>>nr_playeri;
    // }

    Joc() = default;
    ~Joc() = default;

    // explicit Joc(std::string nr_playeri)
    //     : nr_playeri(std::move(nr_playeri)) {
    // }

    bool Minte(Player& player, Player& adversar, const Table& table) {
        int minciuna;

        std::cout<<adversar.Get_Nume()<<", daca crezi ca "<<player.Get_Nume()<<" minte, scrie 1, altfel scrie 0: ";
        std::cin>>minciuna;

        if (minciuna!=0 && minciuna!=1) {std::cout<<"poti scrie doar 0 si 1 aici: "; std::cin>>minciuna;}
        if (minciuna==1) {
            std::vector<int> carti_jucator = player.getCartiAlese();
            int masa_aleasa = table.Table_index();
            bool toate_corecte = std::all_of(carti_jucator.begin(), carti_jucator.end(),
                                             [masa_aleasa](int carte) { return carte == masa_aleasa || carte==4; });

            if (!toate_corecte) {
                std::cout<<player.Get_Nume()<<" a mintit! ";
                player.CresteViata();
                return true;
            }
            else {
                std::cout<<adversar.Get_Nume()<<"nu a mintit! "<<std::endl;
                adversar.CresteViata();
                return true;
            }
        }
        std::cout<<std::endl;
        return false;
    }

};


int main() {
    Pachet_carti pachet;
    Table table;
    Joc joc;
    pachet.Amesteca_pachet();
    table.setTableName();
    table.Afis_TableName();

    Player player1("Marius", pachet,0);
    player1.Afis_Mana();

    Player player2("Ivan", pachet,0);
    player2.Afis_Mana();

    while (player1.Get_viata()<6 && player2.Get_viata()<6) {
        while (!player1.Fara_carti() && !player2.Fara_carti()) {

            if (!player1.Alege_carti()) {
                std::cout << std::endl;
                if (joc.Minte(player1, player2, table)) break;

                std::cout<<player1.Get_Nume()<<" nu mai are carti! ";
                player2.CresteViata();
                break;
            }
            if (joc.Minte(player1, player2, table)) break;

            if (!player2.Alege_carti()) {
                std::cout << std::endl;
                if (joc.Minte(player2, player1, table)) break;

                std::cout<<player2.Get_Nume()<<" nu mai are carti! ";
                player1.CresteViata();
                break;
            }
            if (joc.Minte(player2, player1, table)) break;

        }
        if (player1.Get_viata() >= 6 || player2.Get_viata() >= 6) break;

        std::cout << std::endl;
        std::cout <<"runda s-a terminat"<<std::endl;
        std::cout <<"se genereaza o masa noua"<< std::endl;

        pachet.Amesteca_pachet();
        table.setTableName();
        table.Afis_TableName();
        player1.reset_carti(pachet);
        player2.reset_carti(pachet);
        std::cout<<std::endl;
    }
    std::cout << "Gata joculetul" << std::endl;
}

//     sf::RenderWindow window;
//     ///////////////////////////////////////////////////////////////////////////
//     /// NOTE: sync with env variable APP_WINDOW from .github/workflows/cmake.yml:31
//     window.create(sf::VideoMode({800, 700}), "My Window", sf::Style::Default);
//     ///////////////////////////////////////////////////////////////////////////
//     //
//     ///////////////////////////////////////////////////////////////////////////
//     /// NOTE: mandatory use one of vsync or FPS limit (not both)            ///
//     /// This is needed so we do not burn the GPU                            ///
//     window.setVerticalSyncEnabled(true);                                    ///
//     /// window.setFramerateLimit(60);                                       ///
//     ///////////////////////////////////////////////////////////////////////////
//     ///
//     while(window.isOpen()) {
//         bool shouldExit = false;
//         sf::Event e{};
//         while(window.pollEvent(e)) {
//             switch(e.type) {
//                 case sf::Event::Closed:
//                     window.close();
//                 break;
//                 case sf::Event::Resized:
//                     std::cout << "New width: " << window.getSize().x << '\n'
//                               << "New height: " << window.getSize().y << '\n';
//                 break;
//                 case sf::Event::KeyPressed:
//                     std::cout << "Received key " << (e.key.code == sf::Keyboard::X ? "X" : "(other)") << "\n";
//                 if(e.key.code == sf::Keyboard::Escape)
//                     shouldExit = true;
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

