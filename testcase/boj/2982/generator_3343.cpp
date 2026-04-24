#include "testlib.h"
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <numeric>
using namespace std;

int findp(vector<int>& p, int x) {
    return p[x] == x ? x : p[x] = findp(p, p[x]);
}

void unite(vector<int>& p, int x, int y) {
    x = findp(p, x);
    y = findp(p, y);
    if (x != y) p[x] = y;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of nodes
    int N = rnd.next(3, 10);
    // Length of the king's visit sequence
    int G = rnd.next(2, min(N, 5));
    // Sample the king's path nodes (distinct)
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);
    shuffle(perm.begin(), perm.end());
    vector<int> gpath(perm.begin(), perm.begin() + G);

    // Prepare DSU for connectivity
    vector<int> parent(N + 1);
    iota(parent.begin(), parent.end(), 0);

    // Edge set and weight map
    set<pair<int,int>> edges;
    map<pair<int,int>, int> weight;

    // Hyper-parameter for weights
    int maxL = rnd.next(5, 20);
    int minL = rnd.next(1, maxL);

    // 1) Ensure king's path edges exist
    for (int i = 0; i + 1 < G; i++) {
        int u = gpath[i], v = gpath[i+1];
        pair<int,int> e = u < v ? make_pair(u, v) : make_pair(v, u);
        if (!edges.count(e)) {
            edges.insert(e);
            weight[e] = rnd.next(minL, maxL);
            unite(parent, u, v);
        }
    }

    // 2) Add edges to form a spanning tree (connect all components)
    while ((int)edges.size() < N - 1) {
        int u = rnd.next(1, N), v = rnd.next(1, N);
        if (u == v) continue;
        int pu = findp(parent, u), pv = findp(parent, v);
        if (pu == pv) continue;
        pair<int,int> e = u < v ? make_pair(u, v) : make_pair(v, u);
        if (edges.count(e)) continue;
        edges.insert(e);
        weight[e] = rnd.next(minL, maxL);
        unite(parent, u, v);
    }

    // 3) Decide total number of edges M
    int maxEdges = N * (N - 1) / 2;
    int M = rnd.next((int)edges.size(), maxEdges);

    // 4) Add random extra edges up to M
    vector<pair<int,int>> cand;
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            pair<int,int> e = make_pair(i, j);
            if (!edges.count(e)) cand.push_back(e);
        }
    }
    shuffle(cand.begin(), cand.end());
    for (int i = 0; (int)edges.size() < M && i < (int)cand.size(); i++) {
        auto e = cand[i];
        edges.insert(e);
        weight[e] = rnd.next(minL, maxL);
    }

    // 5) Pick start A and end B for the delivery (distinct)
    int A = rnd.next(1, N);
    int B;
    do { B = rnd.next(1, N); } while (B == A);

    // 6) Delay K
    int K = rnd.next(0, 10);

    // Output
    println(N, M);
    println(A, B, K, G);
    println(gpath);

    // Shuffle edges before output for diversity
    vector<pair<int,int>> outE(edges.begin(), edges.end());
    shuffle(outE.begin(), outE.end());
    for (auto &e : outE) {
        println(e.first, e.second, weight[e]);
    }

    return 0;
}
