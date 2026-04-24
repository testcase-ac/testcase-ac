#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small N for hand-checking
    int N = rnd.next(1, 10);
    vector<int> f(N);

    // Choose generation mode for diversity
    int mode = rnd.next(0, 3);
    if (mode == 0) {
        // Uniform random function
        for (int i = 0; i < N; i++) {
            f[i] = rnd.next(0, N - 1);
        }
    } else if (mode == 1) {
        // Exactly one cycle, others attach as trees
        int csz = rnd.next(1, N);
        vector<int> ids(N);
        iota(ids.begin(), ids.end(), 0);
        shuffle(ids.begin(), ids.end());
        vector<int> cycle(ids.begin(), ids.begin() + csz);
        // form the cycle
        for (int i = 0; i < csz - 1; i++) {
            f[cycle[i]] = cycle[i + 1];
        }
        f[cycle[csz - 1]] = cycle[0];
        // attach other nodes as trees feeding into the cycle
        vector<int> pool = cycle;
        vector<int> others(ids.begin() + csz, ids.end());
        shuffle(others.begin(), others.end());
        for (int u : others) {
            int p = rnd.any(pool);
            f[u] = p;
            pool.push_back(u);
        }
    } else if (mode == 2) {
        // Star: one self-loop center, others point to center
        int c = rnd.next(0, N - 1);
        f[c] = c;
        for (int i = 0; i < N; i++) {
            if (i == c) continue;
            f[i] = c;
        }
    } else {
        // Single chain ending in a self-loop
        vector<int> ids(N);
        iota(ids.begin(), ids.end(), 0);
        shuffle(ids.begin(), ids.end());
        for (int i = 0; i + 1 < N; i++) {
            f[ids[i]] = ids[i + 1];
        }
        if (N > 0) {
            f[ids[N - 1]] = ids[N - 1];
        }
    }

    // Compute reachability matrix
    vector<vector<int>> reach(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        int cur = i;
        while (!reach[i][cur]) {
            reach[i][cur] = 1;
            cur = f[cur];
        }
    }

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        println(reach[i]);
    }

    return 0;
}
