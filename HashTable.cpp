#include "Hashtable.h"
#include <fstream>

const double LOAD_FACTOR = 0.75;

Hashtable::Hashtable() {
    table = nullptr;
    used = nullptr;
    capacity = 0;
    size = 0;
}

Hashtable::~Hashtable() {
    delete[] table;
    delete[] used;
}

int Hashtable::hashFunction(int key) {
    return key % capacity;
}

void Hashtable::rehash() {
    int oldCap = capacity;
    int* oldTable = table;
    bool* oldUsed = used;

    capacity = (capacity == 0 ? 4 : capacity * 2);
    table = new int[capacity];
    used = new bool[capacity];
    for (int i = 0; i < capacity; i++) used[i] = false;
    size = 0;

    for (int i = 0; i < oldCap; i++) {
        if (oldUsed[i]) {
            insert(oldTable[i]);
        }
    }
    delete[] oldTable;
    delete[] oldUsed;
}

void Hashtable::insert(int key) {
    if (capacity == 0 || (double)size / capacity > LOAD_FACTOR) {
        rehash();
    }
    int idx = hashFunction(key);
    while (used[idx]) {
        if (table[idx] == key) return;  // υπάρχει ήδη
        idx = (idx + 1) % capacity;
    }
    table[idx] = key;
    used[idx] = true;
    size++;
}

bool Hashtable::search(int key) {
    if (capacity == 0) return false;
    int idx = hashFunction(key);
    int start = idx;
    while (used[idx]) {
        if (table[idx] == key) return true;
        idx = (idx + 1) % capacity;
        if (idx == start) break;
    }
    return false;
}

void Hashtable::deleteKey(int key) {
    if (capacity == 0) return;
    int idx = hashFunction(key);
    int start = idx;
    while (used[idx]) {
        if (table[idx] == key) {
            used[idx] = false;
            size--;
            return;
        }
        idx = (idx + 1) % capacity;
        if (idx == start) break;
    }
}

int Hashtable::getSize() {
    return size;
}

void Hashtable::buildFromArray(const char* filename) {
    std::ifstream in(filename);
    int x;
    while (in >> x) {
        insert(x);
    }
    in.close();
}
