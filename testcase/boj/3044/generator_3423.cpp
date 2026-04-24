#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of towns
    int N = rnd.next(2, 10);
    // Decide if we want an infinite-path case
    bool infinite = rnd.next(0, 1) == 1;
    // For finite cases, sometimes force at least one path
    bool forcePath = !infinite && rnd.next(0, 1) == 1;

    vector<pair<int,int>> edges;

    // Guarantee at least one path if needed
    if (forcePath || infinite) {
        if (N == 2) {
            edges.emplace_back(1, 2);
        } else {
            int maxMids = N - 2;
            int k = rnd.next(0, maxMids);
            vector<int> mids(N - 2);
            iota(mids.begin(), mids.end(), 3);
            shuffle(mids.begin(), mids.end());
            mids.resize(k);
            int u = 1;
            for (int v : mids) {
                edges.emplace_back(u, v);
                u = v;
            }
            edges.emplace_back(u, 2);
        }
    }

    // Add a reachable cycle for infinite cases
    if (infinite) {
        int cycleLen = rnd.next(1, N);
        vector<int> nodes(N);
        iota(nodes.begin(), nodes.end(), 1);
        shuffle(nodes.begin(), nodes.end());
        nodes.resize(cycleLen);
        for (int i = 0; i < cycleLen; i++) {
            int a = nodes[i];
            int b = nodes[(i + 1) % cycleLen];
            edges.emplace_back(a, b);
        }
        int x = nodes[0];
        edges.emplace_back(1, x);
        edges.emplace_back(x, 2);
    }

    // Random extra edges (could include duplicates/self-loops)
    int extraMax = min(20, N * (N - 1));
    int extra = rnd.next(0, extraMax);
    for (int i = 0; i < extra; i++) {
        int a = rnd.next(1, N);
        int b = rnd.next(1, N);
        edges.emplace_back(a, b);
    }

    // Ensure at least one edge
    if (edges.empty()) {
        edges.emplace_back(rnd.next(1, N), rnd.next(1, N));
    }

    // Shuffle for randomness
    shuffle(edges.begin(), edges.end());

    int M = edges.size();
    println(N, M);
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    return 0;
}
