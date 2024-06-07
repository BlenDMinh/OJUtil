#include<bits/stdc++.h>
using namespace std;

vector<int> a;

void recur(int n, int last) {
    if(n == 0) {
        for(int num : a) 
            cout << num << " ";
        cout << endl;
    }

    for(int i = min(n, last); i >= 1; i--) {
        a.push_back(i);
        recur(n - i, i);
        a.pop_back();
    }
}

int main() {
    int n;
    cin >> n;
    recur(n, 31);
}