#include "DigitalWallet.hpp"
#include <iostream>
#include <memory>
#include <vector>

void demoUniquePtr() {
    std::cout << "\n--- Demo unique_ptr ---\n";
    
    //am alocat resursa (nu se pote copia)
    std::unique_ptr<DigitalWallet> u1 = std::make_unique<DigitalWallet>("User1");
    u1->addTransaction(100);
    u1->print();

    // std::unique_ptr<DigitalWallet> u2 = u1; //aici e eroare de compilare ca nu se poate copia

    //resursa poate fi doar mutata
    std::cout << "[Move] Transferam ownership catre u2...\n";
    std::unique_ptr<DigitalWallet> u2 = std::move(u1);

    if (!u1) std::cout << "u1 este acum nullptr (gol).\n";
    if (u2) {
        std::cout << "u2 detine resursa: ";
        u2->print();
    }
}

void demoSharedPtr() {
    std::cout << "\n--- Demo shared_ptr ---\n";

    //am alocat resursa shared
    std::shared_ptr<DigitalWallet> s1 = std::make_shared<DigitalWallet>("SharedWallet");
    
    {
        //incercam sa copiem pointerul => ar trebui sa creasca numarul de referinte
        std::shared_ptr<DigitalWallet> s2 = s1;
        std::cout << "Ref count (s1, s2): " << s1.use_count() << "\n"; //ar trebui sa afiseze 2
        
        s2->addTransaction(50); //modificarea e vizibila
    } //pentru ca s2 moare , scade numarul de referinte

    std::cout << "Ref count dupa iesire din scope intern: " << s1.use_count() << "\n"; // Afiseaza 1
    s1->print();
}

void demonstrateCrash() {
    std::cout << "\n--- Demo Utilizare Gresita (Crash Potential) ---\n";

    std::unique_ptr<DigitalWallet> uPtr = std::make_unique<DigitalWallet>("RiskyWallet");
    
    //cream un nou pointer la pointerul unique, cu move
    std::unique_ptr<DigitalWallet> uPtrNew = std::move(uPtr);

    //normal nu ar trebui sa functioneze , deoarece nu mai e valabil
    if (uPtr) {
        uPtr->addTransaction(10);
    } else {
        std::cout << "[Safe Check] uPtr este null dupa move. Accesarea ar fi provocat SEGFAULT (Crash).\n";
    }

    //uPtr->addTransaction(10); //asta trebuie sa crape programul
}

int main() {
    demoUniquePtr();
    demoSharedPtr();
    demonstrateCrash();
    return 0;
}