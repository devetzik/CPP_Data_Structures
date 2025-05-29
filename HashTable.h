#ifndef HASHTABLE_H
#define HASHTABLE_H

class Hashtable {
private:
    int* table;     // πίνακας κλειδιών
    int capacity;   // μέγεθος πίνακα
    int size;       // πόσα στοιχεία έχουμε

    int hashFunction(int key); // key mod capacity
    void rehash();             // διπλασιασμός πίνακα όταν γεμίσει

public:
    Hashtable();

    void buildFromArray(const char* filename); // διαβάζει και κάνει insert από αρχείο
    void insert(int key);
    bool search(int key);
    int getSize();
};

#endif
