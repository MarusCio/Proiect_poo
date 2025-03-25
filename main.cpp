#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <random>
#include <algorithm>
// #include <SFML/Graphics.hpp>
// #include <chrono>
// #include <thread>

class Pachet_Carti {
    std::vector<std::string>carti;

public:
    Pachet_Carti() :
        carti{"A", "A", "A", "A", "A", "A",
            "K", "K", "K", "K", "K", "K",
            "Q", "Q", "Q", "Q", "Q", "Q",
            "JOKER","JOKER"} {}


    Pachet_Carti(const Pachet_Carti &x): carti{x.carti} {};

    ~Pachet_Carti() = default;

    Pachet_Carti& operator=(const Pachet_Carti &x) {
        carti = x.carti;
        return *this;
    }

    void Amesteca_Pachet() {
        carti={"A", "A", "A", "A", "A", "A",
            "K", "K", "K", "K", "K", "K",
            "Q", "Q", "Q", "Q", "Q", "Q",
            "JOKER","JOKER"};
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

    Player(const Player& x) {
        this->nume=x.nume;
        this->mana=x.mana;
        this->viata=x.viata;
        this->carti_alese=x.carti_alese;
        this->glont=x.glont;
    }

    Player &operator=(const Player &x) {
        this->nume=x.nume;
        this->mana=x.mana;
        this->viata=x.viata;
        this->carti_alese=x.carti_alese;
        this->glont=x.glont;
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

    void Index_Pt_Carti(int nr, std::vector<int>& indecsi) {
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
            std::cout<<"Ai voie sa selectezi minim o carte si maxim 3, respectiv numarul tau de carti din mana"<<std::endl;
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

    [[nodiscard]] bool Fara_Carti() const {
        return mana.empty();
    }

    void Reset_Carti(Pachet_Carti& pachet) {
        mana = pachet.Extrage_Mana();
        Afis_Mana();
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

    [[nodiscard]] int Get_Glont() const {
        return glont;
    }

    void Invarte_Revolver(int alt_glont) {
        glont=alt_glont;
    }
};

class Table{
    std::string table_name;
    int index_table{};

public:
    Table() = default;

    Table(const std::string& table_name, const int& index_table){
        this->table_name=table_name;
        this->index_table=index_table;
    }

    Table(const Table& x) {
        this->index_table=x.index_table;
        this->table_name=x.table_name;
    }

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
        Player player, adversar;
        Table table;
        Pachet_Carti carti;

public:

        Joc(const std::string& nume_player, const std::string& nume_adversar, Pachet_Carti& pachet)
            : dificultate(1), player(nume_player, pachet, 0), adversar(nume_adversar, pachet, 0) {}


        Joc(const Joc& x) {
            this->dificultate=x.dificultate;
            this->player=x.player;
            this->adversar=x.adversar;
            this->table=x.table;
            this->carti=x.carti;
        }

        Joc& operator=(const Joc& x) {
            this->dificultate=x.dificultate;
            this->player=x.player;
            this->adversar=x.adversar;
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
                std::cout<<"Daca refuzi sate joci te omoara oricum..."<<std::endl;
                std::cout<<"Deci numaru de rusi cu care vrei sa te joci este:";
                std::cin>>nr_playeri;
            }
            else{
                std::cout<<"Poti juca maxim cu toti rusii, adica 3... NU ii eneva!"<<std::endl;
                std::cout<<"Deci numaru de rusi cu care vrei sa te joci este:";
                std::cin>>nr_playeri;
            }
        }

        this->dificultate=nr_playeri;

        return dificultate;
    }

        bool Minte(Player& player, Player& adversar, const Table& table) {
        int minciuna;

        std::cout<<adversar.Get_Nume()<<", daca crezi ca "<<player.Get_Nume()<<" minte, scrie 1, altfel scrie 0: ";
        std::cin>>minciuna;

        if (minciuna!=0 && minciuna!=1) {std::cout<<"poti scrie doar 0 si 1 aici: "; std::cin>>minciuna;}
        if (minciuna==1) {
            std::vector<int> carti_jucator = player.Get_CartiAlese();
            int masa_aleasa = table.Table_Index();
            bool toate_corecte = std::all_of(carti_jucator.begin(), carti_jucator.end(),
                                             [masa_aleasa](int carte) { return carte == masa_aleasa || carte==4; });

            if (!toate_corecte) {
                std::cout<<player.Get_Nume()<<" a mintit! "<<std::endl;
                player.Creste_Viata();
                std::cout<<player.Get_Nume()<<": "<<player.Get_Viata()<<"/6"<<std::endl;
                return true;
            }
            else {
                std::cout<<player.Get_Nume()<<" nu a mintit! "<<std::endl;
                adversar.Creste_Viata();
                std::cout<<adversar.Get_Nume()<<": "<<adversar.Get_Viata()<<"/6"<<std::endl;
                return true;
            }
        }
        std::cout<<std::endl;
        return false;
    }


        static void Reset_Revolver1(Player& player1, Player& player2) {
        player1.Invarte_Revolver(rand()%6+1);
        player2.Invarte_Revolver(rand()%6+1);
    }
        static void Reset_Revolver2(Player& player1, Player& player2, Player& player3) {
        player1.Invarte_Revolver(rand()%6+1);
        player2.Invarte_Revolver(rand()%6+1);
        player3.Invarte_Revolver(rand()%6+1);
    }

        static void Reset_Revolver3(Player& player1, Player& player2, Player& player3, Player& player4) {
            player1.Invarte_Revolver(rand()%6+1);
            player2.Invarte_Revolver(rand()%6+1);
            player3.Invarte_Revolver(rand()%6+1);
            player4.Invarte_Revolver(rand()%6+1);
    }

};

int main() {
    srand(time(nullptr));

    Pachet_Carti pachet;
    Table table;
    Joc joc("Marius", "Ivan", pachet);
    int dif=joc.Set_Dificultate();

    pachet.Amesteca_Pachet();
    table.Set_TableName();
    std::cout<<table<<std::endl;

    std::string pierzator;

    if (dif==1) {
        Player player1("Marius", pachet,0);
        player1.Afis_Mana();
        int glont1 = player1.Get_Glont();

        Player player2("Ivan", pachet,0);
        player2.Afis_Mana();
        int glont2 = player2.Get_Glont();

        Joc::Reset_Revolver1(player1, player2);


        while (player1.Get_Viata()<glont1 && player2.Get_Viata()<glont2) {
            while (!player1.Fara_Carti() && !player2.Fara_Carti()) {

                if (!player1.Alege_Carti()) {
                    std::cout << std::endl;
                    if (joc.Minte(player1, player2, table)) break;

                    std::cout<<player1.Get_Nume()<<" nu mai are carti! ";
                    player2.Creste_Viata();
                    std::cout<<player2.Get_Nume()<<": "<<player2.Get_Viata()<<"/6"<<std::endl;
                    break;
                }

                if (joc.Minte(player1, player2, table)) break;

                if (!player2.Alege_Carti()) {
                    std::cout << std::endl;
                    if (joc.Minte(player2, player1, table)) break;

                    std::cout<<player2.Get_Nume()<<" nu mai are carti! ";
                    player1.Creste_Viata();
                    std::cout<<player1.Get_Nume()<<": "<<player1.Get_Viata()<<"/6"<<std::endl;
                    break;
                }

                if (joc.Minte(player2, player1, table)) break;
            }

            if (player1.Get_Viata() >= glont1) {
                std::cout<<std::endl<<"🔥🔥🔥 BOOOOOOOOOOOOOOOOOOOOOM 🔥🔥🔥 "<<std::endl;
                pierzator=player2.Get_Nume();
                break;
            }

            if (player2.Get_Viata() >= glont2) {
                std::cout<<std::endl<<"🔥🔥🔥 BOOOOOOOOOOOOOOOOOOOOOM 🔥🔥🔥 "<<std::endl;
                pierzator=player1.Get_Nume();
                break;
            }

            std::cout << std::endl;
            std::cout <<"runda s-a terminat"<<std::endl;
            std::cout <<"se genereaza o masa noua"<< std::endl;

            pachet.Amesteca_Pachet();
            table.Set_TableName();
            std::cout<<table<<std::endl;
            player1.Reset_Carti(pachet);
            player2.Reset_Carti(pachet);
            std::cout<<std::endl;
        }

        if (pierzator=="Marius") std::cout<<"Felicitari ai reusit sa bati rusii la jocul lor!"<<std::endl;
        else std::cout<<"Din pacate ai murit... Data viitoare nu mai intra in baruri dubioase in Rusia!"<<std::endl;
    }

    else if (dif==2){

        Player player1("Marius", pachet,0);
        player1.Afis_Mana();
        int glont1 = player1.Get_Glont();

        Player player2("Ivan", pachet,0);
        player2.Afis_Mana();
        int glont2 = player2.Get_Glont();

        Player player3("Aleksei", pachet,0);
        player3.Afis_Mana();
        int glont3 = player3.Get_Glont();

        Joc::Reset_Revolver2(player1, player2,player3);


        while (player1.Get_Viata()<glont1 && player2.Get_Viata()<glont2 && player3.Get_Viata()<glont3) {
            while (!player1.Fara_Carti() && !player2.Fara_Carti() && !player3.Fara_Carti()) {

                if (!player1.Alege_Carti()) {
                    std::cout << std::endl;
                    if (joc.Minte(player1, player2, table)) break;

                    std::cout<<player1.Get_Nume()<<" nu mai are carti! ";
                    player2.Creste_Viata();
                    std::cout<<player2.Get_Nume()<<": "<<player2.Get_Viata()<<"/6"<<std::endl;
                    break;
                }
                if (joc.Minte(player1, player2, table)) break;


                if (!player2.Alege_Carti()) {
                    std::cout << std::endl;
                    if (joc.Minte(player2, player3, table)) break;

                    std::cout<<player2.Get_Nume()<<" nu mai are carti! ";
                    player3.Creste_Viata();
                    std::cout<<player3.Get_Nume()<<": "<<player3.Get_Viata()<<"/6"<<std::endl;
                    break;
                }
                if (joc.Minte(player2, player3, table)) break;


                if (!player3.Alege_Carti()) {
                    std::cout << std::endl;
                    if (joc.Minte(player3, player1, table)) break;

                    std::cout<<player3.Get_Nume()<<" nu mai are carti! ";
                    player1.Creste_Viata();
                    std::cout<<player1.Get_Nume()<<": "<<player1.Get_Viata()<<"/6"<<std::endl;
                    break;
                }
                if (joc.Minte(player3, player1, table)) break;

            }

            if (player1.Get_Viata() >= glont1) {
                std::cout<<std::endl<<"🔥🔥🔥 BOOOOOOOOOOOOOOOOOOOOOM 🔥🔥🔥 "<<std::endl;
                pierzator=player2.Get_Nume();
                break;
            }

            if (player2.Get_Viata() >= glont2) {
                std::cout<<std::endl<<"🔥🔥🔥 BOOOOOOOOOOOOOOOOOOOOOM 🔥🔥🔥 "<<std::endl;
                pierzator=player1.Get_Nume();
                break;
            }

            if (player3.Get_Viata() >= glont3) {
                std::cout<<std::endl<<"🔥🔥🔥 BOOOOOOOOOOOOOOOOOOOOOM 🔥🔥🔥 "<<std::endl;
                pierzator=player1.Get_Nume();
                break;
            }

            std::cout << std::endl;
            std::cout <<"runda s-a terminat"<<std::endl;
            std::cout <<"se genereaza o masa noua"<< std::endl;

            pachet.Amesteca_Pachet();
            table.Set_TableName();
            std::cout<<table<<std::endl;
            player1.Reset_Carti(pachet);
            player2.Reset_Carti(pachet);
            player3.Reset_Carti(pachet);
            std::cout<<std::endl;
        }

        if (pierzator=="Marius") std::cout<<"Felicitari ai reusit sa bati rusii la jocul lor!"<<std::endl;
        else std::cout<<"Din pacate ai murit... Data viitoare nu mai intra in baruri dubioase in Rusia!"<<std::endl;
    }

    else if (dif==3) {
        Player player1("Marius", pachet,0);
        player1.Afis_Mana();
        int glont1 = player1.Get_Glont();

        Player player2("Ivan", pachet,0);
        player2.Afis_Mana();
        int glont2 = player2.Get_Glont();

        Player player3("Aleksei", pachet,0);
        player3.Afis_Mana();
        int glont3 = player3.Get_Glont();

        Player player4("Dimitri", pachet,0);
        player4.Afis_Mana();
        int glont4 = player4.Get_Glont();

        Joc::Reset_Revolver3(player1, player2,player3,player4);


        while (player1.Get_Viata()<glont1 && player2.Get_Viata()<glont2 && player3.Get_Viata()<glont3 && player4.Get_Viata()<glont4) {
            while (!player1.Fara_Carti() && !player2.Fara_Carti() && !player3.Fara_Carti() && !player4.Fara_Carti()) {

                if (!player1.Alege_Carti()) {
                    std::cout << std::endl;
                    if (joc.Minte(player1, player2, table)) break;

                    std::cout<<player1.Get_Nume()<<" nu mai are carti! ";
                    player2.Creste_Viata();
                    std::cout<<player2.Get_Nume()<<": "<<player2.Get_Viata()<<"/6"<<std::endl;
                    break;
                }
                if (joc.Minte(player1, player2, table)) break;


                if (!player2.Alege_Carti()) {
                    std::cout << std::endl;
                    if (joc.Minte(player2, player3, table)) break;

                    std::cout<<player2.Get_Nume()<<" nu mai are carti! ";
                    player3.Creste_Viata();
                    std::cout<<player3.Get_Nume()<<": "<<player3.Get_Viata()<<"/6"<<std::endl;
                    break;
                }
                if (joc.Minte(player2, player3, table)) break;


                if (!player3.Alege_Carti()) {
                    std::cout << std::endl;
                    if (joc.Minte(player3, player4, table)) break;

                    std::cout<<player3.Get_Nume()<<" nu mai are carti! ";
                    player4.Creste_Viata();
                    std::cout<<player4.Get_Nume()<<": "<<player4.Get_Viata()<<"/6"<<std::endl;
                    break;
                }
                if (joc.Minte(player3, player4, table)) break;


                if (!player4.Alege_Carti()) {
                    std::cout << std::endl;
                    if (joc.Minte(player4, player1, table)) break;

                    std::cout<<player4.Get_Nume()<<" nu mai are carti! ";
                    player1.Creste_Viata();
                    std::cout<<player1.Get_Nume()<<": "<<player1.Get_Viata()<<"/6"<<std::endl;
                    break;
                }
                if (joc.Minte(player4, player1, table)) break;
            }

            if (player1.Get_Viata() >= glont1) {
                std::cout<<std::endl<<"🔥🔥🔥 BOOOOOOOOOOOOOOOOOOOOOM 🔥🔥🔥 "<<std::endl;
                pierzator=player1.Get_Nume();
                break;
            }

            if (player2.Get_Viata() >= glont2) {
                std::cout<<std::endl<<"🔥🔥🔥 BOOOOOOOOOOOOOOOOOOOOOM 🔥🔥🔥 "<<std::endl;
                pierzator=player2.Get_Nume();
                break;
            }

            if (player3.Get_Viata() >= glont3) {
                std::cout<<std::endl<<"🔥🔥🔥 BOOOOOOOOOOOOOOOOOOOOOM 🔥🔥🔥 "<<std::endl;
                pierzator=player3.Get_Nume();
                break;
            }

            if (player4.Get_Viata() >= glont4) {
                std::cout<<std::endl<<"🔥🔥🔥 BOOOOOOOOOOOOOOOOOOOOOM 🔥🔥🔥 "<<std::endl;
                pierzator=player4.Get_Nume();
                break;
            }

            std::cout << std::endl;
            std::cout <<"runda s-a terminat"<<std::endl;
            std::cout <<"se genereaza o masa noua"<< std::endl;

            pachet.Amesteca_Pachet();
            table.Set_TableName();
            std::cout<<table<<std::endl;
            player1.Reset_Carti(pachet);
            player2.Reset_Carti(pachet);
            player3.Reset_Carti(pachet);
            player4.Reset_Carti(pachet);
            std::cout<<std::endl;
        }

        if (pierzator=="Marius") std::cout<<"Felicitari ai reusit sa bati rusii la jocul lor!"<<std::endl;
        else std::cout<<"Din pacate ai murit... Data viitoare nu mai intra in baruri dubioase din Rusia!"<<std::endl;
    }


    // char joc_nou;
    // std::cout<<"Vrei sa joci din nou? Apasa 0 daca da: ";
    // std::cin>>joc_nou;
    //
    // if (joc_nou == '0') {
    //     // main();
    // }
    // else {
    //     std::cout<<"Cand iti revine cheful stii unde sa revii"<<std::endl;
    // }
}
// }
//
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

