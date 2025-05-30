#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <fstream>
using namespace std;

vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
    vector<int> dist(V, std::numeric_limits<int>::max() );
    dist[src] = 0;
    for (int i = 0; i < V; i++) {
        for (vector<int> edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            if (dist[u] != std::numeric_limits<int>::max()  && dist[u] + wt < dist[v]) {
                if(i == V - 1)
                    return {-1};
                dist[v] = dist[u] + wt;
            }
        }
    }
    return dist;
}

// Dijkstra usando lista de adyacencia
vector<int> dijkstra(int V, vector<vector<pair<int,int>>>& adj, int src) {
    vector<int> dist(V, std::numeric_limits<int>::max() );
    vector<bool> visited(V, false );
    dist[src] = 0;
    visited[src] = true;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, src});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u] or not visited[u]) continue;
        for (auto [v, wt] : adj[u]) {
            if (dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
                pq.push({dist[v], v});
                visited[v] = true; // Marcar como visitado
            }
        }
    }
    return dist;
}

// Genera un grafo aleatorio dirigido y ponderado
void generarGrafo(int V, int E, vector<vector<int>>& edges, vector<vector<pair<int,int>>>& adj) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> node_dist(0, V-1);
    std::uniform_int_distribution<> weight_dist(1, 20); // pesos negativos y positivos

    edges.clear();
    adj.assign(V, {});

    for (int i = 0; i < E; ++i) {
        int u = node_dist(gen);
        int v = node_dist(gen);
        while (v == u) v = node_dist(gen); // evitar bucles
        int w = weight_dist(gen);
        bool exists = false;
        for (auto [vi, wi] : adj[u]) {
            if (vi == v) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            edges.push_back({u, v, w});
            //edges.push_back({v, u, w}); // si quieres grafo no dirigido
            //edges.push_back({u, v, w});
            edges.push_back({v, u, w});
            adj[v].push_back({u, w});
            adj[u].push_back({v, w});
        }
        
    }
}

void mostrarGrafoGraphviz(int V, const vector<vector<pair<int,int>>>& adj, const std::string& filename = "graph.dot") {
    std::ofstream fout(filename);
    fout << "digraph G {\n";
    for (int u = 0; u < V; ++u) {
        for (auto [v, w] : adj[u]) {
            fout << "    " << u << " -> " << v << " [label=\"" << w << "\"];\n";
        }
    }
    fout << "}\n";
    fout.close();
    std::cout << "Archivo Graphviz generado: " << filename << std::endl;
}
