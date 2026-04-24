#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
#include <array>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of islands
    int N = rnd.next(2, 10);
    // Choose two distinct factory locations
    int S = rnd.next(1, N);
    int T;
    do {
        T = rnd.next(1, N);
    } while (T == S);

    // Build a guaranteed path from S to T
    int len = rnd.next(1, N - 1);  // number of edges on the path
    vector<int> others;
    for (int i = 1; i <= N; ++i)
        if (i != S && i != T)
            others.push_back(i);
    shuffle(others.begin(), others.end());
    vector<int> path;
    path.push_back(S);
    for (int i = 0; i < len - 1; ++i)
        path.push_back(others[i]);
    path.push_back(T);

    // Hyper-parameter for weights
    int maxW = rnd.next(10, 1000);
    int bias = rnd.next(-1, 1);  // bias >0 => heavier edges, <0 => lighter edges

    vector<array<int,3>> edges;
    set<pair<int,int>> used;
    edges.reserve(N + 20);

    // Add the guaranteed path edges
    for (int i = 0; i < len; ++i) {
        int u = path[i], v = path[i+1];
        int w = rnd.wnext(maxW, bias) + 1;
        edges.push_back({u, v, w});
        used.insert({min(u,v), max(u,v)});
    }

    // Add extra random edges
    int Mmax = N * (N - 1) / 2;
    int maxExtra = min(Mmax - len, 15);
    int extra = rnd.next(0, maxExtra);
    vector<pair<int,int>> candidates;
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            if (!used.count({i, j}))
                candidates.emplace_back(i, j);
        }
    }
    shuffle(candidates.begin(), candidates.end());
    for (int i = 0; i < extra; ++i) {
        int u = candidates[i].first;
        int v = candidates[i].second;
        int w = rnd.wnext(maxW, bias) + 1;
        edges.push_back({u, v, w});
    }

    // Finalize M and shuffle all edges
    int M = edges.size();
    shuffle(edges.begin(), edges.end());

    // Output
    println(N, M);
    for (auto &e : edges)
        println(e[0], e[1], e[2]);
    println(S, T);

    return 0;
}
