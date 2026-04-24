#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of cities
    int N = rnd.next(3, 10);

    // Prepare available intermediate nodes (3..N)
    vector<int> avail;
    for (int i = 3; i <= N; i++) avail.push_back(i);
    shuffle(avail.begin(), avail.end());

    // Decide number of guaranteed node-disjoint paths (at least 1)
    int maxPaths = min(3, N - 2);
    int kPaths = rnd.next(1, maxPaths);

    vector<pair<int,int>> edges;
    set<pair<int,int>> used;
    int idx = 0;
    // Build kPaths node-disjoint simple paths from 1 to 2
    for (int i = 0; i < kPaths; i++) {
        int remPaths = kPaths - i - 1;
        int remainNodes = (int)avail.size() - idx;
        int maxC = max(1, min(2, remainNodes - remPaths));
        int c = rnd.next(1, maxC);
        int cur = 1;
        for (int j = 0; j < c; j++) {
            int nxt = avail[idx++];
            edges.emplace_back(cur, nxt);
            used.insert({cur, nxt});
            cur = nxt;
        }
        // connect to 2
        edges.emplace_back(cur, 2);
        used.insert({cur, 2});
    }

    // Collect remaining candidate edges (no self-loops, no direct 1<->2, no duplicates)
    vector<pair<int,int>> cand;
    for (int u = 1; u <= N; u++) {
        for (int v = 1; v <= N; v++) {
            if (u == v) continue;
            if ((u == 1 && v == 2) || (u == 2 && v == 1)) continue;
            if (used.count({u, v})) continue;
            cand.emplace_back(u, v);
        }
    }
    shuffle(cand.begin(), cand.end());

    // Add some extra random edges for diversity
    int maxExtra = min((int)cand.size(), 10);
    vector<int> biases = {-3, -1, 0, 1, 3};
    int tExtra = rnd.any(biases);
    int extraCount = rnd.wnext(maxExtra + 1, tExtra);
    for (int i = 0; i < extraCount; i++) {
        auto e = cand[i];
        edges.push_back(e);
        used.insert(e);
    }

    // Final shuffle of all edges
    shuffle(edges.begin(), edges.end());

    // Output
    println(N, (int)edges.size());
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    return 0;
}
