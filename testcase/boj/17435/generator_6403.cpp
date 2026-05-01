#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small m for hand-checkable sizes
    int m = rnd.next(1, 15);

    // Hyper-parameter: choose function type
    int funcType = rnd.next(0, 2);
    vector<int> f(m + 1);
    if (funcType == 0) {
        // Identity mapping
        for (int i = 1; i <= m; i++)
            f[i] = i;
    } else if (funcType == 1) {
        // Fully random mapping
        for (int i = 1; i <= m; i++)
            f[i] = rnd.next(1, m);
    } else {
        // One cycle plus random attachments
        int k = rnd.next(1, m);
        vector<int> p(m);
        iota(p.begin(), p.end(), 1);
        shuffle(p.begin(), p.end());
        // Cycle on first k elements
        for (int i = 0; i < k; i++) {
            int u = p[i], v = p[(i + 1) % k];
            f[u] = v;
        }
        // Others point randomly to any in the cycle
        for (int i = k; i < m; i++) {
            int u = p[i];
            f[u] = p[rnd.next(0, k - 1)];
        }
    }

    // Number of queries
    int Q = rnd.next(1, min(20, m * 3));
    // Prepare queries
    vector<pair<int,int>> queries;
    for (int i = 0; i < Q; i++) {
        int x = rnd.next(1, m);
        int nType = rnd.next(0, 2);
        int n;
        if (nType == 0) {
            // small steps
            n = rnd.next(1, 5);
        } else if (nType == 1) {
            // medium steps
            int hi = max(5, m * 5);
            n = rnd.next(1, hi);
        } else {
            // large steps to force cycle wrap
            int lo = max(1, m * 10);
            int hi = 500000;
            if (lo > hi) lo = hi;
            n = rnd.next(lo, hi);
        }
        queries.emplace_back(n, x);
    }

    // Output
    println(m);
    // f(1) ... f(m)
    vector<int> f0(m);
    for (int i = 0; i < m; i++) f0[i] = f[i + 1];
    println(f0);
    println(Q);
    for (auto &qr : queries)
        println(qr.first, qr.second);

    return 0;
}
