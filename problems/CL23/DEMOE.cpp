#include<bits/stdc++.h>
using namespace std;

int n, t;

const int MAX = 10000;

int area[MAX + 100][MAX + 100];

int X_MIN, X_MAX, Y_MIN, Y_MAX;

int goX[4] = {1, 0, -1, 0};
int goY[4] = {0, 1, 0, -1};

int main() {
    cin >> n >> t;
    for(int x = 0; x <= MAX; x++)
        for(int y = 0; y <= MAX; y++) {
            area[x][y] = 0;
        }
    for(int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if(x1 > x2)
            swap(x1, x2);
        if(y1 > y2)
            swap(y1, y2);
        for(int x = x1; x < x2; x++) {
            // area[x][y1]++;
            // area[x][y2]--;
        }

        X_MIN = min(X_MIN, x1);
        X_MAX = max(X_MAX, x2);
        Y_MIN = min(Y_MIN, y1);
        Y_MAX = max(Y_MAX, y2);
    }

    for(int x = 0; x <= X_MAX; x++) {
        for(int y = 1; y <= Y_MAX; y++) {
            area[x][y] += area[x][y-1];
        }
    }

    long long ans_1 = 0;

    for(int x = 0; x <= X_MAX; x++) {
        for(int y = 0; y <= Y_MAX; y++) {
            if(area[x][y]) {
                area[x][y] = 1;
                ans_1++;
            }
        }
    }

    // for(int y = 0; y < Y_MAX; y++) {
    //     for(int x = 0; x < X_MAX; x++) {
    //         cout << area[x][y] << " ";
    //     }
    //     cout << endl;
    // }
    cout << ans_1 << endl;
    if(t == 2) {
        long long ans_2 = 0;

        for(int x = 0; x <= X_MAX; x++) {
            for(int y = 0; y <= Y_MAX; y++) {
                if(area[x][y]) {
                    // int sum = 0;
                    // cout << x << " " << y << endl;
                    for(int d = 0; d < 4; d++) {
                        int rX = x + goX[d];
                        int rY = y + goY[d];
                        int value;
                        if(rX < 0 || rX > MAX || rY < 0 || rY > MAX) {
                            value = 0;
                        } else {
                            value = area[rX][rY];
                        }
                        ans_2 += value == 0;
                    }
                    // cout << sum << endl;
                }
            }
        }

        cout << ans_2 << endl;
    }

    return 0;
}