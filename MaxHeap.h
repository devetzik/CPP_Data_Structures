#ifndef MAXHEAP_H
#define MAXHEAP_H

class MaxHeap {
private:
    int* arr;       // Δυναμικός πίνακας που κρατά τα στοιχεία του σωρού
    int capacity;   // Συνολική χωρητικότητα του πίνακα
    int size;       // Τρέχον πλήθος στοιχείων στον σωρό

    void ensureCapacity();      // Διπλασιάζει τον πίνακα αν γεμίσει
    void heapifyUp(int index);  // Εξισορρόπηση προς τα πάνω μετά από insert
    void heapifyDown(int index);// Εξισορρόπηση προς τα κάτω μετά από delete

public:
    MaxHeap();                  // Constuctor

    void insert(int value);     // Εισάγει νέο στοιχείο στον σωρό
    int getMax();               // Επιστρέφει το μέγιστο στοιχείο (ρίζα), ή -1 αν κενό
    int deleteMax();            // Αφαιρεί και επιστρέφει το μέγιστο στοιχείο, ή -1 αν κενό
    int getSize();              // Επιστρέφει τον αριθμό στοιχείων στον σωρό
    void buildFromArray(int* data, int count); // Δημιουργεί σωρό από πίνακα δεδομένων
};

#endif
