#include "MaxHeap.h"
#include <cstring>

// Constructor
MaxHeap::MaxHeap() {
    capacity = 4;    // αρχικά μπορούμε να αποθηκεύσουμε 4 στοιχεία
    size = 0;        // κανένα στοιχείο ακόμη
    arr = new int[capacity];
}


// αν ο πίνακας είναι γεμάτος, διπλασιάζει τη χωρητικότητα
void MaxHeap::ensureCapacity() {
    if (size < capacity) return;    // ακόμα υπάρχει χώρος
    int newCap = capacity * 2;      // διπλασιασμός
    int* newArr = new int[newCap];
    memcpy(newArr, arr, size * sizeof(int));    // Αντιγράφει τα παλιά στοιχεία
    delete[] arr;                   // απελευθερώνει τον παλιό πίνακα
    arr = newArr;
    capacity = newCap;
}

// μετά από εισαγωγή, φροντίζουμε να μην παραβιάζεται η ιδιότητα max-heap
void MaxHeap::heapifyUp(int index) {
    while (index > 0) {    // όσο δεν είμαστε στη ρίζα και το παιδί > γονέα, κάνουμε swap
        int parent = (index - 1) / 2;
        if (arr[index] > arr[parent]) {
            int tmp = arr[index];
            arr[index] = arr[parent];
            arr[parent] = tmp;
            index = parent;
        }
        else {
            break;
        }
    }
}

// μετά από διαγραφή της ρίζας, φέρνουμε το τελευταίο στοιχείο πάνω
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
            break;
        }
    }
}

// προσθέτει το νέο στοιχείο στο τέλος και εξισορροπεί προς τα πάνω
void MaxHeap::insert(int value) {
    ensureCapacity();        // βεβαιωνόμαστε ότι υπάρχει χώρος
    arr[size] = value;       // βάζουμε το νέο στοιχείο
    size++;
    heapifyUp(size - 1);     // διορθώνουμε τη δομή
}

// επιστρέφει το στοιχείο στη ρίζα του σωρού ή -1 αν είναι άδειος
int MaxHeap::getMax() {
    if (size == 0) return -1;
    return arr[0];
}

// αφαιρεί το μέγιστο (ρίζα), φέρνει το τελευταίο στοιχείο πάνω
// και εξισορροπεί προς τα κάτω
int MaxHeap::deleteMax() {
    if (size == 0) return -1;
    int maxValue = arr[0];
    arr[0] = arr[size - 1];
    size--;
    heapifyDown(0);
    return maxValue;
}

// επιστρέφει πόσα στοιχεία περιέχει ο σωρός
int MaxHeap::getSize() {
    return size;
}

// κατασκευάζει σωρό από πίνακα
void MaxHeap::buildFromArray(int* data, int count) {
    delete[] arr;    // απελευθερώνει τον παλιό πίνακα
	capacity = count * 2;    // διπλή χωρητικότητα
    size = count;
    arr = new int[capacity];

    for (int i = 0; i < count; i++) {
        arr[i] = data[i];    // αντιγραφή δεδομένων
    }
    
    for (int i = count / 2 - 1; i >= 0; i--) {
		heapifyDown(i);  // χτίσιμο του σωρού
    }
}
