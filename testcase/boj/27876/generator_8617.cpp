#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(int n = 0) { init(n); }
    void init(int n) {
        p.resize(n);
        r.assign(n, 0);
        for (int i = 0; i < n; ++i) p[i] = i;
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) ++r[a];
    }
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_SMALL = 200;
    const int MAX_N = 10000000;

    // Precompute perfect squares up to 2 * MAX_SMALL
    vector<bool> isSquare(2 * MAX_SMALL + 1, false);
    for (int k = 1; k * k <= 2 * MAX_SMALL; ++k) {
        isSquare[k * k] = true;
    }

    // Incrementally build the perfect-square-sum graph for prefixes 1..n
    DSU dsu(MAX_SMALL + 1); // 1-based indices
    vector<bool> prefixConnected(MAX_SMALL + 1, false);

    for (int n = 1; n <= MAX_SMALL; ++n) {
        for (int j = 1; j < n; ++j) {
            if (isSquare[n + j]) dsu.unite(n, j);
        }
        int root1 = dsu.find(1);
        bool ok = true;
        for (int i = 2; i <= n; ++i) {
            if (dsu.find(i) != root1) {
                ok = false;
                break;
            }
        }
        prefixConnected[n] = ok;
    }

    vector<int> okNs, badNs;
    for (int n = 1; n <= MAX_SMALL; ++n) {
        if (prefixConnected[n]) okNs.push_back(n);
        else badNs.push_back(n);
    }

    int type = rnd.next(0, 7);
    int N = 1;

    switch (type) {
        case 0:
            // Trivial smallest case
            N = 1;
            break;
        case 1:
            // Guaranteed impossible (disconnected) small N
            if (!badNs.empty())
                N = rnd.any(badNs);
            else
                N = rnd.next(1, MAX_SMALL);
            break;
        case 2:
            // Guaranteed possible (connected) small N
            if (!okNs.empty())
                N = rnd.any(okNs);
            else
                N = rnd.next(1, MAX_SMALL);
            break;
        case 3:
            // Smallest impossible N (edge where merging first fails)
            if (!badNs.empty())
                N = badNs.front();
            else
                N = rnd.next(1, MAX_SMALL);
            break;
        case 4:
            // Largest impossible N within small range
            if (!badNs.empty())
                N = badNs.back();
            else
                N = rnd.next(1, MAX_SMALL);
            break;
        case 5:
            // Random small N
            N = rnd.next(1, MAX_SMALL);
            break;
        case 6:
            // Completely random N over full constraints
            N = rnd.next(1, MAX_N);
            break;
        case 7: {
            // Structured large-ish N
            int st = rnd.next(0, 3);
            int maxK = (int)floor(sqrt((double)MAX_N));
            if (st == 0) {
                // Perfect square
                int k = rnd.next(1, maxK);
                N = k * k;
            } else if (st == 1) {
                // One less than a perfect square
                int k = rnd.next(2, maxK); // ensure k*k-1 >= 3
                N = k * k - 1;
            } else if (st == 2) {
                // One more than a perfect square
                int k = rnd.next(1, maxK);
                long long val = 1LL * k * k + 1;
                if (val > MAX_N) val = MAX_N;
                N = (int)val;
            } else {
                // Near the upper limit
                int low = max(1, MAX_N - 1000);
                N = rnd.next(low, MAX_N);
            }
            break;
        }
        default:
            N = rnd.next(1, MAX_N);
    }

    println(N);
    return 0;
}
