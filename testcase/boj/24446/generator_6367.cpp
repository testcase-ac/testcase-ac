#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of vertices
    int N = rnd.next(5, 15);
    // Choose graph type: 0=tree,1=sparse,2=medium,3=dense,4=star+extra
    int gtype = rnd.next(0, 4);
    int maxEdges = N * (N - 1) / 2;
    vector<pair<int,int>> edges;

    if (gtype == 0) {
        // a random tree
        for (int v = 2; v <= N; v++) {
            int u = rnd.next(1, v-1);
            int a = min(u, v), b = max(u, v);
            edges.emplace_back(a, b);
        }
    } else if (gtype == 4) {
        // star centered at C, then some extra edges
        int C = rnd.next(1, N);
        vector<vector<bool>> used(N+1, vector<bool>(N+1, false));
        // star edges
        for (int v = 1; v <= N; v++) {
            if (v == C) continue;
            int a = min(C, v), b = max(C, v);
            edges.emplace_back(a, b);
            used[a][b] = used[b][a] = true;
        }
        // possible extra edges
        vector<pair<int,int>> cand;
        for (int i = 1; i <= N; i++) {
            for (int j = i+1; j <= N; j++) {
                if (!used[i][j]) cand.emplace_back(i, j);
            }
        }
        shuffle(cand.begin(), cand.end());
        int extra = rnd.next(0, min((int)cand.size(), N/2));
        for (int i = 0; i < extra; i++) edges.push_back(cand[i]);
    } else {
        // random edge selection from all pairs
        vector<pair<int,int>> all;
        all.reserve(maxEdges);
        for (int i = 1; i <= N; i++)
            for (int j = i+1; j <= N; j++)
                all.emplace_back(i, j);
        // decide M based on type
        int M;
        if (gtype == 1) {
            // sparse: just above a tree up to N+5
            M = rnd.next(N-1, min(maxEdges, N + 5));
        } else if (gtype == 2) {
            // medium: between N+5 and 3N
            M = rnd.next(min(maxEdges, N + 5), min(maxEdges, 3*N));
        } else {
            // dense: from 3N to full
            M = rnd.next(min(maxEdges, 3*N), maxEdges);
        }
        shuffle(all.begin(), all.end());
        edges.assign(all.begin(), all.begin() + M);
    }

    // Shuffle final edge list for randomness
    shuffle(edges.begin(), edges.end());
    int M = edges.size();
    int R = rnd.next(1, N);

    // Output
    println(N, M, R);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    return 0;
}
