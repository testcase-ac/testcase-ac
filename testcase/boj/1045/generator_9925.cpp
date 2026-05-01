#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N = 0, M = 0;
    int E = 0;
    vector<string> g;

    auto initMatrix = [&](int n) {
        N = n;
        g.assign(N, string(N, 'N'));
        E = 0;
    };

    auto addEdge = [&](int u, int v) {
        if (u == v) return;
        if (u > v) swap(u, v);
        if (g[u][v] == 'N') {
            g[u][v] = g[v][u] = 'Y';
            ++E;
        }
    };

    int type = rnd.next(0, 5); // 6 different scenario types

    switch (type) {
        // Type 0: K3 cluster + path tail, connected, tricky lexicographic case
        case 0: {
            int n = rnd.next(4, 10);
            initMatrix(n);
            // K3 on {0,1,2}
            addEdge(0, 1);
            addEdge(0, 2);
            addEdge(1, 2);
            // Path from 2 to n-1
            for (int v = 3; v < N; ++v) {
                addEdge(v - 1, v); // edges 2-3,3-4,...
            }
            // E = N, connected. Make M = N-1 to force tradeoff between high-priority cluster edges and tail edges.
            M = N - 1;
            break;
        }

        // Type 1: Two cliques connected by a single bridge edge, another lexicographic trap
        case 1: {
            int nA, nB, n;
            while (true) {
                nA = rnd.next(4, 6); // size of first clique
                int EA = nA * (nA - 1) / 2;
                int maxNB = min(4, EA + 1 - nA); // ensure N-1 <= EA
                if (maxNB >= 2) {
                    nB = rnd.next(2, maxNB);
                    n = nA + nB;
                    break;
                }
            }
            initMatrix(n);
            // Clique A: vertices [0 .. nA-1]
            for (int i = 0; i < nA; ++i)
                for (int j = i + 1; j < nA; ++j)
                    addEdge(i, j);
            // Clique B: vertices [nA .. n-1]
            for (int i = nA; i < n; ++i)
                for (int j = i + 1; j < n; ++j)
                    addEdge(i, j);
            // Single bridge edge
            addEdge(nA - 1, nA);
            // Choose M = N-1 so that top M edges ignore the bridge and B, causing disconnection
            M = N - 1;
            break;
        }

        // Type 2: Connected graph but E < M (impossible because not enough edges)
        case 2: {
            int n = rnd.next(3, 10);
            initMatrix(n);
            // Build a random spanning tree
            for (int i = 1; i < N; ++i) {
                int p = rnd.next(0, i - 1);
                addEdge(p, i);
            }
            // Add a small random number of extra edges (up to 3)
            int ex = rnd.next(0, 3);
            vector<pair<int,int>> cand;
            for (int i = 0; i < N; ++i)
                for (int j = i + 1; j < N; ++j)
                    if (g[i][j] == 'N')
                        cand.push_back({i, j});
            shuffle(cand.begin(), cand.end());
            ex = min(ex, (int)cand.size());
            for (int k = 0; k < ex; ++k)
                addEdge(cand[k].first, cand[k].second);
            // Now choose M > E, ensuring M >= N-1
            int delta = rnd.next(1, 3);
            M = min(1000, E + delta);
            if (M < N - 1) M = N - 1; // safety, though E >= N-1 so normally unnecessary
            break;
        }

        // Type 3: Underlying graph disconnected (two components), E >= M
        case 3: {
            int n = rnd.next(3, 12);
            initMatrix(n);
            int K = rnd.next(1, N - 2); // first component size: [1 .. N-2]
            // First component tree: vertices [0 .. K-1]
            for (int i = 1; i < K; ++i) {
                int p = rnd.next(0, i - 1);
                addEdge(p, i);
            }
            // Second component tree: vertices [K .. N-1]
            for (int i = K + 1; i < N; ++i) {
                int p = rnd.next(K, i - 1);
                addEdge(p, i);
            }
            // Ensure at least N-1 edges (so E >= M >= N-1 is possible)
            int need = (N - 1) - E;
            if (need < 0) need = 0;
            vector<pair<int,int>> cand;
            // Intra-component non-edges only (no cross edges to keep graph disconnected)
            for (int i = 0; i < K; ++i)
                for (int j = i + 1; j < K; ++j)
                    if (g[i][j] == 'N')
                        cand.push_back({i, j});
            for (int i = K; i < N; ++i)
                for (int j = i + 1; j < N; ++j)
                    if (g[i][j] == 'N')
                        cand.push_back({i, j});
            shuffle(cand.begin(), cand.end());
            int idx = 0;
            while (need > 0 && idx < (int)cand.size()) {
                addEdge(cand[idx].first, cand[idx].second);
                ++idx;
                --need;
            }
            // Optionally add a couple more intra edges for variety
            int extra = rnd.next(0, 2);
            while (extra > 0 && idx < (int)cand.size()) {
                addEdge(cand[idx].first, cand[idx].second);
                ++idx;
                --extra;
            }
            // Choose M in [N-1, min(E, N-1+3)] to keep size small but nontrivial
            int maxM = min(E, N - 1 + 3);
            if (maxM < N - 1) maxM = N - 1;
            M = rnd.next(N - 1, maxM);
            break;
        }

        // Type 4: Random connected graph with moderate density, valid (connected) case
        case 4: {
            int n = rnd.next(2, 15);
            initMatrix(n);
            // Spanning tree
            for (int i = 1; i < N; ++i) {
                int p = rnd.next(0, i - 1);
                addEdge(p, i);
            }
            // Add random extra edges with probability 1/2
            for (int i = 0; i < N; ++i) {
                for (int j = i + 1; j < N; ++j) {
                    if (g[i][j] == 'N') {
                        if (rnd.next(0, 1) == 1) {
                            addEdge(i, j);
                        }
                    }
                }
            }
            int minM = N - 1;
            int maxM = E;
            if (minM > maxM) minM = maxM; // safety
            if (rnd.next(0, 1) == 0) {
                int extra = min(3, maxM - minM);
                M = minM + rnd.next(0, extra);
            } else {
                M = rnd.next(minM, maxM);
            }
            break;
        }

        // Type 5: Complete graph (clique), various M
        case 5: {
            int n = rnd.next(2, 10);
            initMatrix(n);
            for (int i = 0; i < N; ++i)
                for (int j = i + 1; j < N; ++j)
                    addEdge(i, j);
            int Emax = E;
            vector<int> candM;
            candM.push_back(N - 1);
            candM.push_back(Emax);
            candM.push_back(max(N - 1, Emax / 2));
            // remove duplicates
            vector<int> uniq;
            for (int x : candM) {
                bool found = false;
                for (int y : uniq)
                    if (y == x) { found = true; break; }
                if (!found) uniq.push_back(x);
            }
            M = rnd.any(uniq);
            break;
        }
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; ++i)
        println(g[i]);

    return 0;
}
