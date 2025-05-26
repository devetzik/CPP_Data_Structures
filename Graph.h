#ifndef GRAPH_H
#define GRAPH_H

#include <queue>  // μόνο για BFS

// Κόμβος λίστας γειτνίασης
struct EdgeNode {
    int to;             // η κορυφή στην άκρη
    int weight;         // το βάρος της ακμής
    EdgeNode* next;     // επόμενος κόμβος στη λίστα
    EdgeNode(int t, int w, EdgeNode* n)
        : to(t), weight(w), next(n) {
    }
};

class Graph {
private:
    int numVertices;    // πλήθος κορυφών
    int numEdges;       // πλήθος ακμών
    EdgeNode** adj;     // δυναμικός πίνακας head pointers

    // Απελευθερώνει πλήρως τη δομή (λίστες + πίνακα)
    void clearGraph();

public:
    Graph();
    ~Graph();

    void buildGraph(int n);                  // αρχικοποίηση με n κορυφές
    void insertEdge(int u, int v, int w);    // εισαγωγή ακμής (u–v, βάρος w)
    void deleteEdge(int u, int v);           // διαγραφή ακμής u–v
    void getSize(int& vertices, int& edges); // επιστρέφει (vertices, edges)

    int computeShortestPath(int src, int dest); // Dijkstra
    int computeSpanningTree();                  // Prim
    int findConnectedComponents();              // BFS
};

#endif
