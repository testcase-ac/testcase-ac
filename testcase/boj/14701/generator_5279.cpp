#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small sizes
    int N = rnd.next(2, 10);
    int maxM = min(20, 2 * N + 5);
    int M = rnd.next(1, maxM);

    // Remaining students on board
    vector<int> rem(N);
    iota(rem.begin(), rem.end(), 1);

    vector<pair<int,int>> ops;
    bool hasQuery = false;

    for (int i = 0; i < M; i++) {
        bool canRemove = !rem.empty();
        bool doRemove = false;
        if (canRemove) {
            // Hyperparameter: more removals while many students remain
            double frac = double(rem.size()) / N;
            double removeProb = 0.4 + 0.6 * frac; // from 0.4 to 1.0
            doRemove = (rnd.next() < removeProb);
        }
        if (doRemove) {
            int x = rnd.any(rem);
            ops.emplace_back(1, x);
            // erase x from rem
            auto it = find(rem.begin(), rem.end(), x);
            rem.erase(it);
        } else {
            int x = rnd.next(1, N);
            ops.emplace_back(2, x);
            hasQuery = true;
        }
    }
    // Ensure at least one query
    if (!hasQuery) {
        ops[0] = {2, rnd.next(1, N)};
    }

    // Output
    println(N, M);
    for (auto &p : ops) {
        println(p.first, p.second);
    }
    return 0;
}
