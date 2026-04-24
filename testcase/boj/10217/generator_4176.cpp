#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for diversity
    int N = rnd.next(2, 10);              // number of airports
    int M = rnd.next(0, 100);             // budget
    int maxEdges = N * (N - 1);           // directed edges possible
    int K = (M == 0 ? 0 : rnd.next(0, min(maxEdges, 20)));  // number of tickets

    // build all possible directed edges
    vector<pair<int,int>> cand;
    for (int u = 1; u <= N; ++u) {
        for (int v = 1; v <= N; ++v) {
            if (u != v) cand.emplace_back(u, v);
        }
    }
    shuffle(cand.begin(), cand.end());

    // pick K edges
    cand.resize(K);
    // prepare final edges with cost and time
    vector<tuple<int,int,int,int>> edges;
    for (auto &p : cand) {
        int u = p.first, v = p.second;
        // cost c in [1..M], diverse distribution
        int ct = rnd.next(-1, 1);
        int c = rnd.wnext(max(1, M), ct) + (M > 0 ? 1 : 0);
        if (c > M) c = rnd.next(1, M);
        // time d in [1..1000], diverse distribution
        int tt = rnd.next(-2, 2);
        int d = rnd.wnext(1000, tt) + 1;
        edges.emplace_back(u, v, c, d);
    }

    // output single test case
    println(1);
    println(N, M, K);
    for (auto &e : edges) {
        int u, v, c, d;
        tie(u, v, c, d) = e;
        println(u, v, c, d);
    }
    return 0;
}
