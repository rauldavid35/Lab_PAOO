#include "DigitalWallet.hpp"            
#include <iostream>                     
#include <utility>                      

int main() {          
    std::cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n" ;                
    std::cout << "=== Demo pentru (2)-(6) [TEMA 1 + ASSIGN-URI] ===\n";

    DigitalWallet w1("Andre");       
    w1.addTransaction(+100);            
    w1.addTransaction(-30);
    w1.addTransaction(+50);
    std::cout << "\nw1 -> ";            
    w1.print();            

    DigitalWallet w2 = w1;              
    std::cout << "\nw2 (copia lui w1) -> ";
    w2.print();                          

    w2.addTransaction(-10);             
    std::cout << "\ndupa ce am modificat w2, w1 ramane: ";
    w1.print();                          

    DigitalWallet w3("Raul");           
    w3.addTransaction(+5);              
    w3 = w2;                            
    std::cout << "\nw3 (copy-assigned de la w2) -> ";
    w3.print();                         

    DigitalWallet w4 = std::move(w3);   
    std::cout << "\nw4 (moved de la w3) -> ";
    w4.print();                          
    std::cout << "\nw3 dupa move (valid dar gol): ";
    w3.print();                         

    DigitalWallet w5("Dani");           
    w5.addTransaction(+200);           
    w5 = std::move(w4);                 
    std::cout << "\nw5 dupa move-assign de la w4 -> ";
    w5.print();                          
    std::cout << "\nw4 dupa move-assign (valid dar gol): ";
    w4.print();                          

    for (int i = 0; i < 16; ++i)        
        w1.addTransaction(i);           
    std::cout << "\nw1 dupa mai multe adduri -> ";
    w1.print();                          

    std::cout << "\n=== Sfarsitul demo-ului ===\n";

    std::cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n" ;

    std::cout << "\n=== Test chain-assignment ===\n";
    DigitalWallet c1("Chain1");
    c1.addTransaction(1);
    DigitalWallet c2("Chain2");
    c2.addTransaction(2);
    DigitalWallet c3("Chain3");
    c3.addTransaction(3);

    // aici se foloseste faptul ca operator= intoarce DigitalWallet&
    c1 = c2 = c3;

    std::cout << "c1 -> "; c1.print();
    std::cout << "c2 -> "; c2.print();
    std::cout << "c3 -> "; c3.print();

    std::cout << "\n=== Sfarsit demo chain-assignment ===\n";

    std::cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n" ;

    std::cout << "\n=== Test self-assignment ===\n";
    w1.print();
    w1 = w1;            // aici vezi în output că nu se strică nimic
    std::cout << "w1 dupa self-assign -> ";
    w1.print();

    std::cout << "\n=== Sfarsit demo self-assignment ===\n";

    std::cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n" ;

    return 0;                           
}
