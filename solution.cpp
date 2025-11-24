#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Graph {
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int v) {
        V = v;
        adj.resize(V);
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "\nPerforming BFS starting from node " << start << ":\n";
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << "Visited node " << node << "\n";

            for (auto neigh : adj[node]) {
                if (!visited[neigh.first]) {
                    visited[neigh.first] = true;
                    q.push(neigh.first);
                }
            }
        }
    }

    void DFSUtil(int node, vector<bool> &visited) {
        visited[node] = true;
        cout << "Visited node " << node << "\n";

        for (auto neigh : adj[node]) {
            if (!visited[neigh.first]) {
                DFSUtil(neigh.first, visited);
            }
        }
    }

    void DFS(int start) {
        vector<bool> visited(V, false);
        cout << "\nPerforming DFS starting from node " << start << ":\n";
        DFSUtil(start, visited);
    }

    void dijkstra(int src) {
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            for (auto neigh : adj[u]) {
                int v = neigh.first;
                int w = neigh.second;

                if (dist[v] > d + w) {
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "\nShortest distances from node " << src << ":\n";
        for (int i = 0; i < V; i++) {
            if (dist[i] == INT_MAX)
                cout << "Node " << i << " is unreachable\n";
            else
                cout << "Node " << i << " : " << dist[i] << "\n";
        }
    }
};

int main() {
    cout << "Creating a simple water supply system graph...\n";

    Graph g(6);

    cout << "Adding connections between nodes with their distances...\n";
    g.addEdge(0, 1, 4);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 5);
    g.addEdge(2, 4, 6);
    g.addEdge(1, 5, 10);

    g.BFS(0);
    g.DFS(0);
    g.dijkstra(0);

    return 0;
}
