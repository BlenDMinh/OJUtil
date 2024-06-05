#include<bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    long long weight;
    Edge(int to = -1, long long weight = -1) : to(to), weight(weight) {}
};

int n, m;
int new_n_index;
vector<Edge> g[400005];
Edge redirect[200005];
int num[200005], low[200005], cnt = 0;
bool deleted[200005];
bool being_accounted[200005];
stack<int> s;

int res = 0;

int fastscan() {
    int number = 0;
    char c = getchar();
    while(c<'0' || c>'9') c = getchar();
    while(c>='0' && c<='9') {
        number = number * 10 + c - 48;
        c = getchar();
    }
    return number;
}

long long exhaust(long long w) {
    long long res = 0;
    while(w) {
        res += w;
        w /= 2;
    }
    return res;
}

void dfs(int u) {
    num[u] = low[u] = ++cnt;
    s.push(u);
    for(Edge v : g[u]) {
        if(num[v.to] == -1) {
            dfs(v.to);
        }
        if(!deleted[v.to]) {
            low[u] = min(low[u], low[v.to]);
        }
    }

    if(num[u] == low[u]) {
        int node_index = new_n_index++;
        vector<int> subgraph;
        res++;
        while(true) {
            int v = s.top();
            s.pop();
            deleted[v] = true;
            being_accounted[v] = true;
            subgraph.push_back(v);
            if(v == u) break;
        }

        long long w = 0;

        for(int v : subgraph) {
            for(Edge e : g[v]) {
                if(being_accounted[e.to]) {
                    // printf("exhaust %d %d %lld\n", v, e.to, exhaust(e.weight));
                    w += exhaust(e.weight);
                } else {
                    g[node_index].push_back(Edge(e.to, e.weight));
                }
            }
        }

        for(int v : subgraph) {
            redirect[v] = Edge(node_index, w);
            being_accounted[v] = false;
        }
    }
}

long long f[400005];

long long best(int u) {
    if(f[u] != -1) 
        return f[u];
    long long res = 0;
    long long init_w = 0;

    if(redirect[u].to != -1) {
        init_w = redirect[u].weight;
        u = redirect[u].to;
    }

    // printf("u: %d init_w: %lld\n", u, init_w);
    
    for(Edge v : g[u]) {
        if(redirect[v.to].to != -1) {
            v = Edge(redirect[v.to].to, v.weight + redirect[v.to].weight);
        }

        res = max(res, best(v.to) + v.weight);
    }

    return f[u] = init_w + res;
}

int main() {
    n = fastscan();
    m = fastscan();
    new_n_index = n + 1;
    for(int i = 0; i < m; i++) {
        int u, v, w;
        u = fastscan();
        v = fastscan();
        w = fastscan();
        g[u].push_back(Edge(v, w));
    }

    for(int i = 1; i <= n; i++)
        num[i] = low[i] = -1;

    for(int i = 1; i <= n; i++)
        redirect[i] = Edge(-1, -1);

    for(int i = 1; i <= n; i++) {
        if(num[i] == -1) {
            dfs(i);
        }
    }

    for(int i = 1; i <= new_n_index; i++) {
        f[i] = -1;
    }

    // for(int i = 1; i <= new_n_index; i++) {
    //     if(redirect[i].to != -1) {
    //         printf("%d Redirect u w: %d %lld\n", i, redirect[i].to, redirect[i].weight);
    //         continue;
    //     }

    //     printf("u: %d:\n", i);
    //     for(Edge e : g[i]) {
    //         printf("\tv w: %d %lld\n", e.to, e.weight);
    //     }
    // }

    long long res = best(1);
    printf("%lld\n", res);

    return 0;
}