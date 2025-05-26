#include "MinHeap.h"
#include <cstring>

MinHeap::MinHeap() {
    capacity = 4;
    size = 0;
    arr = new int[capacity];
}

MinHeap::~MinHeap() {
    delete[] arr;
}

void MinHeap::ensureCapacity() {
    if (size < capacity) return;
    int newCap = capacity * 2;
    int* newArr = new int[newCap];
    // αντιγράφουμε τα παλιά στοιχεία
    memcpy(newArr, arr, size * sizeof(int));
    delete[] arr;
    arr = newArr;
    capacity = newCap;
}

void MinHeap::heapifyUp(int idx) {
    // όσο δεν φτάσαμε στη ρίζα και το στοιχείο < γονέα, κάνουμε swap
    while (idx > 0) {
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
    // όσο έχουμε παιδιά και παραβιάζεται η ιδιότητα, κάνουμε swap με το μικρότερο παιδί
    while (true) {
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

int MinHeap::getSize() {
    return size;
}

void MinHeap::buildFromArray(int* data, int count) {
    // απελευθερώνουμε παλιό πίνακα
    delete[] arr;
    capacity = count * 2;
    size = count;
    arr = new int[capacity];
    // αντιγράφουμε τα δεδομένα
    for (int i = 0; i < count; i++) {
        arr[i] = data[i];
    }
    // χτίζουμε σωρό με heapifyDown από τα μέσα
    for (int i = count / 2 - 1; i >= 0; i--) {
        heapifyDown(i);
    }
}
