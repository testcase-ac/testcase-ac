#include <vector>
#include <set>
#include <algorithm>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose small number of towns
    int N = rnd.next(2, 10);
    int X = rnd.next(1, N);
    // Prepare list of other towns
    vector<int> others;
    for (int i = 1; i <= N; ++i) {
        if (i != X) others.push_back(i);
    }
    set<pair<int,int>> seen;
    vector<pair<pair<int,int>, int>> edges;
    // Build in-tree to ensure each node can reach X
    vector<int> procIn = {X};
    shuffle(others.begin(), others.end());
    for (int u : others) {
        int v = rnd.any(procIn);
        if (seen.insert({u, v}).second) {
            int w = rnd.next(1, 100);
            edges.push_back({{u, v}, w});
        }
        procIn.push_back(u);
    }
    // Build out-tree to ensure X can reach each node
    vector<int> procOut = {X};
    vector<int> order = others;
    shuffle(order.begin(), order.end());
    for (int v : order) {
        int u = rnd.any(procOut);
        if (seen.insert({u, v}).second) {
            int w = rnd.next(1, 100);
            edges.push_back({{u, v}, w});
        }
        procOut.push_back(v);
    }
    // Determine extra edges to add (cap total edges ≤20)
    int base = seen.size();
    int maxTotal = N * (N - 1);
    int maxExtra = min(maxTotal - base, 20 - base);
    if (maxExtra < 0) maxExtra = 0;
    int extra = rnd.next(0, maxExtra);
    int M = base + extra;
    // Add random extra edges
    while ((int)seen.size() < M) {
        int u = rnd.next(1, N);
        int v = rnd.next(1, N);
        if (u == v) continue;
        if (!seen.insert({u, v}).second) continue;
        int w = rnd.next(1, 100);
        edges.push_back({{u, v}, w});
    }
    // Output
    println(N, M, X);
    for (auto &e : edges) {
        println(e.first.first, e.first.second, e.second);
    }
    return 0;
}
