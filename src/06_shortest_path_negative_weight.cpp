#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <fstream>
using namespace std;

#include "graph.hpp"

int main() {
    int V=4, E=4,src=0;
    vector<vector<int>> edges;
    vector<vector<pair<int,int>>> adj;
        edges = {
        {0, 1, 5},
        {0, 2, 6},
        {2, 3, -3},
        {3, 1, -3},
    };
    adj.assign(V, {});
    adj[0].push_back({1, 5});
    adj[0].push_back({2, 6});
    adj[2].push_back({3, -3});
    adj[3].push_back({1, -3});
    mostrarGrafoGraphviz(V, adj);
    cout << "\nBellman-Ford:\n";
    vector<int> dist_bf = bellmanFord(V, edges, src);
    if (dist_bf.size() == 1 && dist_bf[0] == -1) {
        cout << "Ciclo negativo detectado.\n";
    } else {
        for (int d : dist_bf) cout << d << " ";
        cout << endl;
    }

    cout << "\nDijkstra:\n";
    vector<int> dist_dj = dijkstra(V, adj, src);
    for (int d : dist_dj) cout << d << " ";
    cout << endl;

    return 0;
}