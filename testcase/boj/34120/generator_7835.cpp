#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of buildings
    int N = rnd.next(3, 15);

    // Build all possible directed edges (no self-loops)
    vector<pair<int,int>> allEdges;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            if (i != j)
                allEdges.emplace_back(i, j);
    shuffle(allEdges.begin(), allEdges.end());

    // Always ensure a path from 1 to N
    int pathLen = rnd.next(2, N); // number of nodes in path
    vector<int> mids;
    for (int i = 2; i <= N - 1; i++) mids.push_back(i);
    shuffle(mids.begin(), mids.end());
    vector<int> pathNodes;
    pathNodes.push_back(1);
    for (int i = 0; i < pathLen - 2; i++)
        pathNodes.push_back(mids[i]);
    pathNodes.push_back(N);

    vector<pair<int,int>> edges;
    set<long long> used;
    for (int i = 0; i + 1 < (int)pathNodes.size(); i++) {
        int u = pathNodes[i], v = pathNodes[i+1];
        edges.emplace_back(u, v);
        used.insert((long long)u * (N+1) + v);
    }

    // Extra edges
    int maxTotalEdges = min((int)allEdges.size(), N * 3);
    int minTotalEdges = max((int)edges.size(), 3);
    int M = rnd.next(minTotalEdges, maxTotalEdges);
    for (auto &e : allEdges) {
        if ((int)edges.size() == M) break;
        long long id = (long long)e.first * (N+1) + e.second;
        if (used.count(id)) continue;
        edges.push_back(e);
        used.insert(id);
    }
    shuffle(edges.begin(), edges.end());

    // Hyper-parameters
    bool unitTimes = rnd.next(0, 1);
    vector<double> windowProps = {0.2, 0.5, 0.8};
    double windowProb = rnd.any(windowProps);
    vector<int> smallAB = {1, 2, 5, 10};
    int a = rnd.any(smallAB);
    int b = rnd.any(smallAB);

    // Build window flags c[1..N]
    vector<int> c(N+1, 0);
    for (int i = 2; i <= N-1; i++)
        c[i] = (rnd.next() < windowProb ? 1 : 0);
    c[1] = 0; c[N] = 0;

    // Output
    println(N, M);
    for (auto &e : edges) {
        int t = unitTimes ? 1 : rnd.next(1, 20);
        println(e.first, e.second, t);
    }
    // Print c[1..N]
    vector<int> cv(c.begin() + 1, c.end());
    println(cv);
    println(a, b);

    return 0;
}
