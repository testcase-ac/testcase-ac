#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);
    for (int ti = 0; ti < T; ti++) {
        // Number of nodes
        int N = rnd.next(2, 10);
        // Max possible directed edges excluding self-loops, but cap small
        int maxE = min(N*(N-1), 20);
        // Choose E with bias: sometimes dense, sometimes sparse
        int E;
        if (rnd.next() < 0.5) {
            // bias to small
            E = rnd.wnext(maxE, -1) + 1;
        } else {
            // bias to large
            E = rnd.wnext(maxE, +1) + 1;
        }
        // Choose distinct A, B
        int A = rnd.next(0, N-1);
        int B;
        do { B = rnd.next(0, N-1); } while (B == A);
        // Weight range hyper-parameter
        int maxW;
        if (rnd.next() < 0.5) {
            maxW = rnd.next(5, 20);  // small weights
        } else {
            maxW = rnd.next(100, 1000); // large weights
        }
        // Pre-generate all possible directed edges (u != v)
        vector<pair<int,int>> cand;
        cand.reserve(N*(N-1));
        for (int u = 0; u < N; u++) {
            for (int v = 0; v < N; v++) {
                if (u != v) cand.emplace_back(u, v);
            }
        }
        // Remove guaranteed edge (A,B) from candidates
        cand.erase(remove(cand.begin(), cand.end(), make_pair(A, B)), cand.end());
        // Shuffle candidates
        shuffle(cand.begin(), cand.end());
        // Build edges: reserve one direct A->B, then take E-1 others
        vector<pair<int,int>> edges;
        edges.reserve(E);
        edges.emplace_back(A, B);
        for (int i = 0; i < E-1; i++) {
            edges.push_back(cand[i]);
        }
        // Shuffle final edge list
        shuffle(edges.begin(), edges.end());
        // Decide a special weight for the direct A->B edge
        int specialW;
        if (rnd.next() < 0.5) {
            specialW = rnd.next(maxW/2 + 1, maxW);
        } else {
            specialW = rnd.next(1, max(1, maxW/2));
        }
        // Output this test case
        println(N, E, A, B);
        for (auto &e : edges) {
            int w;
            if (e.first == A && e.second == B) {
                w = specialW;
            } else {
                w = rnd.next(1, maxW);
            }
            println(e.first, e.second, w);
        }
    }
    return 0;
}
