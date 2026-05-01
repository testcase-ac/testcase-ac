#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: small, medium, or larger (but <=12)
    int N;
    int ncase = rnd.next(0, 2);
    if (ncase == 0) {
        N = rnd.next(2, 5);
    } else if (ncase == 1) {
        N = rnd.next(6, 8);
    } else {
        N = rnd.next(9, 12);
    }

    // Choose tree shape: 0=chain, 1=star, 2=random spanning tree
    int shape = rnd.next(0, 2);
    vector<pair<int,int>> edges;
    if (shape == 0) {
        // Chain 1-2-3-...-N
        for (int i = 1; i < N; i++) {
            edges.emplace_back(i, i+1);
        }
    } else if (shape == 1) {
        // Star centered at random node
        int center = rnd.next(1, N);
        for (int i = 1; i <= N; i++) {
            if (i != center) edges.emplace_back(center, i);
        }
    } else {
        // Random spanning tree via prefix method
        vector<int> order(N);
        for (int i = 0; i < N; i++) order[i] = i + 1;
        shuffle(order.begin(), order.end());
        for (int i = 1; i < N; i++) {
            int u = order[i];
            int v = order[rnd.next(0, i-1)];
            edges.emplace_back(u, v);
        }
    }

    // Hyper-parameter for edge weights: mostly small or mostly large
    int maxW;
    if (rnd.next(0,1) == 0) {
        maxW = rnd.next(5, 20);
    } else {
        maxW = rnd.next(100, 10000);
    }

    // Assign a random weight in [1, maxW] to each edge
    vector<tuple<int,int,int>> we;
    for (auto &e : edges) {
        int w = rnd.next(1, maxW);
        we.emplace_back(e.first, e.second, w);
    }

    // Hyper-parameter for number of queries M
    int maxPairs = N*(N-1)/2;
    int M;
    if (rnd.next(0,1) == 0) {
        M = rnd.next(1, min(maxPairs, 5));
    } else {
        int lo = min(maxPairs, 6);
        int hi = min(maxPairs, 20);
        M = rnd.next(lo, hi);
    }

    // Generate all possible unordered pairs
    vector<pair<int,int>> queries;
    for (int u = 1; u <= N; u++) {
        for (int v = u + 1; v <= N; v++) {
            queries.emplace_back(u, v);
        }
    }
    shuffle(queries.begin(), queries.end());
    queries.resize(M);
    // Randomly swap order of each query
    for (auto &q : queries) {
        if (rnd.next(0,1) == 0) swap(q.first, q.second);
    }

    // Output
    println(N, M);
    for (auto &t : we) {
        int u, v, w;
        tie(u, v, w) = t;
        println(u, v, w);
    }
    for (auto &q : queries) {
        println(q.first, q.second);
    }
    return 0;
}
