#include "MinHeap.h"
#include <cstring>

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
    memcpy(newArr, arr, size * sizeof(int));    // αντιγράφουμε τα παλιά στοιχεία
    delete[] arr;
    arr = newArr;
    capacity = newCap;
}

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