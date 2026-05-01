#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose number of kernels
    int N = rnd.next(2, 12);

    // Decide if the graph is connected or intentionally disconnected
    bool forcedConn = (N <= 3);
    bool isConnected = forcedConn || rnd.next() < 0.7;

    // Hyper-parameter: choose a maximum weight from a variety of scales
    vector<int> weightCaps = {5, 20, 100, 1000, 10000000};
    int maxW = rnd.any(weightCaps);

    vector<tuple<int,int,int>> edges;
    set<pair<int,int>> seen;

    if (isConnected) {
        // First, build a simple chain 1-2,2-3,... to guarantee connectivity
        for (int i = 1; i < N; i++) {
            int w = rnd.next(1, maxW);
            edges.emplace_back(i, i+1, w);
            seen.insert({i, i+1});
        }
        // Add extra random edges
        int totalPairs = N * (N - 1) / 2;
        int maxExtra = totalPairs - (N - 1);
        int extra = (maxExtra > 0 ? rnd.next(0, maxExtra) : 0);

        vector<pair<int,int>> cand;
        cand.reserve(totalPairs);
        for (int i = 1; i <= N; i++) {
            for (int j = i + 1; j <= N; j++) {
                if (!seen.count({i,j}))
                    cand.emplace_back(i, j);
            }
        }
        shuffle(cand.begin(), cand.end());
        for (int i = 0; i < extra; i++) {
            int u = cand[i].first, v = cand[i].second;
            int w = rnd.next(1, maxW);
            edges.emplace_back(u, v, w);
        }
    } else {
        // Intentionally disconnected: fewer than N-1 edges
        int maxM = N - 2; // ensures disconnected
        int M = rnd.next(1, maxM);

        vector<pair<int,int>> cand;
        cand.reserve(N*(N-1)/2);
        for (int i = 1; i <= N; i++) {
            for (int j = i + 1; j <= N; j++) {
                cand.emplace_back(i, j);
            }
        }
        shuffle(cand.begin(), cand.end());
        for (int i = 0; i < M; i++) {
            int u = cand[i].first, v = cand[i].second;
            int w = rnd.next(1, maxW);
            edges.emplace_back(u, v, w);
        }
    }

    // Shuffle edges for added variability
    shuffle(edges.begin(), edges.end());

    // Choose start and end kernels (can be equal)
    int s = rnd.next(1, N);
    int t = rnd.next(1, N);

    // Output
    println(N, (int)edges.size());
    for (auto &e : edges) {
        int u, v, w;
        tie(u, v, w) = e;
        println(u, v, w);
    }
    println(s, t);

    return 0;
}
