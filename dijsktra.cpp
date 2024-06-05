#include<bits/stdc++.h>
using namespace std;

struct Edge {
    int from, to;
    long long w;

    Edge(int from, int to, long long w) : from(from), to(to), w(w) {}
};

int n, m;
vector<Edge> adj[100005];
long long dist[100005];

long long dijsktra(int from, int to) {
    priority_queue<pair<long long, int>> q;
    dist[from] = 0;
    q.push({0, from});
    while(!q.empty()) {
        pair<long long, int> p = q.top();
        q.pop();
        int u = p.second;
        if(u == to) 
            return dist[u];
        for(Edge e : adj[u]) {
            if(dist[e.to] > dist[u] + e.w) {
                dist[e.to] = dist[u] + e.w;
                q.push({-dist[e.to], e.to});
            }
        }
    }
    return -1;
}

int main() {
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back(Edge(u, v, w));
        adj[v].push_back(Edge(v, u, w));
    }

    for(int i = 1; i <= n; i++) {
        dist[i] = LLONG_MAX;
    }

    cout << dijsktra(1, n) << endl;
}