#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <fstream>
using namespace std;

#include "graph.hpp"

int main() {
    int V=5, E=10,src=0;
    vector<vector<pair<int,int>>> adj;
    adj.assign(V, {});
    adj[0].push_back({1, 11});
    adj[0].push_back({2, -2});
    adj[1].push_back({2, 2});
    adj[1].push_back({4, 13});
    adj[2].push_back({3, 20});
    adj[2].push_back({4, 14});
    adj[3].push_back({0, 13});
    adj[3].push_back({4, -4});
    adj[4].push_back({1, 6});
    adj[4].push_back({2, -3});
    mostrarGrafoGraphviz(V, adj);
    vector<vector<int>> adj_matrix= adjListToMatrix(V, adj);
    cout << "Matriz de Adyacencia:\n";
    for (const auto& row : adj_matrix) {
        for (int d : row) {
            if (d == std::numeric_limits<int>::max() / 2)
                cout << "0 ";
            else
                cout << d << " ";
        }
        cout << endl;
    }
    std::vector<std::vector<int>> dist = floydWarshall(V, adj_matrix);
    cout << "Matriz de distancias:\n";
    for (const auto& row : dist) {
        for (int d : row) {
            if (d == std::numeric_limits<int>::max() / 2)
                cout << "INF ";
            else
                cout << d << " ";
        }
        cout << endl;
    }
    cout << "\nDistancias desde el nodo " << src << ":\n";
    for (int i = 0; i < V; ++i) {
        if (dist[src][i] == std::numeric_limits<int>::max() / 2)
            cout << "INF ";
        else
            cout << dist[src][i] << " ";
    }
    cout << endl;
    

    return 0;
}