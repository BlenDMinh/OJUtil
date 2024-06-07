#include<bits/stdc++.h>
using namespace std;

const int MAX = 100000;

int p[MAX + 5];

void calc() {
    p[0] = 0;
    p[1] = 1;
    for (int i = 2; i <= MAX; i++)
        p[i] = i - 1;
    for (int i = 2; i <= MAX; i++)
        for (int j = 2 * i; j <= MAX; j += i)
              p[j] -= p[i];
}

int main() {
    calc();
}