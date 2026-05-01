#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameters for N
    vector<int> wts = {-2, -1, 0, 1, 2};
    int tN = rnd.any(wts);
    // We want N in [2,15]
    int rawN = rnd.wnext(14, tN); // 0..13
    int N = rawN + 2;

    vector<pair<int,int>> edges;
    int M;

    // Two modes: star teleport vs random graph
    if (rnd.next() < 0.4) {
        // Star mode: pick a hub and connect to random subset of others
        int hub = rnd.next(1, N);
        int cnt = rnd.next(1, N - 1);
        vector<int> others;
        for (int i = 1; i <= N; i++) {
            if (i == hub) continue;
            others.push_back(i);
        }
        shuffle(others.begin(), others.end());
        for (int i = 0; i < cnt; i++) {
            edges.emplace_back(hub, others[i]);
        }
        M = (int)edges.size();
    } else {
        // Random teleporter edges
        long long possible = 1LL * N * (N - 1) / 2;
        double density = rnd.next();
        int rawMmax = int(density * possible);
        int Mmax = min(rawMmax, 40); // cap to keep input compact
        if (Mmax < 0) Mmax = 0;
        M = rnd.next(0, Mmax);
        // build all pairs
        vector<pair<int,int>> all;
        for (int i = 1; i <= N; i++)
            for (int j = i + 1; j <= N; j++)
                all.emplace_back(i, j);
        shuffle(all.begin(), all.end());
        edges.assign(all.begin(), all.begin() + M);
    }

    // Choose start S and end E with some bias
    int tS = rnd.any(wts);
    int S = rnd.wnext(N, tS) + 1;
    int tE = rnd.any(wts);
    int E = rnd.wnext(N, tE) + 1;
    if (E == S) {
        E = (E % N) + 1;
    }

    // Output
    println(N, M);
    println(S, E);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    return 0;
}
