#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <random>
#include <algorithm>

#include "Joc.h"
#include "Pachet_Carti.h"
#include "Player.h"
#include "Table.h"

// #include "cmake-build-debug/_deps/sfml-src/src/SFML/Window/CursorImpl.hpp"
// #include <SFML/Graphics.hpp>
// #include <chrono>
// #include <thread>

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