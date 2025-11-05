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

char* DigitalWallet::dupCString(const char* s) {
    return safeDup(s);
}

void DigitalWallet::ensureCapacity(std::size_t minCap) {
    if (capacity_ >= minCap) return;
    std::size_t newCap = capacity_ ? capacity_ : 1;
    while (newCap < minCap) newCap *= 2;
    int* newData = new int[newCap];
    for (std::size_t i = 0; i < size_; ++i) newData[i] = tx_[i];
    delete[] tx_;
    tx_ = newData;
    capacity_ = newCap;
}

DigitalWallet::DigitalWallet(const char* owner, std::size_t initialCap)
    : owner_(dupCString(owner)),
      tx_(initialCap ? new int[initialCap] : nullptr),
      size_(0),
      capacity_(initialCap) {
    std::cout << "[ctor] DigitalWallet(owner=" << (owner_?owner_:"(null)") << ")\n";
}

DigitalWallet::DigitalWallet(const DigitalWallet& other)
    : owner_(dupCString(other.owner_)),
      tx_(other.capacity_ ? new int[other.capacity_] : nullptr),
      size_(other.size_),
      capacity_(other.capacity_) {
    std::cout << "[copy ctor] from " << (other.owner_?other.owner_:"(null)") << "\n";
    for (std::size_t i = 0; i < size_; ++i) tx_[i] = other.tx_[i];
}

DigitalWallet::DigitalWallet(DigitalWallet&& other) noexcept
    : owner_(other.owner_),
      tx_(other.tx_),
      size_(other.size_),
      capacity_(other.capacity_) {
    std::cout << "[move ctor] stealing from " << (other.owner_?other.owner_:"(null)") << "\n";
    other.owner_ = nullptr;
    other.tx_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

DigitalWallet& DigitalWallet::operator=(const DigitalWallet& other) {
    std::cout << "[copy assign] <= " << (other.owner_?other.owner_:"(null)") << "\n";
    if (this == &other) return *this;

    char* newOwner = dupCString(other.owner_);
    int*  newTx    = other.capacity_ ? new int[other.capacity_] : nullptr;
    for (std::size_t i = 0; i < other.size_; ++i) newTx[i] = other.tx_[i];

    delete[] owner_;
    delete[] tx_;

    owner_ = newOwner;
    tx_ = newTx;
    size_ = other.size_;
    capacity_ = other.capacity_;
    return *this;
}

DigitalWallet& DigitalWallet::operator=(DigitalWallet&& other) noexcept {
    std::cout << "[move assign] <= " << (other.owner_?other.owner_:"(null)") << "\n";
    if (this == &other) return *this;

    delete[] owner_;
    delete[] tx_;

    owner_ = other.owner_;
    tx_ = other.tx_;
    size_ = other.size_;
    capacity_ = other.capacity_;

    other.owner_ = nullptr;
    other.tx_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
    return *this;
}

DigitalWallet::~DigitalWallet() {
    std::cout << "[dtor] DigitalWallet(owner=" << (owner_?owner_:"(null)") << ")\n";
    delete[] owner_;
    delete[] tx_;
}

void DigitalWallet::addTransaction(int amount) {
    ensureCapacity(size_ + 1);
    tx_[size_++] = amount;
}

int DigitalWallet::at(std::size_t idx) const {
    if (idx >= size_) throw std::out_of_range("index out of range");
    return tx_[idx];
}

void DigitalWallet::print(std::ostream& os) const {
    os << "Wallet(" << (owner_?owner_:"(null)") << ") [" << size_ << " tx] = { ";
    for (std::size_t i = 0; i < size_; ++i) {
        os << tx_[i];
        if (i + 1 < size_) os << ", ";
    }
    os << " }\n";
}
