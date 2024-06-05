#include<bits/stdc++.h>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    for (size_t test = 0; test < t; test++) {
        long long a, b;
        scanf("%lld %lld", &a, &b);
        if(a == 0) {
            printf("NO SOL\n");
            continue;
        }

        map<long long, int> factors;
        for (size_t i = 2; i <= sqrt(a); i++) {
            while(a % i == 0) {
                factors[i]++;
                a /= i;
            }
        }

        if(a > 1) {
            factors[a]++;
        }

        long long res = 1;
        for(auto factor : factors) {
            long long p = factor.first;
            int cnt = factor.second;
            if (cnt % 2 != 0) {
                res *= p;
            }
        }


    }
}