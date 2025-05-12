#include <iostream>
#include <vector>
#include <random>

#include "Liars_Deck.h"
#include "Liars_Dice.h"
#include "Pachet_Carti.h"


// #include "cmake-build-debug/_deps/sfml-src/src/SFML/Window/CursorImpl.hpp"
// #include <SFML/Graphics.hpp>
// #include <chrono>
// #include <thread>

void Afis_Moduri() {
    std::cout<<"Alege un mod de joc:\n";
    std::cout<<"1) --> LIAR'S DECK 🃏\n";
    std::cout<<"2) --> LIAR'S DICE 🎲\n";
    std::cout<<"Mod de joc: ";
}

void Avertismente(int x) {
    std::cout<<std::endl;
    if (x==0) {
        std::cout<<"⚠️ Trebuie sa alegi unul dintre modurile de joc ⚠️\n";
    }
    else if (x==1) {
        std::cout<<"⚠️⚠️ TREBUIE SA SCRII 1 SAU 2! ⚠️⚠️\n";
    }
    else if (x==2) {
        std::cout<<"⚠️⚠️⚠️ Daca mai faci asta inca o data, Dimitri se va autosesiza si va alege el pentru tine... ⚠️⚠️⚠️\n";
    }
    Afis_Moduri();
}


int main() {
    srand(time(nullptr));

    Pachet_Carti pachet;
    Zaruri zaruri;
    pachet.Amesteca_Pachet();
    int mod_de_joc;

    Liars_Deck joc({"Marius","Ivan","Aleksei","Dimitri"},pachet);
    Liars_Dice joc2({"Marius","Ivan","Aleksei","Dimitri"},zaruri);

    std::cout<<"\n----------- Privet! -----------\n";
    std::cout<<"Moduri de joc:\n";
    std::cout<<"1) --> LIAR'S DECK 🃏\n";
    std::cout<<"2) --> LIAR'S DICE 🎲\n";
    std::cout<<"Mod de joc: ";
    std::cin>>mod_de_joc;
    int eroare=0;

    while (mod_de_joc!=1 && mod_de_joc!=2) {
        if (eroare==3) {mod_de_joc=1; break;}

        Avertismente(eroare);
        std::cin>>mod_de_joc;

        eroare++;
    }
    std::cout<<std::endl;
    if (mod_de_joc==1) joc.Incepe_Joc();
    else joc2.Incepe_Joc();

    eroare=0;
    std::string joc_nou;
    std::cout<<std::endl<<"Vrei sa joci din nou? Scrie da pentru a continua:";
    std::cin>>joc_nou;

    int mod_de_joc_nou;
    while (joc_nou == "da") {
        std::cout<<std::endl;

        Pachet_Carti pachet2;
        Zaruri zaruri2;
        pachet2.Amesteca_Pachet();
        Liars_Deck joc3({"Marius","Ivan","Aleksei","Dimitri"},pachet2);
        Liars_Dice joc4({"Marius","Ivan","Aleksei","Dimitri"},zaruri2);

        Afis_Moduri();
        std::cin>>mod_de_joc_nou;

        while (mod_de_joc_nou!=1 && mod_de_joc_nou!=2) {

            if (eroare==3) {mod_de_joc_nou=1; break;}
            Avertismente(eroare);
            std::cin>>mod_de_joc_nou;

            eroare++;
        }

        std::cout<<std::endl;
        if (mod_de_joc_nou==1) joc3.Incepe_Joc();
        else joc4.Incepe_Joc();

        std::cout<<std::endl<<"Vrei sa joci din nou? Scrie da pentru a continua:";
        std::cin>>joc_nou;
    }

    std::cout<<std::endl<<"-----------------------------------------"<<std::endl;
    std::cout<<"Cand iti revine cheful stii unde sa revii"<<std::endl;
    std::cout<<"-----------------------------------------"<<std::endl;
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
