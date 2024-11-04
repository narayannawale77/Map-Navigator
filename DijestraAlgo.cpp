#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

const int MAX = 100;
int adj[MAX][MAX];
int dist[MAX];
bool visited[MAX];
int parent[MAX];
int n; // Number of nodes

struct Node {
    int vertex;
    int weight;
    bool operator>(const Node& other) const {
        return weight > other.weight;
    }
};

// Function to implement Dijkstra's algorithm
void dijkstra(int src) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    for (int i = 0; i < n; i++) {
        dist[i] = numeric_limits<int>::max();
        visited[i] = false;
        parent[i] = -1;
    }
    dist[src] = 0;
    pq.push({src, 0});

    while (!pq.empty()) {
        int u = pq.top().vertex;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (adj[u][v] != 0 && !visited[v]) {
                if (dist[u] + adj[u][v] < dist[v]) {
                    dist[v] = dist[u] + adj[u][v];
                    parent[v] = u;
                    pq.push({v, dist[v]});
                }
            }
        }
    }
}

// Function to draw the path
void drawPath(int src, int dest) {
    if (parent[dest] == -1) {
        cout << "No path found!" << endl;
        return;
    }
    int current = dest;
    while (current != src) {
        line(current * 50, 400 - dist[current], parent[current] * 50, 400 - dist[parent[current]]);
        current = parent[current];
    }
}

int main() {
    // Initialize graphics
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Example graph (adjacency matrix)
    n = 5; // Number of nodes
    adj[0][1] = 10; adj[0][2] = 3;
    adj[1][2] = 1; adj[1][3] = 2;
    adj[2][1] = 4; adj[2][3] = 8; adj[2][4] = 2;
    adj[3][4] = 7;
    adj[4][3] = 9; adj[4][0] = 2;

    // Set source and destination
    int src = 0, dest = 3;

    // Run Dijkstra's algorithm
    dijkstra(src);

    // Draw nodes
    for (int i = 0; i < n; i++) {
        circle(i * 50 + 50, 400 - dist[i], 10);
        outtextxy(i * 50 + 50 - 5, 400 - dist[i] - 15, to_string(i).c_str());
    }

    // Draw the shortest path
    drawPath(src, dest);

    getch();
    closegraph();
    return 0;
}
