#ifndef DIGITAL_WALLET_HPP              
#define DIGITAL_WALLET_HPP

#include <cstddef>                      
#include <iostream>                     

class DigitalWallet {                   
private:                               
    char* ownerName_;            
    int* transactions_;         
    std::size_t transactionCount_;     
    std::size_t capacity_;             

    static char* duplicateCString(const char* s); 
    void ensureCapacity(std::size_t minCapacity); 

public:                                 
    DigitalWallet(const char* ownerName, std::size_t initialCapacity = 0);

    DigitalWallet(const DigitalWallet& other);         
    DigitalWallet(DigitalWallet&& other) noexcept;        
    DigitalWallet& operator=(const DigitalWallet& other); 
    DigitalWallet& operator=(DigitalWallet&& other) noexcept; 
    ~DigitalWallet();                                     

    void addTransaction(int amount);                      
    int  transactionAt(std::size_t index) const;          

    void print(std::ostream& os = std::cout) const;       
};

#endif
