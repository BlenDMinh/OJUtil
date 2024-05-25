#include<bits/stdc++.h>
using namespace std;

int n, m;
vector<int> adj[100005];
int t = 0;
int num[100005], low[100005];
stack<int> st;

void dfs(int u) {
    num[u] = low[u] = ++t;
    st.push(u);
    for(int v : adj[u]) {
        if(num[v] == 0) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else {
            low[u] = min(low[u], num[v]);
        }
    }

    if(num[u] == low[u]) {
        cout << "SCC: ";
        while(true) {
            int v = st.top();
            st.pop();
            cout << v << " ";
            if(v == u) break;
        }
        cout << endl;
    }
}

int main() {
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    dfs(1);

    return 0;
}