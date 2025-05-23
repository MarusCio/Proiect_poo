//
// Created by cioba on 5/21/2025.
//

#include "Manager_Joc.h"

void Manager_Joc::Incepe_Joc(const int mod) {

    if (mod==1) {
        Pachet_Carti pachet;
        pachet.Amesteca_Pachet();
        joc_crt = std::make_unique<Liars_Deck>(std::vector<std::string>{"Marius", "Ivan", "Aleksei", "Dimitri"}, pachet);
    }
    else {
        Zaruri zaruri;
        joc_crt = std::make_unique<Liars_Dice>(std::vector<std::string>{"Marius", "Ivan", "Aleksei", "Dimitri"}, zaruri);
    }
    joc_crt->Joaca_Joc_Template_Method();

    jocuri_jucate.emplace_back(joc_crt->clone());
}

void Manager_Joc::Afiseaza_Istoric() const {
    if (!jocuri_jucate.empty()) {
        std::cout<<"\nIstoric jocuri jucate: "<<std::endl;
        int k=0;
        for (const auto& joc: jocuri_jucate) std::cout<<++k<<") "<<joc->Get_Nume_Joc()<<std::endl;
    }
}

void Manager_Joc::Afis_Moduri() {
    std::cout<<"Alege un mod de joc:\n";
    std::cout<<"1) --> LIAR'S DECK 🃏\n";
    std::cout<<"2) --> LIAR'S DICE 🎲\n";
    std::cout<<"Mod de joc: ";
}

void Manager_Joc::Avertismente(const int x) {
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

void Manager_Joc::Porneste_Joc() {
    srand(time(nullptr));
    int mod_de_joc;
    bool verificare=false;

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
        Incepe_Joc(mod_de_joc);

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

            Incepe_Joc(mod_de_joc_nou);

            std::cout<<std::endl;
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

    Afiseaza_Istoric();

}
