#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

static const int MAX_X = 1000000;
static const int MAX_N = 200000;
static const int MAX_Q = 200000;
// We allow positions up to MAX_X + MAX_Q + some slack
static const int M = MAX_X + MAX_Q + 5;

int findp(int x, vector<int> &p) {
    if (p[x] == x) return x;
    return p[x] = findp(p[x], p);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // Read n
    int n = inf.readInt(1, MAX_N, "n");
    inf.readEoln();
    // Read initial positions
    vector<long long> x(n+1);
    {
        vector<long long> xs = inf.readLongs(n, 1LL, (long long)MAX_X, "x_i");
        for (int i = 0; i < n; i++) {
            x[i+1] = xs[i];
        }
    }
    inf.readEoln();
    // Check strictly increasing
    for (int i = 1; i < n; i++) {
        ensuref(x[i] < x[i+1],
                "Positions must be strictly increasing: x[%d]=%lld >= x[%d]=%lld",
                i, x[i], i+1, x[i+1]);
    }
    // Read q
    int q = inf.readInt(1, MAX_Q, "q");
    inf.readEoln();
    // Prepare DSU for free positions [1..M+1]
    vector<int> parent(M+2);
    for (int i = 0; i <= M+1; i++) parent[i] = i;
    // Mark initial occupied pads: union(x_i, x_i+1)
    for (int i = 1; i <= n; i++) {
        int xi = (int)x[i];
        // occupy xi
        int a = findp(xi, parent);
        int b = findp(xi+1, parent);
        if (a != b) parent[a] = b;
    }
    // Current positions
    vector<int> cur(n+1);
    for (int i = 1; i <= n; i++) {
        cur[i] = (int)x[i];
    }
    // Process jumps
    for (int j = 0; j < q; j++) {
        int idx = inf.readInt(1, n, "i");
        inf.readEoln();
        // frog idx jumps: find nearest free > cur[idx]
        int start = cur[idx] + 1;
        // start might exceed M+1
        ensuref(start <= M+1,
                "No lily pad available: current position %d makes start %d out of bounds at jump %d",
                cur[idx], start, j+1);
        int y = findp(start, parent);
        // y is the smallest free >= start
        ensuref(y <= M,
                "No empty lily pad exists for jump %d of frog %d: found %d",
                j+1, idx, y);
        // occupy y
        int np = y + 1;
        int py = findp(y, parent);
        int pp = findp(np, parent);
        if (py != pp) parent[py] = pp;
        // update frog position
        cur[idx] = y;
    }
    inf.readEof();
    return 0;
}
