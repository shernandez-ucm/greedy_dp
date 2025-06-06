#include <iostream>
#include <vector>
#include <algorithm>
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
    //visited[src] = true;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, src});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (visited[u]) continue; // No volver a visitar nodos ya marcados
        visited[u] = true;
        for (auto [v, wt] : adj[u]) {
            if (!visited[v] && dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// Algoritmo de Floyd-Warshall para encontrar todas las distancias más cortas entre pares de nodos
std::vector<std::vector<int>> floydWarshall(int V, const std::vector<std::vector<int>>& adjMatrix) {
    const int INF = std::numeric_limits<int>::max() / 2; // Para evitar overflow
    std::vector<std::vector<int>> dist = adjMatrix;

    // Inicializar: si no hay arista, poner INF (excepto en la diagonal)
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i != j && dist[i][j] == 0)
                dist[i][j] = INF;
        }
    }

    // Floyd-Warshall
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    return dist;
}

// Busca si el vértice v está en la lista de adyacencia de u
bool is_adjacent(int u, int v, const std::vector<std::vector<std::pair<int,int>>>& adj) {
    for (const auto& neighbor : adj[u]) {
        if (neighbor.first == v) return true;
    }
    return false;
}

// Genera un grafo aleatorio dirigido y ponderado
void generarGrafo(int V, int E, vector<vector<int>>& edges, vector<vector<pair<int,int>>>& adj) {
    std::random_device rd;
    unsigned int seed=1;
    std::srand(seed);
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> node_dist(0, V-1);
    std::uniform_int_distribution<> weight_dist(-5, 20); // pesos negativos y positivos

    edges.clear();
    adj.assign(V, {});
    for (int i = 1; i < V; ++i) {
        int w = weight_dist(gen);
        edges.push_back({i-1, i, w});
        adj[i-1].push_back({i, w});
    }

     for (int i = V-1; i < E; ++i) {
        int u = node_dist(gen);
        int v = node_dist(gen);
        int w = weight_dist(gen);
        while (v == u or is_adjacent(u,v,adj)) v = node_dist(gen); // evitar bucles
        edges.push_back({u, v, w});
        adj[u].push_back({v, w});
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
