#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(1, 5);

    int N, M, X, Y;
    vector<int> A;
    vector<pair<int,int>> edges;
    vector<int> B;

    auto addEdge = [&](int u, int v, set<pair<int,int>>& used) {
        if (u == v) return;
        if (u > v) swap(u, v);
        if (used.insert({u, v}).second) {
            edges.push_back({u, v});
        }
    };

    if (scenario == 1) {
        // Finite, connected graph
        N = rnd.next(2, 10);
        set<pair<int,int>> used;
        edges.clear();

        // Spanning tree
        for (int i = 2; i <= N; ++i) {
            int p = rnd.next(1, i - 1);
            addEdge(i, p, used);
        }

        // Some extra edges
        int maxExtra = min(5, N * (N - 1) / 2 - (N - 1));
        int extra = maxExtra > 0 ? rnd.next(0, maxExtra) : 0;
        for (int k = 0; k < extra; ++k) {
            int u = rnd.next(1, N);
            int v = rnd.next(1, N);
            if (u == v) { --k; continue; }
            addEdge(u, v, used);
        }

        M = (int)edges.size();

        // A_i
        A.assign(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            if (rnd.next(0, 2) == 0) A[i] = 0;
            else A[i] = rnd.next(1, 20);
        }

        // B: any subset, but Y>=1
        Y = rnd.next(1, N);
        vector<int> nodes(N);
        iota(nodes.begin(), nodes.end(), 1);
        shuffle(nodes.begin(), nodes.end());
        B.assign(nodes.begin(), nodes.begin() + Y);

        // X
        X = rnd.next(1, N);
    }
    else if (scenario == 2) {
        // Infinite: component without B and with positive A
        N = rnd.next(2, 10);
        vector<int> perm(N);
        iota(perm.begin(), perm.end(), 1);
        shuffle(perm.begin(), perm.end());

        int safeSize = rnd.next(1, N - 1);
        vector<int> safeNodes(perm.begin(), perm.begin() + safeSize);
        vector<int> unsafeNodes(perm.begin() + safeSize, perm.end());

        set<pair<int,int>> used;
        edges.clear();

        auto buildGroup = [&](const vector<int>& g) {
            if ((int)g.size() <= 1) return;
            int style = rnd.next(0, 2);
            if (style == 0) {
                // no edges
                return;
            } else if (style == 1) {
                // chain
                for (int i = 0; i + 1 < (int)g.size(); ++i)
                    addEdge(g[i], g[i + 1], used);
            } else {
                // random tree
                for (int i = 1; i < (int)g.size(); ++i) {
                    int p = rnd.next(0, i - 1);
                    addEdge(g[i], g[p], used);
                }
            }
        };

        buildGroup(safeNodes);
        buildGroup(unsafeNodes);

        M = (int)edges.size();

        // A_i
        A.assign(N + 1, 0);
        bool posSafe = false;
        for (int v : safeNodes) {
            A[v] = rnd.next(0, 20);
            if (A[v] > 0) posSafe = true;
        }
        if (!posSafe) {
            int v = rnd.any(safeNodes);
            A[v] = rnd.next(1, 20);
        }
        for (int v : unsafeNodes) {
            if (rnd.next(0, 1) == 0) A[v] = 0;
            else A[v] = rnd.next(1, 20);
        }

        // B only from unsafe group
        int unsafeCnt = (int)unsafeNodes.size();
        Y = rnd.next(1, unsafeCnt);
        shuffle(unsafeNodes.begin(), unsafeNodes.end());
        B.assign(unsafeNodes.begin(), unsafeNodes.begin() + Y);

        X = rnd.next(1, N);
    }
    else if (scenario == 3) {
        // All nodes protected at 0.5: Y = N
        N = rnd.next(1, 10);

        // Complete candidate edge list
        vector<pair<int,int>> allEdges;
        for (int i = 1; i <= N; ++i)
            for (int j = i + 1; j <= N; ++j)
                allEdges.push_back({i, j});
        shuffle(allEdges.begin(), allEdges.end());

        int maxEdges = min((int)allEdges.size(), 2 * N);
        M = rnd.next(0, maxEdges);
        edges.assign(allEdges.begin(), allEdges.begin() + M);

        A.assign(N + 1, 0);
        for (int i = 1; i <= N; ++i)
            A[i] = rnd.next(0, 20);

        Y = N;
        B.clear();
        for (int i = 1; i <= N; ++i) B.push_back(i);

        X = rnd.next(1, N);
    }
    else if (scenario == 4) {
        // Unreachable component but all its A_i = 0 -> finite answer
        N = rnd.next(2, 10);
        vector<int> perm(N);
        iota(perm.begin(), perm.end(), 1);
        shuffle(perm.begin(), perm.end());

        int safeSize = rnd.next(1, N - 1);
        vector<int> safeNodes(perm.begin(), perm.begin() + safeSize);
        vector<int> unsafeNodes(perm.begin() + safeSize, perm.end());

        set<pair<int,int>> used;
        edges.clear();

        auto buildGroup = [&](const vector<int>& g) {
            if ((int)g.size() <= 1) return;
            int style = rnd.next(0, 2);
            if (style == 0) {
                return;
            } else if (style == 1) {
                for (int i = 0; i + 1 < (int)g.size(); ++i)
                    addEdge(g[i], g[i + 1], used);
            } else {
                for (int i = 1; i < (int)g.size(); ++i) {
                    int p = rnd.next(0, i - 1);
                    addEdge(g[i], g[p], used);
                }
            }
        };

        buildGroup(safeNodes);
        buildGroup(unsafeNodes);

        M = (int)edges.size();

        A.assign(N + 1, 0);
        // safe group all zero
        for (int v : safeNodes) A[v] = 0;
        // unsafe group, ensure at least one positive
        bool posUnsafe = false;
        for (int v : unsafeNodes) {
            A[v] = rnd.next(0, 20);
            if (A[v] > 0) posUnsafe = true;
        }
        if (!posUnsafe) {
            int v = rnd.any(unsafeNodes);
            A[v] = rnd.next(1, 20);
        }

        int unsafeCnt = (int)unsafeNodes.size();
        Y = rnd.next(1, unsafeCnt);
        shuffle(unsafeNodes.begin(), unsafeNodes.end());
        B.assign(unsafeNodes.begin(), unsafeNodes.begin() + Y);

        X = rnd.next(1, N);
    }
    else { // scenario == 5
        // Path graph with 1 or 2 B's
        N = rnd.next(2, 12);
        set<pair<int,int>> used;
        edges.clear();

        for (int i = 1; i < N; ++i)
            addEdge(i, i + 1, used);
        M = (int)edges.size();

        A.assign(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            A[i] = rnd.next(0, 20);
        }

        int pattern = rnd.next(1, 3);
        B.clear();
        if (pattern == 1) {
            Y = 1;
            B.push_back(1);
        } else if (pattern == 2) {
            Y = 1;
            B.push_back(N);
        } else {
            Y = (N == 2 ? 1 : 2);
            if (Y == 1) B.push_back(1);
            else { B.push_back(1); B.push_back(N); }
        }

        X = rnd.next(1, N);
    }

    // Output
    println(N, M, X, Y);
    vector<int> Aout(N);
    for (int i = 1; i <= N; ++i) Aout[i - 1] = A[i];
    println(Aout);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    println(B);

    return 0;
}
