#pragma once
#include <cstddef>
#include <iostream>

class DigitalWallet {
private:
    char* owner_;            
    int*  tx_;              
    std::size_t size_;       
    std::size_t capacity_;   

    static char* dupCString(const char* s);
    void ensureCapacity(std::size_t minCap);

public:
    explicit DigitalWallet(const char* owner = "Anon", std::size_t initialCap = 4);

    DigitalWallet(const DigitalWallet& other);

    DigitalWallet(DigitalWallet&& other) noexcept;

    DigitalWallet& operator=(const DigitalWallet& other);

    DigitalWallet& operator=(DigitalWallet&& other) noexcept;

    ~DigitalWallet();

    void addTransaction(int amount);
    std::size_t count() const { return size_; }
    const char* owner() const { return owner_; }
    int at(std::size_t idx) const; // aruncă dacă e out-of-range
    void print(std::ostream& os = std::cout) const;
};
