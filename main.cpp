#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <random>
#include <algorithm>

class Pachet_carti {
    std::vector<std::string>carti;

public:
    Pachet_carti() :
        carti{"A", "A", "A", "A", "A", "A",
            "K", "K", "K", "K", "K", "K",
            "Q", "Q", "Q", "Q", "Q", "Q",
            "JOKER","JOKER"} {};


    Pachet_carti(const Pachet_carti &x) {
        carti = x.carti;
    }

    ~Pachet_carti() = default;

    Pachet_carti& operator=(const Pachet_carti &x) {
        carti = x.carti;
        return *this;
    }

    void Amesteca_pachet() {
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
        for(int i=0;i<mana.size();i++) {
            std::cout<<mana[i]<<" ";
        }
    }

};



class Player {
    std::string nume;
    std::vector<std::string> mana;

public:
    Player(const std::string& nume,Pachet_carti& mana) {
        this->nume=nume;
        this->mana=mana.Extrage_mana();
    }

    Player &operator=(const Player &x) {
        this->nume=x.nume;
        this->mana=x.mana;
        return *this;
    }

    ~Player() = default;

    void Afis_Mana() {
        std::cout<<nume<<": ";
        for (size_t i = 0; i < mana.size(); i++) {
            std::cout << i + 1 << ")" << mana[i] << " ";
        }
        std::cout << std::endl;
    }

    void Index_pt_carti(int nr, std::vector<int>& indecsi) {
        int index;
        for (int i=0;i<nr;i++) {
            std::cin>>index;

            while (index < 1 || index>mana.size()) {
                std::cout<<"vezi cate carti ai in mana + numerotarea cartilor incepe de la 1"<<std::endl;
                std::cin>>index;
            }

            indecsi.push_back(index - 1);
        }
    }

    void Alege_carti() {
        std::vector<int> indecsi;
        int nr_carti;

        std::cout<<nume<<", alege un numar de carti intre 1 si 3 : ";
        std::cin>>nr_carti;

        while (nr_carti > mana.size()){
            std::cout<<"Mai ai doar "<<mana.size()<<" carti in mana"<<std::endl;
            std::cin>>nr_carti;
        }

        while (nr_carti <1 || nr_carti >3) {
            std::cout<<"Ai voie sa selectezi minim o carte si maxim 3"<<std::endl;
            std::cin>>nr_carti;
        }

        if (nr_carti==1){ std::cout<<"indexul cartii este: "<<std::endl;
            Index_pt_carti(nr_carti,indecsi);
        }
        else {std::cout<<"indexul celor "<<nr_carti<<" carti este: "<<std::endl;
            Index_pt_carti(nr_carti,indecsi);
        }

        Mana_ramasa(indecsi);
    }

    void Mana_ramasa(std::vector<int> indecsi) {
        std::sort(indecsi.rbegin(), indecsi.rend());

        for (int idx : indecsi) {
            mana.erase(mana.begin() + idx);
        }
        std::cout<<std::endl;

        std::cout<<nume<<": ";
        for (int i=0;i<mana.size();i++) {
            std::cout<<i + 1<<")"<<mana[i]<< " ";
        }
        std::cout<<std::endl;
    }


};

class Joc {
    std::string nr_playeri;

public:

    // int Alege_nr_playeri() {
    //     std::cin>>nr_playeri;
    //
    // }

    Joc() = default;

    explicit Joc(std::string nr_playeri)
        : nr_playeri(std::move(nr_playeri)) {
    }

    int Alege_masa() {
        return rand() % 3 + 1;
    }
};

class Table{
    std::string table_name;


public:

    void setTableName(Joc& joc) {
        if (joc.Alege_masa()==1) this->table_name="ACE'S TABLE";
        if (joc.Alege_masa()==2) this->table_name="KING'S TABLE";
        if (joc.Alege_masa()==3) this->table_name="QUEEN'S TABLE";
    }
    void printTableName() const {
        std::cout <<"Masa aleasa: " << table_name << std::endl;
    }
};

int main() {
    Pachet_carti pachet;
    pachet.Amesteca_pachet();

    Player player1("Stefi", pachet);
    player1.Afis_Mana();

    Player player2("Marus", pachet);
    player2.Afis_Mana();

    std::cout << std::endl;

    player1.Alege_carti();
    std::cout << std::endl;
    player2.Alege_carti();
    std::cout << std::endl;
    player1.Alege_carti();
}




    /*srand(time(0));
    Joc joc;
    Table table;
    Player player1{"EU","Player1:"};
    player1.afismana();
    std::cout<<std::endl;
    table.setTableName(joc);
    table.printTableName();

    Player player2{"AI","Player2:"};
    player2.afismana();
    std::cout<<std::endl;
    table.setTableName(joc);
    table.printTableName();

    Pachet_carti pachet;
    pachet.Amesteca_pachet();*/


