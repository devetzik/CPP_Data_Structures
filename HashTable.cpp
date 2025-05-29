#include "Hashtable.h"
#include <fstream>

const double LOAD_FACTOR = 0.75; // Όριο πληρότητας για επανακατασκευή


// Constructor
Hashtable::Hashtable(){
    table = nullptr;
    capacity = 0;
    size = 0;
}

void Hashtable::rehash() {
    int oldCap = capacity;
    int* oldTbl = table;
    if (capacity == 0) {         // Νέο μέγεθος
        capacity = 4;
    }
    else {
        capacity = capacity * 2;
    }
    table = new int[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i] = INT_MIN;    // Αρχικοποίηση για «κενή» θέση
    }
    size = 0;

    for (int i = 0; i < oldCap; ++i) {
        if (oldTbl[i] != INT_MIN) {
            insert(oldTbl[i]);    // Επανατοποθέτηση παλιών στοιχείων
        }
    }
    delete[] oldTbl;
}


// Συνάρτηση κατακερματισμού
int Hashtable::hashFunction(int key) {
    return key % capacity;
}


void Hashtable::insert(int key) {
    // rehash αν load factor πολύ μεγάλος ή αν ο πίνακας άδειος
    if (capacity == 0 || (double)size / capacity > LOAD_FACTOR) {
        rehash();
    }
    int idx = hashFunction(key);
    // Γραμμική διερεύνηση μέχρι sentinel
    while (table[idx] != INT_MIN) {
        if (table[idx] == key) {
            return;  // υπάρχει ήδη
        }
        idx = (idx + 1) % capacity;
    }
    table[idx] = key;
    size++;
}


// Αναζήτηση στοιχείου στον πίνακα
bool Hashtable::search(int key){
    if (capacity == 0) return false;
    int idx = hashFunction(key);
    int start = idx;
    // Ψάχνουμε μέχρι να πέσουμε σε sentinel ή να βρούμε το key
    while (table[idx] != INT_MIN) {
        if (table[idx] == key) {
            return true;
        }
        idx = (idx + 1) % capacity;
        if (idx == start) break;
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
