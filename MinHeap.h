#ifndef MINHEAP_H
#define MINHEAP_H

// Σωρός ελαχίστων (MinHeap)
class MinHeap {
private:
    int* arr;        // δυναμικός πίνακας με τα στοιχεία
    int size;        // πόσα στοιχεία έχει τώρα
    int capacity;    // πόσα χωράει ο πίνακας

    // Βοηθητικές μέθοδοι για διατήρηση της ιδιότητας heap
    void ensureCapacity();     // διπλασιάζει τον πίνακα όταν γεμίσει
    void heapifyUp(int idx);   // φέρνει το στοιχείο στη σωστή θέση προς τα πάνω
    void heapifyDown(int idx); // φέρνει το στοιχείο στη σωστή θέση προς τα κάτω

public:
    MinHeap();                 // constructor
    ~MinHeap();                // destructor

    void insert(int value);    // εισαγωγή νέου στοιχείου
    int getMin();              // επιστρέφει το ελάχιστο (ρίζα) ή -1 αν άδειος
    int deleteMin();           // αφαιρεί και επιστρέφει το ελάχιστο ή -1 αν άδειος
    int getSize();             // πόσα στοιχεία έχει
    void buildFromArray(int* data, int count); // κατασκευάζει σωρό από πίνακα
};

#endif // MINHEAP_H
