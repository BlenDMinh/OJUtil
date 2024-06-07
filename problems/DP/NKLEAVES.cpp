#include<bits/stdc++.h>
using namespace std;

int N, K;
int w[100005];
long long dp[100005][11];
long long t[100005], c[100005];

struct Line {
    long long a, b;
    Line(long long a = 0, long long b = 0) : a(a), b(b) {
    }
    long long get(long long x) const {
        return a * x + b;
    }
    /**
     * y = a1x + b1
     * y = a2x + b2
     * a1x + b1 = a2x + b2
     * x = (b2 - b1) / (a1 - a2)
    */
    double intersect(const Line &l) const {
        return (double) (l.b - this->b) / (double) (this->a - l.a);
    }
};

struct HullTrickOperation {
    int pos, size;
    Line line;

    HullTrickOperation(int pos, int size, Line line) : pos(pos), size(size), line(line) {}
};

class HullTrick {
    private:
        bool min_hull;
        bool reverse;
        int size;
        Line *lines;
        stack<HullTrickOperation> operations;

        static bool compare(const Line &l1, const Line &l2, const Line &l3) {
            return l1.intersect(l3) >= l1.intersect(l2);
        }

        static bool compare_reverse(const Line &l1, const Line &l2, const Line &l3) {
            return l1.intersect(l3) <= l1.intersect(l2);
        }

        static bool cmp(double x, double y) {
            return x > y;
        }

        static bool cmp_reverse(double x, double y) {
            return x < y;
        }
    public:
        HullTrick(int N = 100000, bool min_hull = true, bool reverse = false) {
            this->min_hull = min_hull;
            this->reverse = reverse;
            this->lines = new Line[N];
            this->size = 0;
        }

        bool add(const Line &line, bool (*compare)(const Line &, const Line &, const Line &) = nullptr) {
            if(size < 2) {
                operations.push(HullTrickOperation(size, size, lines[size]));
                this->lines[size++] = line;
                return true;
            }

            if(compare == nullptr) {
                if(this->min_hull) {
                    compare = this->reverse ? compare_reverse : HullTrick::compare;
                } else {
                    compare = this->reverse ? HullTrick::compare : HullTrick::compare_reverse;
                }
            }

            int l = 1, r = size - 1;
            int new_pos = size;
            while(l <= r) {
                int m = (l + r) >> 1;
                if(compare(lines[m - 1], lines[m], line)) {
                    new_pos = m;
                    r = m - 1;
                } else {
                    l = m + 1;
                }
            }

            operations.push(HullTrickOperation(new_pos, size, lines[new_pos]));
            size = new_pos + 1;
            lines[new_pos] = line;
            return true;
        }

        void rollback() {
            if(operations.empty()) {
                return;
            }

            HullTrickOperation operation = operations.top();
            operations.pop();
            size = operation.size;
            lines[operation.pos] = operation.line;
        }

        long long query(long long target, bool (*cmp)(double, double) = nullptr) {
            if(cmp == nullptr) {
                if(this->min_hull) {
                    cmp = this->reverse ? HullTrick::cmp : HullTrick::cmp_reverse;
                } else {
                    cmp = this->reverse ? HullTrick::cmp_reverse : HullTrick::cmp;
                }
            }

            int l = 0, r = size - 1;
            long long ans = lines[l].get(target);

            while(l < r) {
                int m = (l + r) >> 1;
                long long x = lines[m].get(target);
                long long y = lines[m + 1].get(target);
                // cout << l << " " << r << " " << m << " " << x << " " << y << endl;
                if(cmp(x, y)) {
                    l = m + 1;
                } else {
                    r = m;
                }

                if(this->min_hull) {
                    ans = min(ans, min(x, y));
                } else {
                    ans = max(ans, max(x, y));
                }
            }

            return ans;
        }

        int getSize() {
            return size;
        }

        const Line &get(int i) {
            return lines[i];
        }

        void debug() {
            for(int i = 0; i < size; i++) {
                cout << "Line: " << lines[i].a << " " << lines[i].b << endl;
            }

            cout << endl;

            // while(!operations.empty()) {
            //     HullTrickOperation operation = operations.top();
            //     operations.pop();
            //     cout << "Operation: " << operation.pos << " " << operation.size << " " << operation.line.a << " " << operation.line.b << endl;
            // }
        }
};

long long cost(int l, int r) {
    return c[r] - c[l] - ((t[r] - t[l]) * l);
}

int main() {
    scanf("%d %d", &N, &K);
    for(int i = 0; i < N; i++) {
        scanf("%d", &w[i]);
        t[i + 1] = t[i] + w[i];
        c[i + 1] = c[i] + w[i] * (i + 1);
    }


    for(int i = 1; i <= N; i++) {
        dp[i][1] = cost(1, i);
    }

    for(int k = 2; k <= K; k++) {
        HullTrick hull(100005, true, true);
        hull.add(Line(-k, dp[k - 1][k - 1] - c[k] + t[k] * k));
        for(int i = k; i <= N; i++) {
            dp[i][k] = hull.query(t[i]) + c[i];
            hull.add(Line(-(i + 1), dp[i][k - 1] - c[i + 1] + t[i + 1] * (i + 1)));

            // for(int j = 0; j < i; j++) {
            //     dp[i][k] = min(dp[i][k], dp[j][k - 1] + cost(j + 1, i));
                // DP[j] + c[i] - c[j + 1] - (t[i] - t[j + 1]) * (j + 1)
                // = DP[j] + t[j + 1] * (j + 1) - c[j + 1] - t[i] * (j + 1) + c[i]
                // = 

            // }
        }
    }

    cout << dp[N][K] << endl;
}