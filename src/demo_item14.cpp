#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

const std::string FILENAME = "shared_data.txt";
std::mutex fileMutex; //asta e mutexul
int sharedCounter = 0;

class Lock {
public:
    explicit Lock(std::mutex& m) : mutex_(m) {
        mutex_.lock(); //acquire mutex (lock)
    }
    
    ~Lock() {
        mutex_.unlock(); //release mutex (unlock)
    }
    
    //nterzicem copierea, deoarece daca copiem , dtor copiei poate sa deblocheze mutexul fara sa dorim
    Lock(const Lock&) = delete;
    Lock& operator=(const Lock&) = delete;
    
private:
    std::mutex& mutex_;
};

//nesicronizat(race condition)
void unsafeWriter(int id) {
    for (int i = 0; i < 5; ++i) {
        std::ofstream file(FILENAME, std::ios::app);
        file << "UnsafeWriter" << id << ": " << i << "\n";
        // file.close() automat, dar scrierile se pot incaleca
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

//sincronizat(RAII lock)
void safeWriter(int id) {
    for (int i = 0; i < 5; ++i) {
        Lock lock(fileMutex); //se face lock
        std::ofstream file(FILENAME, std::ios::app);
        file << "SafeWriter" << id << ": " << i << "\n";
        sharedCounter++;
        //lockul de distruge automat
    }
}

void safeReader() {
    for (int i = 0; i < 5; ++i) {
        Lock lock(fileMutex);//asteapta sa se termine scrisul
        
        std::ifstream file(FILENAME);
        std::string line;
        while(std::getline(file, line)) { } //aici citim
        //aici se deblocheaza automat
    }
}

int main() {
    //Unsafe demo
    std::cout << "--- Start Unsafe Threads ---\n";
    std::remove(FILENAME.c_str());
    
    std::thread t1(unsafeWriter, 1);
    std::thread t2(unsafeWriter, 2);
    t1.join(); t2.join();
    std::cout << "Unsafe terminat (verifica fisierul pentru linii corupte).\n";

    //Safe demo
    std::cout << "\n--- Start Safe Threads (RAII Lock) ---\n";
    std::remove(FILENAME.c_str());
    sharedCounter = 0;

    std::thread t3(safeWriter, 3);
    std::thread t4(safeWriter, 4);
    std::thread t5(safeReader); // Cititor concurent

    t3.join(); t4.join(); t5.join();
    
    std::cout << "Safe terminat. Counter (asteptat 10): " << sharedCounter << "\n";
    
    // Lock l1(fileMutex);
    // Lock l2 = l1; //aici ar trebui sa fie eroare de compilare ca incearca sa dea call la ceva desja "sters"
    
    return 0;
}