#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for number of topics N (1..10), biased
    int tN = rnd.next(-1, 1);
    int N = rnd.wnext(10, tN) + 1;

    // Create a random topological order of topics 1..N
    vector<int> order(N);
    iota(order.begin(), order.end(), 1);
    shuffle(order.begin(), order.end());

    // Hyper-parameter for maximum base time Emax (1..100), biased
    int t_e = rnd.next(-1, 1);
    int Emax = rnd.wnext(100, t_e) + 1;

    // Assign base times e_i
    vector<int> e(N+1);
    for (int u = 1; u <= N; u++) {
        e[u] = rnd.next(1, Emax);
    }

    // Hyper-parameter for dependency density bias
    int t_d = rnd.next(-1, 1);

    // Build dependencies respecting the topological order
    vector<vector<int>> deps(N+1);
    for (int idx = 0; idx < N; idx++) {
        int u = order[idx];
        int prev = idx; // number of earlier nodes
        if (prev > 0) {
            // choose di in [0..prev], biased by t_d
            int di = rnd.wnext(prev + 1, t_d);
            // pick a random subset of size di from the earlier nodes
            vector<int> cand(order.begin(), order.begin() + idx);
            shuffle(cand.begin(), cand.end());
            deps[u].insert(deps[u].end(), cand.begin(), cand.begin() + di);
            // shuffle the chosen dependencies for output diversity
            shuffle(deps[u].begin(), deps[u].end());
        }
    }

    // Output in the required format
    println(N);
    for (int i = 1; i <= N; i++) {
        int di = (int)deps[i].size();
        printf("%d %d", e[i], di);
        for (int v : deps[i]) {
            printf(" %d", v);
        }
        printf("\n");
    }

    return 0;
}
