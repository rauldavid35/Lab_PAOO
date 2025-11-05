#include "DigitalWallet.hpp"
#include <cstring>
#include <utility>
#include <stdexcept>

static char* safeDup(const char* s) {
    if (!s) return nullptr;
    const std::size_t n = std::strlen(s);
    char* p = new char[n + 1];
    std::memcpy(p, s, n + 1);
    return p;
}

char* DigitalWallet::duplicateCString(const char* s) { return safeDup(s); }

void DigitalWallet::ensureCapacity(std::size_t minCapacity) {
    if (capacity_ >= minCapacity) return;
    std::size_t newCap = capacity_ ? capacity_ : 1;
    while (newCap < minCapacity) newCap *= 2;
    int* newData = new int[newCap];
    for (std::size_t i = 0; i < transactionCount_; ++i) newData[i] = transactions_[i];
    delete[] transactions_;
    transactions_ = newData;
    capacity_ = newCap;
}

// ctor „de bază”
DigitalWallet::DigitalWallet(const char* ownerName, std::size_t initialCapacity)
    : ownerName_(duplicateCString(ownerName)), transactions_(initialCapacity ? new int[initialCapacity] : nullptr), transactionCount_(0), capacity_(initialCapacity) {
    std::cout << "[ctor] DigitalWallet(owner=" << (ownerName_ ? ownerName_ : "(null)") << ")\n";
}

// copy-ctor
DigitalWallet::DigitalWallet(const DigitalWallet& other)
    : ownerName_(duplicateCString(other.ownerName_)), transactions_(other.capacity_ ? new int[other.capacity_] : nullptr), transactionCount_(other.transactionCount_), capacity_(other.capacity_) {
    std::cout << "[copy ctor] from " << (other.ownerName_ ? other.ownerName_ : "(null)") << "\n";
    for (std::size_t i = 0; i < transactionCount_; ++i) transactions_[i] = other.transactions_[i];
}

// move-ctor
DigitalWallet::DigitalWallet(DigitalWallet&& other) noexcept
    : ownerName_(other.ownerName_), transactions_(other.transactions_), transactionCount_(other.transactionCount_), capacity_(other.capacity_) {
    std::cout << "[move ctor] stealing from " << (other.ownerName_ ? other.ownerName_ : "(null)") << "\n";
    other.ownerName_ = nullptr;
    other.transactions_ = nullptr;
    other.transactionCount_ = 0;
    other.capacity_ = 0;
}

// copy-assign
DigitalWallet& DigitalWallet::operator=(const DigitalWallet& other) {
    std::cout << "[copy assign] <= " << (other.ownerName_ ? other.ownerName_ : "(null)") << "\n";
    if (this == &other) return *this;

    char* newOwner = duplicateCString(other.ownerName_);
    int*  newTx    = other.capacity_ ? new int[other.capacity_] : nullptr;
    for (std::size_t i = 0; i < other.transactionCount_; ++i) newTx[i] = other.transactions_[i];

    delete[] ownerName_;
    delete[] transactions_;

    ownerName_ = newOwner;
    transactions_ = newTx;
    transactionCount_ = other.transactionCount_;
    capacity_ = other.capacity_;
    return *this;
}

// move-assign
DigitalWallet& DigitalWallet::operator=(DigitalWallet&& other) noexcept {
    std::cout << "[move assign] <= " << (other.ownerName_ ? other.ownerName_ : "(null)") << "\n";
    if (this == &other) return *this;

    delete[] ownerName_;
    delete[] transactions_;

    ownerName_ = other.ownerName_;
    transactions_ = other.transactions_;
    transactionCount_ = other.transactionCount_;
    capacity_ = other.capacity_;

    other.ownerName_ = nullptr;
    other.transactions_ = nullptr;
    other.transactionCount_ = 0;
    other.capacity_ = 0;
    return *this;
}

DigitalWallet::~DigitalWallet() {
    std::cout << "[dtor] DigitalWallet(owner=" << (ownerName_ ? ownerName_ : "(null)") << ")\n";
    delete[] ownerName_;
    delete[] transactions_;
}

void DigitalWallet::addTransaction(int amount) {
    ensureCapacity(transactionCount_ + 1);
    transactions_[transactionCount_++] = amount;
}

int DigitalWallet::transactionAt(std::size_t index) const {
    if (index >= transactionCount_) throw std::out_of_range("index out of range");
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
