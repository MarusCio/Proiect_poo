#include <iostream>
#include <memory>
#include <vector>
#include <random>

#include "Exceptii_Joc.h"
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

void Avertismente(const int x) {
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
    int mod_de_joc;
    bool verificare=false;
    std::unique_ptr<Joc> joc_crt;
    std::vector<std::unique_ptr<Joc>> jocuri_jucate;

    std::cout<<"\n----------- Privet! -----------\n";
    Afis_Moduri();
    std::cin>>mod_de_joc;

    int eroare=0;
    while (mod_de_joc!=1 && mod_de_joc!=2) {
        if (eroare==3) {mod_de_joc=1; break;}

        Avertismente(eroare);
        std::cin>>mod_de_joc;

        eroare++;
    }
    std::cout<<std::endl;

    try {
        if (mod_de_joc==1) {
            Pachet_Carti pachet;
            pachet.Amesteca_Pachet();
            joc_crt = std::make_unique<Liars_Deck>(std::vector<std::string>{"Marius", "Ivan", "Aleksei", "Dimitri"}, pachet);
        }
        else {
            Zaruri zaruri;
            joc_crt = std::make_unique<Liars_Dice>(std::vector<std::string>{"Marius", "Ivan", "Aleksei", "Dimitri"}, zaruri);
        }
        joc_crt->Incepe_Joc();

        jocuri_jucate.push_back(joc_crt->clone());

        eroare=0;
        std::string joc_nou;
        std::cout<<std::endl<<"Vrei sa joci din nou? Scrie da pentru a continua:";
        std::cin>>joc_nou;

        int mod_de_joc_nou;
        while (joc_nou == "da") {
            std::cout<<std::endl;

            Afis_Moduri();
            std::cin>>mod_de_joc_nou;

            while (mod_de_joc_nou!=1 && mod_de_joc_nou!=2) {

                if (eroare==3) {mod_de_joc_nou=1; break;}
                Avertismente(eroare);
                std::cin>>mod_de_joc_nou;

                eroare++;
            }

            std::cout<<std::endl;


            if (mod_de_joc_nou==1) {
                Pachet_Carti pachet2;
                pachet2.Amesteca_Pachet();
                joc_crt = std::make_unique<Liars_Deck>(std::vector<std::string>{"Marius", "Ivan", "Aleksei", "Dimitri"}, pachet2);
            }
            else {
                Zaruri zaruri2;
                joc_crt = std::make_unique<Liars_Dice>(std::vector<std::string>{"Marius", "Ivan", "Aleksei", "Dimitri"}, zaruri2);
            }
            joc_crt->Incepe_Joc();

            jocuri_jucate.push_back(joc_crt->clone()); // salvezi copia înainte de Incepe_Joc()


            std::cout<<std::endl<<"Vrei sa joci din nou? Scrie da pentru a continua:";
            std::cin>>joc_nou;
        }
    }
    catch (const Eroare_Numar_Playeri& e){
        std::cout << "Eroare: " << e.what()<< "\n";
        verificare=true;
    }
    catch (const Eroare_Index_Invalid& e) {
        std::cout << "Eroare: " << e.what()<< "\n";
        verificare=true;
    }
    catch (const Eroare_Declarare_Minciuna& e) {
        std::cout << "Eroare: " << e.what()<< "\n";
        verificare=true;
    }
    catch (const Eroare_Inceput_Liars_Dice& e) {
        std::cout << "Eroare: " << e.what()<< "\n";
        verificare=true;
    }
    catch (const Eroare_Comanda_LD_Invalida& e) {
        std::cout << "Eroare: " << e.what()<< "\n";
        verificare=true;
    }


    std::cout<<std::endl<<"-----------------------------------------"<<std::endl;
    if (verificare==false) std::cout<<"Cand iti revine cheful stii unde sa revii"<<std::endl;
    else std::cout<<"Fii mai atent la inputuri!"<<std::endl;
    std::cout<<"-----------------------------------------"<<std::endl;

    std::cout<<"\nIstoric jocuri jucate: "<<std::endl;
    for (const auto& joc: jocuri_jucate) {std::cout<<joc->Get_Nume_Joc()<<std::endl;}
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
