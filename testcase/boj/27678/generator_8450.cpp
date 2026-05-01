#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

inline void addEdge(int u, int v, vector<pair<int,int>>& edges, vector<vector<bool>>& adj) {
    if (u == v) return;
    if (u > v) swap(u, v);
    if (!adj[u][v]) {
        adj[u][v] = adj[v][u] = true;
        edges.push_back({u, v});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small number of test cases, but slightly variable
    int t = rnd.next(3, 7);
    println(t);

    for (int cas = 0; cas < t; ++cas) {
        // Blank line before each test case
        printf("\n");

        int n;
        vector<pair<int,int>> edges;

        if (cas == 0) {
            // Case 0: very sparse graph (empty / single edge / path)
            n = rnd.next(2, 10);
            vector<vector<bool>> adj(n + 1, vector<bool>(n + 1, false));

            int variant = rnd.next(0, 2); // 0: empty, 1: single edge, 2: path
            if (variant == 0) {
                // empty graph: no edges
            } else if (variant == 1) {
                int u = rnd.next(1, n);
                int v = rnd.next(1, n);
                while (v == u) v = rnd.next(1, n);
                addEdge(u, v, edges, adj);
            } else {
                if (n == 2) {
                    addEdge(1, 2, edges, adj);
                } else {
                    for (int i = 1; i < n; ++i)
                        addEdge(i, i + 1, edges, adj); // path
                }
            }
        } else if (cas == 1) {
            // Case 1: dense small graph (clique or almost clique)
            n = rnd.next(3, 6);
            vector<vector<bool>> adj(n + 1, vector<bool>(n + 1, false));
            int maxEdges = n * (n - 1) / 2;

            if (rnd.next() < 0.5) {
                // full clique
                for (int i = 1; i <= n; ++i)
                    for (int j = i + 1; j <= n; ++j)
                        addEdge(i, j, edges, adj);
            } else {
                // random dense subset of edges
                vector<pair<int,int>> cand;
                for (int i = 1; i <= n; ++i)
                    for (int j = i + 1; j <= n; ++j)
                        cand.push_back({i, j});
                shuffle(cand.begin(), cand.end());
                int minM = maxEdges / 2;
                int maxM2 = maxEdges;
                int m = rnd.next(minM, maxM2);
                m = min(m, 15);
                for (int i = 0; i < m; ++i)
                    addEdge(cand[i].first, cand[i].second, edges, adj);
            }
        } else if (cas == 2) {
            // Case 2: two cliques with possible cross edges, captains in different cliques
            n = rnd.next(4, 7); // ensures internal edges <= 15
            vector<vector<bool>> adj(n + 1, vector<bool>(n + 1, false));
            vector<int> rest;
            for (int i = 3; i <= n; ++i) rest.push_back(i);
            shuffle(rest.begin(), rest.end());

            int sizeA = rnd.next(2, n - 2); // both groups at least size 2
            vector<int> A, B;
            A.push_back(1); // Adam
            B.push_back(2); // Betka

            int needA = sizeA - 1;
            for (int x : rest) {
                if (needA > 0) {
                    A.push_back(x);
                    --needA;
                } else {
                    B.push_back(x);
                }
            }

            // Clique in group A
            for (int i = 0; i < (int)A.size(); ++i)
                for (int j = i + 1; j < (int)A.size(); ++j)
                    addEdge(A[i], A[j], edges, adj);

            // Clique in group B
            for (int i = 0; i < (int)B.size(); ++i)
                for (int j = i + 1; j < (int)B.size(); ++j)
                    addEdge(B[i], B[j], edges, adj);

            int currentM = (int)edges.size();
            int remain = 15 - currentM;
            if (remain > 0) {
                vector<pair<int,int>> cross;
                for (int u : A)
                    for (int v : B)
                        cross.push_back({u, v});
                shuffle(cross.begin(), cross.end());
                int maxExtra = min(remain, (int)cross.size());
                int extra = (maxExtra > 0 ? rnd.next(0, maxExtra) : 0);
                for (int i = 0; i < extra; ++i)
                    addEdge(cross[i].first, cross[i].second, edges, adj);
            }
        } else if (cas == 3) {
            // Case 3: star-like graph with some extra edges
            n = rnd.next(3, 10);
            vector<vector<bool>> adj(n + 1, vector<bool>(n + 1, false));

            int centerChoice = rnd.next(0, 4);
            int center;
            if (centerChoice == 0) center = 1;
            else if (centerChoice == 1) center = 2;
            else center = rnd.next(1, n);

            // Connect center to others with reasonably high probability
            for (int i = 1; i <= n; ++i) {
                if (i == center) continue;
                if (rnd.next() < 0.6)
                    addEdge(center, i, edges, adj);
            }
            // Ensure at least one edge exists
            if (edges.empty()) {
                int v = (center == 1 ? 2 : 1);
                addEdge(center, v, edges, adj);
            }

            // Add some random extra edges among non-center nodes
            vector<pair<int,int>> cand;
            for (int i = 1; i <= n; ++i) {
                if (i == center) continue;
                for (int j = i + 1; j <= n; ++j) {
                    if (j == center) continue;
                    cand.push_back({i, j});
                }
            }
            shuffle(cand.begin(), cand.end());
            int remain = 15 - (int)edges.size();
            if (remain > 0) {
                int maxExtra = min(remain, (int)cand.size());
                int extra = (maxExtra > 0 ? rnd.next(0, maxExtra) : 0);
                for (int i = 0; i < extra; ++i)
                    addEdge(cand[i].first, cand[i].second, edges, adj);
            }
        } else {
            // Case 4+: mixed random (path/cycle or general random graph)
            n = rnd.next(2, 10);
            vector<vector<bool>> adj(n + 1, vector<bool>(n + 1, false));

            if (rnd.next(0, 1) == 0) {
                // Path or cycle
                for (int i = 1; i < n; ++i)
                    addEdge(i, i + 1, edges, adj);
                if (n >= 3 && (int)edges.size() < 15 && rnd.next(0, 1) == 1)
                    addEdge(1, n, edges, adj); // make a cycle
            } else {
                // General random graph with biased size
                vector<pair<int,int>> cand;
                for (int i = 1; i <= n; ++i)
                    for (int j = i + 1; j <= n; ++j)
                        cand.push_back({i, j});
                shuffle(cand.begin(), cand.end());
                int maxM = min((int)cand.size(), 15);
                int bias = rnd.next(-2, 2); // negative -> smaller, positive -> larger
                int m = rnd.wnext(maxM + 1, bias); // result in [0, maxM]
                for (int i = 0; i < m; ++i)
                    addEdge(cand[i].first, cand[i].second, edges, adj);
            }
        }

        int m = (int)edges.size();
        println(n, m);
        for (auto &e : edges)
            println(e.first, e.second);
    }

    return 0;
}
