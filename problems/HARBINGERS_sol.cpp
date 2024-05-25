#include <bits/stdc++.h>
#define X first
#define Y second

const int N = 100005;
const long long INF = (long long)1e18;

using namespace std;

typedef pair<int, int> Line;

struct operation {
    int pos, top;
    Line overwrite;
    operation(int _p, int _t, Line _o) {
        pos = _p; top = _t; overwrite = _o;
    }
};
vector<operation> undoLst;
Line lines[N];
int n, top;

long long eval(Line line, long long x) {return line.X * x + line.Y;}
bool bad(Line a, Line b, Line c)
    {return (double)(b.Y - a.Y) / (a.X - b.X) >= (double)(c.Y - a.Y) / (a.X - c.X);}

long long getMin(long long coord) {
    int l = 0, r = top - 1; long long ans = eval(lines[l], coord);
    while (l < r) {
        int mid = l + r >> 1;
        long long x = eval(lines[mid], coord);
        long long y = eval(lines[mid + 1], coord);
        if (x > y) l = mid + 1; else r = mid;
        ans = min(ans, min(x, y));
    }
    return ans;
}

bool insertLine(Line newLine) {
    int l = 1, r = top - 1, k = top;
    while (l <= r) {
        int mid = l + r >> 1;
        if (bad(lines[mid - 1], lines[mid], newLine)) {
            k = mid; r = mid - 1;
        }
        else l = mid + 1;
    }
    undoLst.push_back(operation(k, top, lines[k]));
    top = k + 1;
    lines[k] = newLine;
    return 1;
}

void undo() {
    operation ope = undoLst.back(); undoLst.pop_back();
    top = ope.top; lines[ope.pos] = ope.overwrite;
}

long long f[N], S[N], V[N], d[N];
vector<Line> a[N];

void dfs(int u, int par) {
    if (u > 1)
        f[u] = getMin(V[u]) + S[u] + V[u] * d[u];
    insertLine(make_pair(-d[u], f[u]));
    cout << "u: " << u << ' ' << f[u] << '\n';
    for(int i = 0; i < top; ++i) cout << lines[i].X << ' ' << lines[i].Y << '\n';
    for (vector<Line>::iterator it = a[u].begin(); it != a[u].end(); ++it) {
        int v = it->X;
        int uv = it->Y;
        if (v == par) continue;
        d[v] = d[u] + uv;
        dfs(v, u);
    }
    undo();
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    int u, v, c;
    for (int i = 1; i < n; ++i) {
        cin >> u >> v >> c;
        a[u].push_back(make_pair(v, c));
        a[v].push_back(make_pair(u, c));
    }
    for (int i = 2; i <= n; ++i) cin >> S[i] >> V[i];
    dfs(1, 0);
    for (int i = 2; i <= n; ++i) cout << f[i] << ' ';
    return 0;
}