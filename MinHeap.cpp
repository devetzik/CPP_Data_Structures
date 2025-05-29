#include "MinHeap.h"

// Constructor
MinHeap::MinHeap() {
    capacity = 4;
    size = 0;
    arr = new int[capacity];
}


// αν ο πίνακας είναι γεμάτος, διπλασιάζει τη χωρητικότητα
void MinHeap::ensureCapacity() {
    if (size < capacity) return;
    int newCap = capacity * 2;
    int* newArr = new int[newCap];
    for (int i = 0; i < size; ++i) {
		newArr[i] = arr[i];      // Αντιγράφει τα παλιά στοιχεία
    }
    delete[] arr;
    arr = newArr;
    capacity = newCap;
}


// μετά από εισαγωγή, φροντίζουμε να μην παραβιάζεται η ιδιότητα min-heap
void MinHeap::heapifyUp(int idx) {
    while (idx > 0) {    // όσο δεν φτάσαμε στη ρίζα και το στοιχείο < γονέα, κάνουμε swap
        int parent = (idx - 1) / 2;
        if (arr[idx] < arr[parent]) {
            int tmp = arr[idx];
            arr[idx] = arr[parent];
            arr[parent] = tmp;
            idx = parent;
        }
        else {
            break;
        }
    }
}


// μετά από διαγραφή της ρίζας, φέρνουμε το τελευταίο στοιχείο πάνω
void MinHeap::heapifyDown(int idx) {
    while (true) {    // όσο έχει παιδιά και παραβιάζεται η ιδιότητα, κάνει swap με το μικρότερο παιδί
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = idx;
        if (left < size && arr[left] < arr[smallest]) {
            smallest = left;
        }
        if (right < size && arr[right] < arr[smallest]) {
            smallest = right;
        }
        if (smallest != idx) {
            int tmp = arr[idx];
            arr[idx] = arr[smallest];
            arr[smallest] = tmp;
            idx = smallest;
        }
        else {
            break;
        }
    }
}


// προσθέτει το νέο στοιχείο στο τέλος και εξισορροπεί προς τα πάνω
void MinHeap::insert(int value) {
    ensureCapacity();
    arr[size] = value;
    size++;
    heapifyUp(size - 1);
}


// επιστρέφει το στοιχείο στη ρίζα του σωρού ή -1 αν είναι άδειος
int MinHeap::getMin() {
    if (size == 0) return -1;
    return arr[0];
}


// αφαιρεί και επιστρέφει το ελάχιστο στοιχείο (ρίζα) ή -1 αν είναι άδειος
int MinHeap::deleteMin() {
    if (size == 0) return -1;
    int minValue = arr[0];
    arr[0] = arr[size - 1];
    size--;
    heapifyDown(0);
    return minValue;
}


// επιστρέφει πόσα στοιχεία περιέχει ο σωρός
int MinHeap::getSize() {
    return size;
}


// κατασκευάζει σωρό από πίνακα
void MinHeap::buildFromArray(int* data, int count) {
    delete[] arr;    // απελευθερώνει παλιό πίνακα
    capacity = count * 2;
    size = count;
    arr = new int[capacity];
    for (int i = 0; i < count; i++) {
        arr[i] = data[i];    // αντιγράφει τα δεδομένα

    }
    for (int i = count / 2 - 1; i >= 0; i--) {
        heapifyDown(i);    // χτίζει σωρό με heapifyDown από τα μέσα
    }
}