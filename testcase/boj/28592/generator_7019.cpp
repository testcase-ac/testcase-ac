#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of nodes: biased towards small but up to 12
    int N = rnd.wnext(12, -2) + 1;
    // Number of queries: between 1 and min(2*N,20)
    int maxQ = max(1, min(N * 2, 20));
    int Q = rnd.next(1, maxQ);
    // Build a tree with varied shapes: chain, star, or random
    vector<pair<int,int>> edges;
    if (N >= 2) {
        int shape = rnd.next(0, 2);
        if (shape == 0) {
            // chain
            for (int i = 1; i < N; i++)
                edges.emplace_back(i, i+1);
        } else if (shape == 1) {
            // star
            int c = rnd.next(1, N);
            for (int i = 1; i <= N; i++)
                if (i != c) edges.emplace_back(c, i);
        } else {
            // random tree
            for (int i = 2; i <= N; i++)
                edges.emplace_back(rnd.next(1, i-1), i);
        }
        shuffle(edges.begin(), edges.end());
    }
    // Assign species labels with varied maximum value
    double t = rnd.next();
    int maxV;
    if (t < 0.5) maxV = rnd.next(1, 3);
    else if (t < 0.8) maxV = rnd.next(4, 10);
    else maxV = rnd.next(11, 20);
    vector<int> v(N);
    for (int i = 0; i < N; i++)
        v[i] = rnd.next(1, maxV);
    // Output
    println(N, Q);
    println(v);
    for (auto &e : edges)
        println(e.first, e.second);
    for (int i = 0; i < Q; i++) {
        int a = rnd.next(1, N), b = rnd.next(1, N);
        println(a, b);
    }
    return 0;
}
