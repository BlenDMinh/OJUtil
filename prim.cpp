#include<bits/stdc++.h>
using namespace std;

struct Edge {
    int from, to;
    long long w;

    Edge(int from, int to, long long w) : from(from), to(to), w(w) {}
};

bool operator<(const Edge &a, const Edge &b) {
    return a.w < b.w;
}

int n, m;
vector<Edge> adj[100005];

priority_queue<Edge> q;

vector<Edge> prim() {
    vector<Edge> mst;
    vector<bool> vis(n + 1, false);
    q.push(Edge(0, 1, 0));
    while(!q.empty()) {
        Edge e = q.top();
        q.pop();
        if(vis[e.to]) continue;
        vis[e.to] = true;
        mst.push_back(e);
        for(Edge f : adj[e.to]) {
            if(!vis[f.to]) {
                q.push(f);
            } 
        }
    }
    return mst;

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

    vector<Edge> mst = prim();
    for(Edge e : mst) {
        cout << e.from << " " << e.to << " " << e.w << endl;
    }

    return 0;
}