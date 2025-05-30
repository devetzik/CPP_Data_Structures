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
void readFileToArray(std::string& filename, int*& outArr, int& outCount) {
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
    

	std::ifstream commands("commands.txt");    // Διαβάζει τις εντολές από το αρχείο commands.txt
	std::ofstream output("output.txt");        // Γράφει τα αποτελέσματα στο αρχείο output.txt
	if (!commands.is_open() || !output.is_open()) {       // Έλεγχος αν τα αρχεία άνοιξαν σωστά
        std::cerr << "Δεν βρέθηκε commands.txt ή output.txt\n";
        return 1;
    }

    std::string cmd, s;
	while (commands >> cmd >> s) {       // Διαβάζει την εντολή και το όνομα της δομής
        auto start = std::chrono::high_resolution_clock::now();   // Αρχή χρονομέτρησης
        std::string res="FAILURE";
       
		if (cmd == "BUILD") {           // Εντολή για κατασκευή δομής από αρχείο
            std::string fname;
            commands >> fname;

            if (s == "MINHEAP" || s == "MAXHEAP" || s == "AVLTREE"){
                int* arr, count;
                readFileToArray(fname, arr, count);

                if (s == "MINHEAP") {
                    minHeap.buildFromArray(arr, count);
                }
                else if (s == "MAXHEAP") {
                    maxHeap.buildFromArray(arr, count);
                }
                else { // AVLTREE
                    avlTree.buildFromArray(arr, count);
                }

                delete[] arr;
                res = "SUCCESS";
            }
            else if (s == "GRAPH") {
                std::ifstream f(fname);
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
                res = "SUCCESS";
            }
            else if (s == "HASHTABLE") {
                hashtable.buildFromArray(fname.c_str());
                res = "SUCCESS";
            }
        }
		else if (cmd == "GETSIZE") {          // Εντολή για να πάρουμε το μέγεθος της δομής
            if (s == "MINHEAP") {
                res = std::to_string(minHeap.getSize());
            }
            else if (s == "MAXHEAP") {
                res = std::to_string(maxHeap.getSize());
            }
            else if (s == "AVLTREE") {
                res = std::to_string(avlTree.getSize());
            }
            else if (s == "GRAPH") {
                int V, E;
                graph.getSize(V, E);
                res = std::to_string(V) + " " + std::to_string(E);
            }
            else if (s == "HASHTABLE") {
                res = std::to_string(hashtable.getSize());
            }
        }
		else if (cmd == "FINDMIN") {        // Eλάχιστο στοιχείο δομής
            if (s == "MINHEAP") {
                res = std::to_string(minHeap.getMin());
            }
            else if (s == "AVLTREE") {
                res = std::to_string(avlTree.findMin());
            }
        }
		else if (cmd == "FINDMAX") {         // Μέγιστο στοιχείο δομής
            if (s == "MAXHEAP") {
                res = std::to_string(maxHeap.getMax());
            }
        }
		else if (cmd == "SEARCH") {          // Αναζήτηση στοιχείου
            int key;
            commands >> key;
            
            if (s == "AVLTREE") {
                if (avlTree.search(key)) {
                    res = "SUCCESS";
                }
            }
            else if (s == "HASHTABLE") {
                if (hashtable.search(key)) {
                    res = "SUCCESS";
                }
            }
        }
		else if (cmd == "INSERT") {           // Εισαγωγή στοιχείου στη δομή
            int x;
            if (s == "MINHEAP") {
                commands >> x;
                minHeap.insert(x);
                res = "SUCCESS";
            }
            else if (s == "MAXHEAP") {
                commands >> x;
                maxHeap.insert(x);
                res = "SUCCESS";
            }
            else if (s == "AVLTREE") {
                commands >> x;
                avlTree.insert(x);
                res = "SUCCESS";
            }
            else if (s == "HASHTABLE") {
                commands >> x;
                hashtable.insert(x);
                res = "SUCCESS";
            }
            else if (s == "GRAPH") {
                int a, b, c;
                commands >> a >> b >> c;
                graph.insertEdge(a, b, c);
                res = "SUCCESS";
            }
        }
		else if (cmd == "DELETEMIN") {       // Διαγραφή ελάχιστου στοιχείου από τη δομή
            if (s == "MINHEAP") {
                res = std::to_string(minHeap.deleteMin());
            }
        }
		else if (cmd == "DELETEMAX") {      // Διαγραφή μέγιστου στοιχείου από τη δομή
            if (s == "MAXHEAP") {
                res = std::to_string(maxHeap.deleteMax());
            }
        }
		else if (cmd == "DELETE") {         // Διαγραφή συγκεκριμένου στοιχείου από τη δομή
            if (s == "AVLTREE") {
                int k;
                commands >> k;
                if (avlTree.search(k)) {
                    avlTree.deleteKey(k);
                    res = "SUCCESS";
                }
            }
            else if (s == "GRAPH") {
                int a, b;
                commands >> a >> b;
                graph.deleteEdge(a, b);
                res = "SUCCESS";
            }
        }
		else if (cmd == "COMPUTESHORTESTPATH") {     // Υπολογισμός συντομότερης διαδρομής
            int a, b;
            commands >> a >> b;
            if (s == "GRAPH") {
                int d = graph.computeShortestPath(a, b);

                if (d > 0) {
                    res = std::to_string(d);
                }
            }
        }
		else if (cmd == "COMPUTESPANNINGTREE") {     // Υπολογισμός ελάχιστου δέντρου
            if (s == "GRAPH") {
                res = std::to_string(graph.computeSpanningTree());
            }
        }
		else if (cmd == "FINDCONNECTEDCOMPONENTS") {     // Υπολογισμός συνιστωσών
            if (s == "GRAPH") {
                res = std::to_string(graph.findConnectedComponents());
            }
        }

        auto end = std::chrono::high_resolution_clock::now();     // Λήξη χρονομέτρησης
        auto diarkeia = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();    // Υπολογισμός διάρκειας
        output << res << " " << diarkeia << "us\n";                 // Εγγραφή του αποτελέσματος στο output.txt
    }

    commands.close();
    output.close();
    return 0;
}