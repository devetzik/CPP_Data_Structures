#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "MinHeap.h"
#include "MaxHeap.h"
#include "AVLTree.h"
#include "Graph.h"
#include "Hashtable.h"

// Βοηθητική συνάρτηση: διαβάζει όλα τα ints από ένα αρχείο
// σε δυναμικό πίνακα και επιστρέφει τον πίνακα + το πλήθος.
void readFileToArray(const std::string& filename, int*& outArr, int& outCount) {
    std::ifstream f(filename);
    int v;
    outCount = 0;
    while (f >> v) {
        outCount++;
    }
    f.clear();
    f.seekg(0);
    outArr = new int[outCount];
    for (int i = 0; i < outCount; ++i) {
        f >> outArr[i];
    }
    f.close();
}

int main() {
    MinHeap    minHeap;
    MaxHeap    maxHeap;
    AVLTree    avlTree;
    Graph      graph;
    Hashtable  hashtable;

    std::ifstream commands("commands.txt");
    std::ofstream output("output.txt");
    if (!commands.is_open() || !output.is_open()) {
        std::cerr << "Σφάλμα: δεν μπόρεσα να ανοίξω commands.txt ή output.txt\n";
        return 1;
    }

    std::string cmd, structure;
    while (commands >> cmd >> structure) {
        auto start = std::chrono::high_resolution_clock::now();
        std::string result;

        if (cmd == "BUILD") {
            std::string filename;
            commands >> filename;

            // ομαδοποιημένη κατασκευή MinHeap/MaxHeap/AVLTree
            if (structure == "MINHEAP" || structure == "MAXHEAP" || structure == "AVLTREE"){
                int* arr, count;
                readFileToArray(filename, arr, count);

                if (structure == "MINHEAP") {
                    minHeap.buildFromArray(arr, count);
                }
                else if (structure == "MAXHEAP") {
                    maxHeap.buildFromArray(arr, count);
                }
                else { // AVLTREE
                    avlTree.buildFromArray(arr, count);
                }

                delete[] arr;
                result = "SUCCESS";
            }
            else if (structure == "GRAPH") {
                std::ifstream f(filename);
                int u, v, w, maxNode = -1;
                while (f >> u >> v >> w) {
                    if (u > maxNode) maxNode = u;
                    if (v > maxNode) maxNode = v;
                }
                f.clear();
                f.seekg(0);
                graph.buildGraph(maxNode + 1);
                while (f >> u >> v >> w) {
                    graph.insertEdge(u, v, w);
                }
                f.close();
                result = "SUCCESS";
            }
            else if (structure == "HASHTABLE") {
                hashtable.buildFromArray(filename.c_str());
                result = "SUCCESS";
            }
            else {
                result = "FAILURE";
            }
        }
        else if (cmd == "GETSIZE") {
            if (structure == "MINHEAP") {
                result = std::to_string(minHeap.getSize());
            }
            else if (structure == "MAXHEAP") {
                result = std::to_string(maxHeap.getSize());
            }
            else if (structure == "AVLTREE") {
                result = std::to_string(avlTree.getSize());
            }
            else if (structure == "GRAPH") {
                int V, E;
                graph.getSize(V, E);
                result = std::to_string(V) + " " + std::to_string(E);
            }
            else if (structure == "HASHTABLE") {
                result = std::to_string(hashtable.getSize());
            }
            else {
                result = "FAILURE";
            }
        }
        else if (cmd == "FINDMIN") {
            if (structure == "MINHEAP")    result = std::to_string(minHeap.getMin());
            else if (structure == "AVLTREE")    result = std::to_string(avlTree.findMin());
            else                                result = "FAILURE";
        }
        else if (cmd == "FINDMAX") {
            if (structure == "MAXHEAP")    result = std::to_string(maxHeap.getMax());
            else                                result = "FAILURE";
        }
        else if (cmd == "SEARCH") {
            int key;
            commands >> key;
            bool ok = (structure == "AVLTREE" ? avlTree.search(key)
                : structure == "HASHTABLE" ? hashtable.search(key)
                : false);
            result = ok ? "SUCCESS" : "FAILURE";
        }
        else if (cmd == "INSERT") {
            if (structure == "MINHEAP") {
                int x; commands >> x;
                minHeap.insert(x);
                result = "SUCCESS";
            }
            else if (structure == "MAXHEAP") {
                int x; commands >> x;
                maxHeap.insert(x);
                result = "SUCCESS";
            }
            else if (structure == "AVLTREE") {
                int x; commands >> x;
                avlTree.insert(x);
                result = "SUCCESS";
            }
            else if (structure == "HASHTABLE") {
                int x; commands >> x;
                hashtable.insert(x);
                result = "SUCCESS";
            }
            else if (structure == "GRAPH") {
                int a, b, c;
                commands >> a >> b >> c;
                graph.insertEdge(a, b, c);
                result = "SUCCESS";
            }
            else {
                result = "FAILURE";
            }
        }
        else if (cmd == "DELETEMIN") {
            if (structure == "MINHEAP")
                result = std::to_string(minHeap.deleteMin());
            else
                result = "FAILURE";
        }
        else if (cmd == "DELETEMAX") {
            if (structure == "MAXHEAP")
                result = std::to_string(maxHeap.deleteMax());
            else
                result = "FAILURE";
        }
        else if (cmd == "DELETE") {
            if (structure == "AVLTREE") {
                int k; commands >> k;
                if (avlTree.search(k)) {
                    avlTree.deleteKey(k);
                    result = "SUCCESS";
                }
                else {
                    result = "FAILURE";
                }
            }
            else if (structure == "GRAPH") {
                int a, b;
                commands >> a >> b;
                graph.deleteEdge(a, b);
                result = "SUCCESS";
            }
            else {
                // deleteKey στο Hashtable δεν υπάρχει
                result = "FAILURE";
            }
        }
        else if (cmd == "COMPUTESHORTESTPATH") {
            int a, b;
            commands >> a >> b;
            if (structure == "GRAPH") {
                int d = graph.computeShortestPath(a, b);
                result = (d < 0 ? "FAILURE" : std::to_string(d));
            }
            else {
                result = "FAILURE";
            }
        }
        else if (cmd == "COMPUTESPANNINGTREE") {
            if (structure == "GRAPH")
                result = std::to_string(graph.computeSpanningTree());
            else
                result = "FAILURE";
        }
        else if (cmd == "FINDCONNECTEDCOMPONENTS") {
            if (structure == "GRAPH")
                result = std::to_string(graph.findConnectedComponents());
            else
                result = "FAILURE";
        }
        else {
            result = "FAILURE"; // άγνωστη εντολή
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        output << result << " " << us << "us\n";
    }

    commands.close();
    output.close();
    return 0;
}