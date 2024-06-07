#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> arr;
    for(int i = 0; i < n; i++) {
        int a;
        cin >> a;
        arr.push_back(a);
    }
    sort(arr.begin(), arr.end());
    for(int i = 0; i < n; i++) {
        arr[i] -= (i + 1);
    }
    int res = arr[0];
    for(int i = 1; i < n; i++) {
        res ^= arr[i] - arr[i - 1];
    }
    if(res) {
        cout << "TUAN";
    } else {
        cout << "CPU";
    }
}