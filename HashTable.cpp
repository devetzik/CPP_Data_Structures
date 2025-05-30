#include "Hashtable.h"
#include <fstream>

const double LOAD_FACTOR = 0.75; // Όριο πληρότητας για επανακατασκευή


// Constructor
Hashtable::Hashtable(){
    table = nullptr;
	occupied = nullptr;
    capacity = 0;
    size = 0;
}


// Επανακατασκευή πίνακα όταν γεμίσει
void Hashtable::rehash() {
    int oldCap = capacity;
    int* oldTable = table;
    bool* oldOcc = occupied;

    capacity = (capacity == 0 ? 4 : capacity * 2);
    table = new int[capacity];
    occupied = new bool[capacity];
    for (int i = 0; i < capacity; ++i) {
        occupied[i] = false;      // αρχικά όλες οι θέσεις κενές
    }
    size = 0;

    for (int i = 0; i < oldCap; ++i) {
        if (oldOcc[i]) {
            insert(oldTable[i]);    // επανατοποθέτηση των παλιών στοιχείων
        }
    }

    delete[] oldTable;
    delete[] oldOcc;
}


// Συνάρτηση κατακερματισμού
int Hashtable::hashFunction(int key) {
    return key % capacity;
}


// Εισαγωγή νέου στοιχείου στον πίνακα
void Hashtable::insert(int key) {
    // κάνουμε rehash αν load factor υπερβαίνει
    if (capacity == 0 || (double)size / capacity > LOAD_FACTOR) {
        rehash();
    }
    int idx = hashFunction(key);
    while (occupied[idx]) {    // γραμμική διερεύνηση μέχρι κενή θέση
        if (table[idx] == key) {
            return;  // υπάρχει ήδη
        }
        idx = (idx + 1) % capacity;
    }
    table[idx] = key;    // βάζουμε το νέο κλειδί
    occupied[idx] = true;
    ++size;
}


// Αναζήτηση στοιχείου στον πίνακα
bool Hashtable::search(int key) {
    if (capacity == 0) return false;
    int idx = hashFunction(key);
    int start = idx;
    while (occupied[idx]) {    // ψάχνουμε μέχρι να πετύχουμε κενή θέση
        if (table[idx] == key) {
            return true;
        }
        idx = (idx + 1) % capacity;
        if (idx == start) break;  // κύκλος
    }
    return false;
}

// Επιστρέφει το πλήθος των στοιχείων
int Hashtable::getSize(){
    return size;
}


// Διαβάζει από αρχείο και κάνει insert τα στοιχεία στον πίνακα
void Hashtable::buildFromArray(const char* filename) {
    std::ifstream in(filename);
    int x;
    while (in >> x) {
        insert(x);
    }
    in.close();
}