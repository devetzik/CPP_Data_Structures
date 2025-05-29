#include "Graph.h"

const int INF = 99999999; // Απείρως μεγάλο βάρος για Dijkstra

Graph::Graph(){
    numVertices = 0;
    numEdges = 0;
    adj = nullptr;
}

void Graph::buildGraph(int n) {
    numVertices = n;    // Ορίζουμε νέα δομή με n κορυφές, χωρίς ακμές
    numEdges = 0;
    adj = new EdgeNode * [n];
    for (int i = 0; i < n; ++i) {
        adj[i] = nullptr;
    }
}

void Graph::insertEdge(int u, int v, int w) {
    if (u < 0 || v < 0 || u >= numVertices || v >= numVertices) return;
    adj[u] = new EdgeNode(v, w, adj[u]);    // προσθήκη u→v
    adj[v] = new EdgeNode(u, w, adj[v]);    // προσθήκη v→u
    ++numEdges;
}

void Graph::deleteEdge(int u, int v) {
    if (u < 0 || v < 0 || u >= numVertices || v >= numVertices) return;
    // διαγραφή από adj[u]
    EdgeNode** pp = &adj[u];
    while (*pp) {
        if ((*pp)->to == v) {
            EdgeNode* tmp = *pp;
            *pp = (*pp)->next;
            delete tmp;
            --numEdges;
            break;
        }
        pp = &((*pp)->next);
    }
    // διαγραφή από adj[v]
    pp = &adj[v];
    while (*pp) {
        if ((*pp)->to == u) {
            EdgeNode* tmp = *pp;
            *pp = (*pp)->next;
            delete tmp;
            break;
        }
        pp = &((*pp)->next);
    }
}


// Επιστρέφει το πλήθος κορυφών και ακμών
void Graph::getSize(int& vertices, int& edges) {
    vertices = numVertices;
    edges = numEdges;
}


// Υπολογίζει το βραχύτερο μονοπάτι από src σε dest με Dijkstra
int Graph::computeShortestPath(int src, int dest) {
    if (src < 0 || dest < 0 || src >= numVertices || dest >= numVertices) return -1;
    int* dist = new int[numVertices];
    bool* used = new bool[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        dist[i] = INF;
        used[i] = false;
    }
    dist[src] = 0;

    // Dijkstra
    for (int k = 0; k < numVertices; ++k) {
        int u = -1, best = INF;
        for (int i = 0; i < numVertices; ++i) {
            if (!used[i] && dist[i] < best) {
                best = dist[i];
                u = i;
            }
        }
        if (u < 0) break;
        used[u] = true;
        for (EdgeNode* p = adj[u]; p; p = p->next) {
            int v = p->to, w = p->weight;
            if (!used[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    int answer = (dist[dest] == INF ? -1 : dist[dest]);
    delete[] dist;
    delete[] used;
    return answer;
}



int Graph::computeSpanningTree() {
    if (numVertices == 0) return 0;
    bool* inMST = new bool[numVertices];
    int* key = new int[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        inMST[i] = false;
        key[i] = INF;
    }
    key[0] = 0;
    int total = 0;

    // Απλοποιημένο Prim O(V^2)
    for (int c = 0; c < numVertices; ++c) {
        int u = -1, best = INF;
        for (int i = 0; i < numVertices; ++i) {
            if (!inMST[i] && key[i] < best) {
                best = key[i];
                u = i;
            }
        }
        if (u < 0) break;
        inMST[u] = true;
        total += (best == INF ? 0 : best);
        for (EdgeNode* p = adj[u]; p; p = p->next) {
            int v = p->to, w = p->weight;
            if (!inMST[v] && w < key[v]) {
                key[v] = w;
            }
        }
    }

    delete[] inMST;
    delete[] key;
    return total;
}


// Εύρεση συνδεδεμένων συστατικών με BFS
int Graph::findConnectedComponents() {
    bool* vis = new bool[numVertices];
    int* queueArr = new int[numVertices];
    for (int i = 0; i < numVertices; ++i) vis[i] = false;
    int count = 0;
    for (int i = 0; i < numVertices; ++i) {
        if (!vis[i]) {
            count++;
            int head = 0, tail = 0;      // αρχικοποίηση head/tail
            queueArr[tail++] = i;
            vis[i] = true;       
                while (head < tail) {     // κλασική BFS
                int u = queueArr[head++];
                for (EdgeNode* p = adj[u]; p; p = p->next) {
                    int v = p->to;
                    if (!vis[v]) {
                        vis[v] = true;
                        queueArr[tail++] = v;
                    }
                }
            }
        }
    }
    delete[] queueArr;
    delete[] vis;
    return count;
}