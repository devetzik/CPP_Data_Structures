#include "MaxHeap.h"
#include <cstring>  // για memcpy

// Κατασκευαστής: αρχικοποιεί με μικρή αρχική χωρητικότητα
MaxHeap::MaxHeap() {
    capacity = 4;    // αρχικά μπορούμε να αποθηκεύσουμε 4 στοιχεία
    size = 0;        // κανένα στοιχείο ακόμη
    arr = new int[capacity];
}

// Καταστροφέας: απελευθερώνει τη μνήμη που δεσμεύτηκε
MaxHeap::~MaxHeap() {
    delete[] arr;
}

// ensureCapacity: αν ο πίνακας είναι γεμάτος, διπλασιάζουμε τη χωρητικότητα
void MaxHeap::ensureCapacity() {
    if (size < capacity) return;    // ακόμα υπάρχει χώρος
    int newCap = capacity * 2;      // διπλασιασμός
    int* newArr = new int[newCap];
    // Αντιγράφουμε τα παλιά στοιχεία
    memcpy(newArr, arr, size * sizeof(int));
    delete[] arr;                   // απελευθερώνουμε τον παλιό πίνακα
    arr = newArr;
    capacity = newCap;
}

// heapifyUp: μετά από εισαγωγή, φροντίζουμε να μην παραβιάζεται η ιδιότητα max-heap
void MaxHeap::heapifyUp(int index) {
    // όσο δεν είμαστε στη ρίζα και το παιδί > γονέα, κάνουμε swap
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (arr[index] > arr[parent]) {
            int tmp = arr[index];
            arr[index] = arr[parent];
            arr[parent] = tmp;
            index = parent;
        }
        else {
            break;  // η ιδιότητα διατηρείται
        }
    }
}

// heapifyDown: μετά από διαγραφή της ρίζας, φέρνουμε το τελευταίο στοιχείο πάνω
// και διορθώνουμε προς τα κάτω ώστε να διατηρείται το max-heap
void MaxHeap::heapifyDown(int index) {
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < size && arr[left] > arr[largest]) {
            largest = left;
        }
        if (right < size && arr[right] > arr[largest]) {
            largest = right;
        }
        if (largest != index) {
            int tmp = arr[index];
            arr[index] = arr[largest];
            arr[largest] = tmp;
            index = largest;
        }
        else {
            break; // η ιδιότητα δεν παραβιάζεται πλέον
        }
    }
}

// insert: προσθέτουμε το νέο στοιχείο στο τέλος και εξισορροπούμε προς τα πάνω
void MaxHeap::insert(int value) {
    ensureCapacity();        // βεβαιωνόμαστε ότι υπάρχει χώρος
    arr[size] = value;       // βάζουμε το νέο στοιχείο
    size++;
    heapifyUp(size - 1);     // διορθώνουμε τη δομή
}

// getMax: επιστρέφει το στοιχείο στη ρίζα του σωρού ή -1 αν είναι άδειος
int MaxHeap::getMax() {
    if (size == 0) return -1;
    return arr[0];
}

// deleteMax: αφαιρεί το μέγιστο (ρίζα), φέρνει το τελευταίο στοιχείο πάνω
// και εξισορροπεί προς τα κάτω
int MaxHeap::deleteMax() {
    if (size == 0) return -1;
    int maxValue = arr[0];
    arr[0] = arr[size - 1];
    size--;
    heapifyDown(0);
    return maxValue;
}

// getSize: επιστρέφει πόσα στοιχεία περιέχει ο σωρός
int MaxHeap::getSize() {
    return size;
}

// buildFromArray: κατασκευάζουμε σωρό από παρεχόμενο πίνακα δεδομένων
void MaxHeap::buildFromArray(int* data, int count) {
    // απελευθερώνουμε παλιό πίνακα
    delete[] arr;
    capacity = count * 2;    // επιλέγουμε λίγο μεγαλύτερη χωρητικότητα
    size = count;
    arr = new int[capacity];
    // αντιγράφουμε τα δεδομένα
    for (int i = 0; i < count; i++) {
        arr[i] = data[i];
    }
    // χτίζουμε το σωρό από τα μέσα προς τη ρίζα
    for (int i = count / 2 - 1; i >= 0; i--) {
        heapifyDown(i);
    }
}
