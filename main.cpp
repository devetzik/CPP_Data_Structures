#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include "MinHeap.h"
#include "MaxHeap.h"
#include "AVLTree.h"
#include "Graph.h"
#include "Hashtable.h"

int main() {
    MinHeap    minHeap;
    MaxHeap    maxHeap;
    AVLTree    avlTree;
    Graph      graph;
    Hashtable  hashtable;

    // Άνοιγμα αρχείων εντολών και εξόδου
    std::ifstream commands("commands.txt");
    std::ofstream output("output.txt");
    if (!commands.is_open() || !output.is_open()) {
        std::cerr << "Σφάλμα: δεν μπορώ να ανοίξω commands.txt ή output.txt\n";
        return 1;
    }

    std::string line;
    // Διαβάζουμε κάθε γραμμή (εντολή)
    while (std::getline(commands, line)) {
        if (line.empty()) continue;

        auto start = std::chrono::high_resolution_clock::now();     // Αρχή μέτρησης χρόνου

        std::istringstream parser(line);
        std::string cmd;
        parser >> cmd;
        std::string result;

        // Επεξεργασία εντολής
        if (cmd == "BUILD") {
            std::string s, fname;
            parser >> s >> fname;
            if (s == "MINHEAP") {
                std::ifstream f(fname);
                int v, count = 0;
                while (f >> v) count++;
                f.clear(); f.seekg(0);
                int* a = new int[count];
                for (int i = 0; i < count; ++i) f >> a[i];
                f.close();
                minHeap.buildFromArray(a, count);
                delete[] a;
                result = "SUCCESS";
            }
            else if (s == "MAXHEAP") {
                std::ifstream f(fname);
                int v, count = 0;
                while (f >> v) count++;
                f.clear(); f.seekg(0);
                int* a = new int[count];
                for (int i = 0; i < count; ++i) f >> a[i];
                f.close();
                maxHeap.buildFromArray(a, count);
                delete[] a;
                result = "SUCCESS";
            }
            else if (s == "AVLTREE") {
                std::ifstream f(fname);
                int v, count = 0;
                while (f >> v) count++;
                f.clear(); f.seekg(0);
                int* a = new int[count];
                for (int i = 0; i < count; ++i) f >> a[i];
                f.close();
                avlTree.buildFromArray(a, count);
                delete[] a;
                result = "SUCCESS";
            }
            else if (s == "GRAPH") {
                std::ifstream f(fname);
                int u, v, w, maxNode = -1;
                while (f >> u >> v >> w) {
                    if (u > maxNode) maxNode = u;
                    if (v > maxNode) maxNode = v;
                }
                f.clear(); f.seekg(0);
                graph.buildGraph(maxNode + 1);
                while (f >> u >> v >> w) graph.insertEdge(u, v, w);
                f.close();
                result = "SUCCESS";
            }
            else if (s == "HASHTABLE") {
                hashtable.buildFromArray(fname.c_str());
                result = "SUCCESS";
            }
            else {
                result = "FAILURE";
            }
        }
        else if (cmd == "GETSIZE") {
            std::string s; parser >> s;
            if (s == "MINHEAP")   result = std::to_string(minHeap.getSize());
            else if (s == "MAXHEAP")   result = std::to_string(maxHeap.getSize());
            else if (s == "AVLTREE")   result = std::to_string(avlTree.getSize());
            else if (s == "GRAPH") {
                int V, E; graph.getSize(V, E);
                result = std::to_string(V) + " " + std::to_string(E);
            }
            else if (s == "HASHTABLE") result = std::to_string(hashtable.getSize());
            else                        result = "FAILURE";
        }
        else if (cmd == "FINDMIN") {
            std::string s; parser >> s;
            if (s == "MINHEAP") result = std::to_string(minHeap.getMin());
            else if (s == "AVLTREE") result = std::to_string(avlTree.findMin());
            else                      result = "FAILURE";
        }
        else if (cmd == "FINDMAX") {
            std::string s; parser >> s;
            if (s == "MAXHEAP") result = std::to_string(maxHeap.getMax());
            else                      result = "FAILURE";
        }
        else if (cmd == "SEARCH") {
            std::string s; int k; parser >> s >> k;
            bool ok = (s == "AVLTREE" ? avlTree.search(k)
                : s == "HASHTABLE" ? hashtable.search(k)
                : false);
            result = ok ? "SUCCESS" : "FAILURE";
        }
        else if (cmd == "INSERT") {
            std::string s; parser >> s;
            if (s == "MINHEAP") { int x; parser >> x; minHeap.insert(x);    result = "SUCCESS"; }
            else if (s == "MAXHEAP") { int x; parser >> x; maxHeap.insert(x);    result = "SUCCESS"; }
            else if (s == "AVLTREE") { int x; parser >> x; avlTree.insert(x);    result = "SUCCESS"; }
            else if (s == "HASHTABLE") { int x; parser >> x; hashtable.insert(x);  result = "SUCCESS"; }
            else if (s == "GRAPH") { int a, b, c; parser >> a >> b >> c; graph.insertEdge(a, b, c); result = "SUCCESS"; }
            else                      result = "FAILURE";
        }
        else if (cmd == "DELETEMIN") {
            std::string s; parser >> s;
            result = (s == "MINHEAP" ? std::to_string(minHeap.deleteMin()) : "FAILURE");
        }
        else if (cmd == "DELETEMAX") {
            std::string s; parser >> s;
            result = (s == "MAXHEAP" ? std::to_string(maxHeap.deleteMax()) : "FAILURE");
        }
        else if (cmd == "DELETE") {
            std::string s; parser >> s;
            if (s == "AVLTREE") {
                int k; parser >> k;
                if (avlTree.search(k)) { avlTree.deleteKey(k); result = "SUCCESS"; }
                else                    result = "FAILURE";
            }
            else if (s == "GRAPH") {
                int a, b; parser >> a >> b;
                graph.deleteEdge(a, b);
                result = "SUCCESS";
            }
            else if (s == "HASHTABLE") {
                int k; parser >> k;
                hashtable.deleteKey(k);
                result = "SUCCESS";
            }
            else result = "FAILURE";
        }
        else if (cmd == "COMPUTESHORTESTPATH") {
            std::string s; int a, b; parser >> s >> a >> b;
            if (s == "GRAPH") {
                int d = graph.computeShortestPath(a, b);
                result = (d < 0 ? "FAILURE" : std::to_string(d));
            }
            else result = "FAILURE";
        }
        else if (cmd == "COMPUTESPANNINGTREE") {
            std::string s; parser >> s;
            if (s == "GRAPH") result = std::to_string(graph.computeSpanningTree());
            else            result = "FAILURE";
        }
        else if (cmd == "FINDCONNECTEDCOMPONENTS") {
            std::string s; parser >> s;
            if (s == "GRAPH") result = std::to_string(graph.findConnectedComponents());
            else            result = "FAILURE";
        }
        else {
            result = "FAILURE";
        }

        auto end = std::chrono::high_resolution_clock::now();    // Τέλος μέτρησης χρόνου
        auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        // Γράφουμε αποτέλεσμα + χρόνο σε μs
        output << result << " " << duration_us << "us\n";
    }

    commands.close();
    output.close();
    return 0;
}