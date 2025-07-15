#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <algorithm>

using namespace std;

class Graph {
    unordered_map<string, vector<pair<string, int>>> adj;

public:
    // Add a connection (pipe)
    void addEdge(string u, string v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // undirected graph
    }

    // Remove a connection (pipe)
    void removeEdge(string u, string v) {
        auto &vecU = adj[u];
        vecU.erase(remove_if(vecU.begin(), vecU.end(), [&](auto &p) { return p.first == v; }), vecU.end());

        auto &vecV = adj[v];
        vecV.erase(remove_if(vecV.begin(), vecV.end(), [&](auto &p) { return p.first == u; }), vecV.end());
    }

    // BFS traversal
    void BFS(string start) {
        unordered_map<string, bool> visited;
        queue<string> q;
        q.push(start);
        visited[start] = true;

        cout << "BFS: ";
        while (!q.empty()) {
            string node = q.front(); q.pop();
            cout << node << " ";

            for (auto &neigh : adj[node]) {
                if (!visited[neigh.first]) {
                    visited[neigh.first] = true;
                    q.push(neigh.first);
                }
            }
        }
        cout << endl;
    }

    // DFS traversal
    void DFSUtil(string node, unordered_map<string, bool> &visited) {
        visited[node] = true;
        cout << node << " ";

        for (auto &neigh : adj[node]) {
            if (!visited[neigh.first])
                DFSUtil(neigh.first, visited);
        }
    }

    void DFS(string start) {
        unordered_map<string, bool> visited;
        cout << "DFS: ";
        DFSUtil(start, visited);
        cout << endl;
    }

    // Dijkstra’s Algorithm: Shortest path from source
    void dijkstra(string src) {
        unordered_map<string, int> dist;
        for (auto &pair : adj)
            dist[pair.first] = INT_MAX;

        dist[src] = 0;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();

            for (auto &[v, weight] : adj[u]) {
                if (dist[v] > d + weight) {
                    dist[v] = d + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "Shortest distances from " << src << ":\n";
        for (auto &[node, d] : dist)
            cout << node << ": " << (d == INT_MAX ? -1 : d) << "\n";
    }
};

int main() {
    Graph g;

    g.addEdge("Source", "Tank1", 4);
    g.addEdge("Tank1", "Junction1", 2);
    g.addEdge("Junction1", "House1", 5);
    g.addEdge("Junction1", "House2", 6);
    g.addEdge("Tank1", "House3", 10);

    g.BFS("Source");
    g.DFS("Source");
    g.dijkstra("Source");

    return 0;
}