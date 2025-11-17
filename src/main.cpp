#include "DigitalWallet.hpp"            
#include <iostream>                     
#include <utility>                      

int main() {                           
    std::cout << "=== Demo pentru (2)-(6) ===\n";

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
    return 0;                           
}
