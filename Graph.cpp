#include "Graph.h"
#include <limits>

static const int INF = std::numeric_limits<int>::max();

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

void Graph::getSize(int& vertices, int& edges) {
    vertices = numVertices;
    edges = numEdges;
}

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

int Graph::findConnectedComponents() {
    bool* vis = new bool[numVertices];
    for (int i = 0; i < numVertices; ++i) vis[i] = false;
    int count = 0;
    std::queue<int> q;

    for (int i = 0; i < numVertices; ++i) {
        if (!vis[i]) {
            ++count;
            vis[i] = true;
            q.push(i);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (EdgeNode* p = adj[u]; p; p = p->next) {
                    if (!vis[p->to]) {
                        vis[p->to] = true;
                        q.push(p->to);
                    }
                }
            }
        }
    }
    delete[] vis;
    return count;
}