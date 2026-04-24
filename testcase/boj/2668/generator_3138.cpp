#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small N for hand-checkability
    int N = rnd.next(1, 10);
    vector<int> f(N + 1);

    // Hyper-parameter: choose mapping type
    // 0: identity, 1: one big cycle, 2: random disjoint cycles, 3: fully random
    int type = rnd.next(0, 3);

    if (type == 0) {
        // Identity mapping: f[i] = i
        for (int i = 1; i <= N; i++)
            f[i] = i;
    }
    else if (type == 1) {
        // One big cycle over all nodes
        vector<int> perm(N);
        for (int i = 0; i < N; i++) perm[i] = i + 1;
        shuffle(perm.begin(), perm.end());
        for (int i = 0; i < N; i++) {
            int u = perm[i];
            int v = perm[(i + 1) % N];
            f[u] = v;
        }
    }
    else if (type == 2) {
        // Random disjoint cycles covering all nodes
        vector<int> rem(N);
        for (int i = 0; i < N; i++) rem[i] = i + 1;
        shuffle(rem.begin(), rem.end());
        int idx = 0;
        while (idx < N) {
            int remain = N - idx;
            int sz = rnd.next(1, remain);
            vector<int> cyc(rem.begin() + idx, rem.begin() + idx + sz);
            shuffle(cyc.begin(), cyc.end());
            for (int i = 0; i < sz; i++) {
                f[cyc[i]] = cyc[(i + 1) % sz];
            }
            idx += sz;
        }
    }
    else {
        // Fully random mapping: each f[i] is uniform in [1, N]
        for (int i = 1; i <= N; i++) {
            f[i] = rnd.next(1, N);
        }
    }

    // Output in required format
    println(N);
    for (int i = 1; i <= N; i++) {
        println(f[i]);
    }

    return 0;
}
