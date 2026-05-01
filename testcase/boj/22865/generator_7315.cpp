#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of nodes
    int N = rnd.next(2, 15);
    // Build a random spanning tree
    vector<int> nodes(N);
    iota(nodes.begin(), nodes.end(), 1);
    shuffle(nodes.begin(), nodes.end());
    vector<pair<int,int>> edges;
    set<pair<int,int>> used;
    for (int i = 1; i < N; i++) {
        int u = nodes[i];
        int v = nodes[rnd.next(0, i-1)];
        if (u > v) swap(u, v);
        edges.emplace_back(u, v);
        used.insert({u, v});
    }
    // Determine total edges M
    int maxPossible = N * (N - 1) / 2;
    int extraMax = (N <= 7 ? maxPossible - (N - 1) : min(N, maxPossible - (N - 1)));
    int extra = extraMax > 0 ? rnd.next(0, extraMax) : 0;
    int M = (N - 1) + extra;
    // Prepare candidate extra edges
    vector<pair<int,int>> cand;
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            if (!used.count({i, j})) cand.emplace_back(i, j);
        }
    }
    shuffle(cand.begin(), cand.end());
    for (int i = 0; i < extra; i++) {
        edges.push_back(cand[i]);
    }
    // Hyper-parameter for weights
    vector<int> Wchoices = {1, 5, 10, 1000};
    int W = rnd.any(Wchoices);
    // Select friend positions, allowing some duplicates
    int A = rnd.next(1, N);
    int B = (rnd.next(0, 3) == 0 ? A : rnd.next(1, N));
    int r = rnd.next(0, 5);
    int C = (r == 0 ? A : (r == 1 ? B : rnd.next(1, N)));
    // Output
    println(N);
    println(A, B, C);
    println(M);
    for (auto &e : edges) {
        int w = rnd.next(1, W);
        println(e.first, e.second, w);
    }
    return 0;
}
