#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // N between 2 and 8
    int N = rnd.next(2, 8);
    // Generate array A with different patterns
    vector<int> A(N);
    int tA = rnd.next(0, 3);
    if (tA == 0) {
        // random
        for (int i = 0; i < N; i++) A[i] = rnd.next(1, 10);
    } else if (tA == 1) {
        // sorted
        for (int i = 0; i < N; i++) A[i] = rnd.next(1, 10);
        sort(A.begin(), A.end());
    } else if (tA == 2) {
        // reverse sorted
        for (int i = 0; i < N; i++) A[i] = rnd.next(1, 10);
        sort(A.begin(), A.end());
        reverse(A.begin(), A.end());
    } else {
        // many duplicates
        int d = rnd.next(1, N);
        vector<int> vals(10);
        iota(vals.begin(), vals.end(), 1);
        shuffle(vals.begin(), vals.end());
        vals.resize(d);
        for (int i = 0; i < N; i++) A[i] = rnd.any(vals);
    }

    // Build all possible swap operations (pairs of positions)
    vector<pair<int,int>> allPairs;
    for (int i = 1; i <= N; i++)
        for (int j = i + 1; j <= N; j++)
            allPairs.emplace_back(i, j);
    int maxPairs = (int)allPairs.size();
    int Mmax = min(10, maxPairs);
    shuffle(allPairs.begin(), allPairs.end());

    // Choose mode for M and connectivity
    int mode = rnd.next(0, 3);
    int M;
    if (mode == 0) {
        // sparse
        M = rnd.next(1, min(N-1, Mmax));
    } else if (mode == 1) {
        // dense
        M = rnd.next(min(N-1, Mmax), Mmax);
    } else if (mode == 2) {
        // random
        M = rnd.next(1, Mmax);
    } else {
        // ensure connectivity
        M = rnd.next(min(N-1, Mmax), Mmax);
    }

    vector<pair<int,int>> ops;
    if (mode == 3) {
        // create a spanning tree randomly
        vector<int> perm(N);
        iota(perm.begin(), perm.end(), 1);
        shuffle(perm.begin(), perm.end());
        for (int i = 0; i < N-1; i++) {
            int u = perm[i], v = perm[i+1];
            if (u > v) swap(u, v);
            ops.emplace_back(u, v);
        }
        // remove tree edges from pool
        vector<pair<int,int>> pool;
        for (auto &p : allPairs) {
            bool ok = true;
            for (auto &q : ops)
                if (p.first == q.first && p.second == q.second) { ok = false; break; }
            if (ok) pool.push_back(p);
        }
        shuffle(pool.begin(), pool.end());
        int need = M - (int)ops.size();
        for (int i = 0; i < need && i < (int)pool.size(); i++)
            ops.push_back(pool[i]);
    } else {
        // take first M random edges
        for (int i = 0; i < M; i++)
            ops.push_back(allPairs[i]);
    }

    // assign costs
    vector<int> costs;
    for (int i = 0; i < (int)ops.size(); i++) {
        // bias cost distribution a bit
        int c = rnd.wnext(10, rnd.next(-1, 1)) + 1;
        if (c > 10) c = 10;
        costs.push_back(c);
    }

    // Output
    println(N);
    println(A);
    println((int)ops.size());
    for (int i = 0; i < (int)ops.size(); i++) {
        printf("%d %d %d\n", ops[i].first, ops[i].second, costs[i]);
    }
    return 0;
}
