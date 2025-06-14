//
// Created by cioba on 5/21/2025.
//

#include "Manager_Joc.h"

#include "Liars_Deck_Factory.h"
#include "Liars_Dice_Factory.h"
#include "Liars_Dice_Traditional_Factory.h"


Manager_Joc::Manager_Joc() = default;

void Manager_Joc::Incepe_Joc(const std::unique_ptr<Joc_Factory> &f) {

    // if (mod==1) {
    //     Pachet_Carti pachet;
    //     pachet.Amesteca_Pachet();
    //     joc_crt = std::make_unique<Liars_Deck>(std::vector<std::string>{"Marius", "Ivan", "Aleksei", "Dimitri"}, pachet);
    // }
    // else {
    //     Zaruri zaruri;
    //     joc_crt = std::make_unique<Liars_Dice>(std::vector<std::string>{"Marius", "Ivan", "Aleksei", "Dimitri"}, zaruri);
    // }
    joc_crt=f->Creaza_joc();
    joc_crt->Joaca_Joc_Template_Method();

    jocuri_jucate.emplace_back(joc_crt->clone());

    const Player* castigator=joc_crt->Get_Castigator();
    castigatori.emplace_back(castigator->clone());
}

void Manager_Joc::Afis_Moduri() {
    std::cout<<"Alege un mod de joc:\n";
    std::cout<<"1) --> LIAR'S DECK 🃏\n";
    std::cout<<"2) --> LIAR'S DICE CLASIC 🎲\n";
    std::cout<<"3) --> LIAR'S DICE TRADITIONAL 🎲\n";
    std::cout<<"Mod de joc: ";
}

void Manager_Joc::Avertismente(const int x) {
    std::cout<<std::endl;
    if (x==0) {
        std::cout<<"⚠ Trebuie sa alegi unul dintre modurile de joc ⚠\n";
    }
    else if (x==1) {
        std::cout<<"⚠⚠ TREBUIE SA SCRII 1, 2 sau 3! ⚠⚠\n";
    }
    else if (x==2) {
        std::cout<<"⚠⚠⚠ Daca mai faci asta inca o data, Dimitri se va autosesiza si va alege el pentru tine... ⚠⚠⚠\n";
    }
    Afis_Moduri();
}

std::string Manager_Joc::Alege_Mod() {
    std::string mod_de_joc;
    std::cin>>mod_de_joc;

    int eroare=0;
    while (mod_de_joc!="1" && mod_de_joc!="2" && mod_de_joc!="3") {
        if (eroare==3) {mod_de_joc="1"; break;}

        Avertismente(eroare);
        std::cin>>mod_de_joc;

        eroare++;
    }
    std::cout<<std::endl;
    return mod_de_joc;

}

std::unique_ptr<Joc_Factory> Manager_Joc::Creaza_Factory(const std::string &mod) {
    if (mod=="1") return std::make_unique<Liars_Deck_Factory>();
    if (mod=="2") return std::make_unique<Liars_Dice_Factory>();
    return std::make_unique<Liars_Dice_Traditional_Factory>();
}

void Manager_Joc::Afiseaza_Istoric() const {
    if (!jocuri_jucate.empty()) {
        std::cout<<"\nIstoric jocuri jucate: "<<std::endl;
        int k=0;
        for (const auto& joc: jocuri_jucate) {
            std::cout<<k+1<<") "<<joc->Get_Nume_Joc()<<", castigator: "<<castigatori[k]->Get_Nume()<<std::endl;
            k++;
        }
    }
}

void Manager_Joc::Porneste_Joc() {
    srand(time(nullptr));
    std::string mod_de_joc;
    bool verificare=false;
    std::unique_ptr<Joc_Factory> factory;

    std::cout<<"\n----------- Privet! -----------\n";
    Afis_Moduri();

    mod_de_joc=Alege_Mod();

    try {
        factory=Creaza_Factory(mod_de_joc);

        Incepe_Joc(factory);


        std::string joc_nou;
        std::cout<<std::endl<<"Vrei sa joci din nou? Scrie da pentru a continua:";
        std::cin>>joc_nou;


        while (joc_nou == "da") {
            std::cout<<std::endl;

            Afis_Moduri();
            mod_de_joc=Alege_Mod();

            factory=Creaza_Factory(mod_de_joc);

            Incepe_Joc(factory);

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

Manager_Joc* Manager_Joc::instanta=nullptr;

Manager_Joc* Manager_Joc::Get_Instanta() {
    if (!instanta) {
        instanta=new Manager_Joc();
    }
    return instanta;
}