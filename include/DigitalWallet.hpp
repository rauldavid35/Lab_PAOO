#ifndef DIGITAL_WALLET_HPP
#define DIGITAL_WALLET_HPP

#include <cstddef>
#include <iostream>

class DigitalWallet {
private:
    char*        ownerName_;          // numele proprietarului (C-string pe heap)
    int*         transactions_;       // vector de tranzacții pe heap
    std::size_t  transactionCount_;   // numărul de tranzacții folosite
    std::size_t  capacity_;           // capacitatea alocată pentru transactions_

    static char* duplicateCString(const char* s);
    void ensureCapacity(std::size_t minCapacity);

public:
    // ctor „de bază”
    DigitalWallet(const char* ownerName, std::size_t initialCapacity = 0);

    // rule of five
    DigitalWallet(const DigitalWallet& other);
    DigitalWallet(DigitalWallet&& other) noexcept;
    DigitalWallet& operator=(const DigitalWallet& other);
    DigitalWallet& operator=(DigitalWallet&& other) noexcept;
    ~DigitalWallet();

    // API
    void addTransaction(int amount);
    int  transactionAt(std::size_t index) const;

    void print(std::ostream& os = std::cout) const;
};

#endif // DIGITAL_WALLET_HPP
