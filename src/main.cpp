#include "DigitalWallet.hpp"
#include <iostream>
#include <utility>

static volatile int* g_leak_sink = nullptr;

int main() {
    std::cout << "=== Proof-of-life demo for items (2)-(6) ===\n";

    DigitalWallet w1("Alice");
    w1.addTransaction(+100);
    w1.addTransaction(-30);
    w1.addTransaction(+50);
    std::cout << "w1 -> "; w1.print();

    DigitalWallet w2 = w1;
    std::cout << "w2 (copy of w1) -> "; w2.print();
    w2.addTransaction(-10);
    std::cout << "after modifying w2, w1 remains: "; w1.print();

    DigitalWallet w3("Bob");
    w3.addTransaction(+5);
    w3 = w2;
    std::cout << "w3 (copy-assigned from w2) -> "; w3.print();

    DigitalWallet w4 = std::move(w3);
    std::cout << "w4 (moved from w3) -> "; w4.print();
    std::cout << "w3 after move (valid but empty): "; w3.print();

    DigitalWallet w5("Charlie");
    w5.addTransaction(+200);
    w5 = std::move(w4);
    std::cout << "w5 after move-assign from w4 -> "; w5.print();
    std::cout << "w4 after move-assign (valid but empty): "; w4.print();

    for (int i = 0; i < 16; ++i) w1.addTransaction(i);
    std::cout << "w1 after bulk adds -> "; w1.print();

    std::cout << "=== End demo – dtors free heap cleanly ===\n";

    //g_leak_sink = new int[10]; 
    //g_leak_sink[0] = 42;       

    return 0;
}
