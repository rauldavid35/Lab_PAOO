#include "DigitalWallet.hpp"            
#include <cstring>                      
#include <utility>                      
#include <stdexcept>                    

static char* safeDup(const char* s) {   // static = vizibil doar în acest fișier .cpp, folosit pentru duplicare string
    if (!s) return nullptr;             
    const std::size_t n = std::strlen(s); 
    char* p = new char[n + 1];          
    std::memcpy(p, s, n + 1);           
    return p;                      
}


char* DigitalWallet::duplicateCString(const char* s) { return safeDup(s); } //returneaza rezultatul de la functia statica

void DigitalWallet::ensureCapacity(std::size_t minCapacity) { //functie folosita pentru alocare de spatiu un plus
    if (capacity_ >= minCapacity) return;
    //std::size_t newCap = 1 ;
    //if(capacity_)
    //    std::size_t newCap=capacity_;      <----BUG , redeclaram newcap in loc sa dau assign
    std::size_t newCap = capacity_ ? capacity_ : 1; //corect , acum nu mai declar o variabila locala noua , ci doar creez si dau assign
    while (newCap < minCapacity) 
        newCap *= 2;
    int* newData = new int[newCap];            
    for (std::size_t i = 0; i < transactionCount_; ++i)
        newData[i] = transactions_[i];
    delete[] transactions_;                   
    transactions_ = newData;                   
    capacity_ = newCap;                      
}

DigitalWallet::DigitalWallet(const char* ownerName, std::size_t initialCapacity) //constructorul simplu
    : ownerName_(duplicateCString(ownerName)),                      
      transactions_(initialCapacity ? new int[initialCapacity] : nullptr),
      transactionCount_(0),                                         
      capacity_(initialCapacity) {                                 
    std::cout << "[ctor] DigitalWallet(detinator = "                   
              << (ownerName_ ? ownerName_ : "(fara nume)") << ")\n";
}

DigitalWallet::DigitalWallet(const DigitalWallet& other) //copy constructorul
    : ownerName_(duplicateCString(other.ownerName_)),               
      transactions_(other.capacity_ ? new int[other.capacity_] : nullptr), 
      transactionCount_(other.transactionCount_),                   
      capacity_(other.capacity_) {                                  
    std::cout << "[copy ctor] de la "                               
              << (other.ownerName_ ? other.ownerName_ : "(fara nume)") << "\n";
    for (std::size_t i = 0; i < transactionCount_; ++i)
        transactions_[i] = other.transactions_[i];
}

DigitalWallet::DigitalWallet(DigitalWallet&& other) noexcept //move constructorul
    : ownerName_(other.ownerName_),                                 
      transactions_(other.transactions_),
      transactionCount_(other.transactionCount_),
      capacity_(other.capacity_) {
    std::cout << "[move ctor] fura de la "                       
              << (other.ownerName_ ? other.ownerName_ : "(fara nume)") << "\n";
    other.ownerName_ = nullptr;      //ca sa evitam folosirea aceleiasi zone de memorie la eliberare, stergem datele din other
    other.transactions_ = nullptr;
    other.transactionCount_ = 0;
    other.capacity_ = 0;
}

DigitalWallet& DigitalWallet::operator=(const DigitalWallet& other) { //copy assignment
    std::cout << "[copy assign] <= "                                
              << (other.ownerName_ ? other.ownerName_ : "(null)") << "\n";
    if (this == &other) return *this;                               

    //prima oara alocam noile resurse
    char* newOwner = duplicateCString(other.ownerName_);            
    int*  newTx    = other.capacity_ ? new int[other.capacity_] : nullptr; 
    for (std::size_t i = 0; i < other.transactionCount_; ++i)       
        newTx[i] = other.transactions_[i];

    //stergem vechile resurse
    delete[] ownerName_;
    delete[] transactions_;

    //si acum transferam din nou resursele
    ownerName_ = newOwner;
    transactions_ = newTx;
    transactionCount_ = other.transactionCount_;
    capacity_ = other.capacity_;

    return *this;  //noua zona de memorie e pe noul owner
}

DigitalWallet& DigitalWallet::operator=(DigitalWallet&& other) noexcept { //move assignment
    std::cout << "[move assign] <= "                                
              << (other.ownerName_ ? other.ownerName_ : "(null)") << "\n";
    if (this == &other) return *this;                               

    //prima oara stergem resursele curente
    delete[] ownerName_;
    delete[] transactions_;

    //copiem pointerii si datele din vechile resurse
    ownerName_ = other.ownerName_;
    transactions_ = other.transactions_;
    transactionCount_ = other.transactionCount_;
    capacity_ = other.capacity_;

    //ca sa evitam folosirea aceleiasi zone de memorie , stergem datele din other
    other.ownerName_ = nullptr;
    other.transactions_ = nullptr;
    other.transactionCount_ = 0;
    other.capacity_ = 0;

    return *this;  //noua zona de memorie e pe noul owner
}

DigitalWallet::~DigitalWallet() { //destructorul care elibereaza toate zonele de memorie
    std::cout << "[dtor] DigitalWallet(detinator = "                      
              << (ownerName_ ? ownerName_ : "(null)") << ")\n";
    delete[] ownerName_;                                            
    delete[] transactions_;                                         
}

void DigitalWallet::addTransaction(int amount) {
    ensureCapacity(transactionCount_ + 1);                          
    transactions_[transactionCount_++] = amount;                    
}

int DigitalWallet::transactionAt(std::size_t index) const {
    if (index >= transactionCount_)                                 
        throw std::out_of_range("index out of range");              
    return transactions_[index];                                     
}

void DigitalWallet::print(std::ostream& os) const {
    os << "Wallet(" << (ownerName_ ? ownerName_ : "(null)") << ") [" 
       << transactionCount_ << " tx] = { ";
    for (std::size_t i = 0; i < transactionCount_; ++i) {          
        os << transactions_[i];                                    
        if (i + 1 < transactionCount_) os << ", ";                  
    }
    os << " }\n";                                                   
}
