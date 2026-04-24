#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters
    int N = rnd.next(2, 10);
    int K = rnd.next(1, 200);
    // Choose source and destination
    int A = rnd.next(1, N);
    int B = rnd.next(1, N);
    while (B == A) B = rnd.next(1, N);
    // Decide if solvable
    bool solvable = rnd.next(0, 1);
    // Determine number of edges, cap for smallness
    int maxDir = N * (N - 1);
    int M = rnd.next(N - 1, min(maxDir, 20));
    // Container for edges
    struct E { int u, v, t, h; };
    vector<E> edges;
    vector<vector<bool>> used(N+1, vector<bool>(N+1, false));
    // If solvable, create a safe path
    if (solvable) {
        int L = rnd.next(1, N - 1);
        // Build a random path of length L from A to B via distinct nodes
        vector<int> nodes;
        for (int i = 1; i <= N; i++) if (i != A && i != B) nodes.push_back(i);
        shuffle(nodes.begin(), nodes.end());
        nodes.resize(L - 1);
        vector<int> path;
        path.push_back(A);
        for (int x : nodes) path.push_back(x);
        path.push_back(B);
        // Distribute damage h_i so total = K-1 (<K)
        int remain = K - 1;
        for (int i = 0; i < L; i++) {
            int u = path[i], v = path[i+1];
            int h;
            if (i == L-1) {
                h = remain;
            } else {
                h = rnd.next(0, remain);
                remain -= h;
            }
            int t = rnd.next(1, 20);
            edges.push_back({u, v, t, h});
            used[u][v] = true;
        }
    }
    // Build list of candidate directed edges not yet used
    vector<pair<int,int>> cand;
    for (int u = 1; u <= N; u++) {
        for (int v = 1; v <= N; v++) {
            if (u != v && !used[u][v]) {
                cand.emplace_back(u, v);
            }
        }
    }
    shuffle(cand.begin(), cand.end());
    // Add random edges to reach M
    for (int i = 0; (int)edges.size() < M && i < (int)cand.size(); i++) {
        int u = cand[i].first, v = cand[i].second;
        int t = rnd.next(1, 20);
        int h;
        if (solvable) {
            // random damage, could be safe or not
            h = rnd.next(0, 200);
        } else {
            // force every edge unsafe by itself
            h = rnd.next(K, min(200, K + 20));
        }
        edges.push_back({u, v, t, h});
    }
    // Output
    println(K, N, M);
    for (auto &e : edges) {
        println(e.u, e.v, e.t, e.h);
    }
    println(A, B);
    return 0;
}
