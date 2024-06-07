#include<bits/stdc++.h>
using namespace std;

int n;
int res = 0;

bool isVisited[110];
vector<int> g[110];

int dfs(int u) {
    isVisited[u] = true;
    int res = 0;
    for(int v : g[u]) {
        if(isVisited[v])
            continue;
        res += dfs(v);
    }
    return res + 1;
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i = 1; i <= 100; i++) {
        if(isVisited[i])
            continue;
        int cnt = dfs(i);
        res = max(res, cnt);
    }
    cout << res;
}