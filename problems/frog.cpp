#include <stdio.h>
#include <vector>

using namespace std;

typedef long long ll;

vector<vector<ll>> A, B, C, base, matrix[200005];
vector<ll> frog[200005];
int n, m, q;

vector<vector<ll>> mul(vector<vector<ll>> A, vector<vector<ll>> B) {
    vector<vector<ll>> C(A.size(), vector<ll>(B[0].size()));
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B[0].size(); j++) {
            for (int k = 0; k < B.size(); k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

vector<vector<ll>> cw() {
    return {{0, -1, 0}, {1, 0, 0}, {0, 0, 1}};
}

vector<vector<ll>> ccw() {
    return {{0, 1, 0}, {-1, 0, 0}, {0, 0, 1}};
}

vector<vector<ll>> xflip(ll k) {
    return {{-1, 0, 0}, {0, 1, 0}, {2 * k, 0, 1}};
}

vector<vector<ll>> yflip(ll k) {
    return {{1, 0, 0}, {0, -1, 0}, {0, 2 * k, 1}};
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 0; i < n; i++) {
        ll x, y;
        scanf("%lld %lld", &x, &y);
        frog[i] = {x, y};
    }
    base = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    for (int i = 0; i < m; i++) {
        char command[10];
        ll k;
        scanf("%s", command);
        if (command[0] == 'c' && command[1] == 'w')
            base = mul(base, cw());
        else if (command[0] == 'c' && command[1] == 'c')
            base = mul(base, ccw());
        else if (command[0] == 'x') {
            scanf("%lld", &k);
            base = mul(base, xflip(k));
        } else {
            scanf("%lld", &k);
            base = mul(base, yflip(k));
        }
        matrix[i] = base;
    }
    for (int i = 0; i < q; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        vector<vector<ll>> res = mul({{frog[x - 1][0], frog[x - 1][1], 1}}, matrix[y - 1]);
        printf("%lld %lld\n", res[0][0], res[0][1]);
    }
    return 0;
}