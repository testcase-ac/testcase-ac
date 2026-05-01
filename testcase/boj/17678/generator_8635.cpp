#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

void dfs_order(int v, int p, const vector<vector<int>>& g, vector<int>& order) {
    order.push_back(v);
    for (int to : g[v]) if (to != p) dfs_order(to, v, g, order);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N = 0, K = 0;
    vector<pair<int,int>> edges;
    vector<int> S;

    int mode = rnd.next(0, 7); // 8 modes: 0..7

    if (mode == 0) {
        // Single state, random tree
        N = rnd.next(2, 20);
        K = 1;
        edges.clear();
        for (int i = 2; i <= N; ++i) {
            int p = rnd.next(1, i - 1);
            edges.push_back({p, i});
        }
        S.assign(N + 1, 1);
    } else if (mode == 1) {
        // Path, each city its own state
        N = rnd.next(2, 20);
        K = N;
        edges.clear();
        for (int i = 2; i <= N; ++i) {
            edges.push_back({i - 1, i});
        }
        S.assign(N + 1, 0);
        for (int i = 1; i <= N; ++i) S[i] = i;
    } else if (mode == 2) {
        // Star, center big state, several small states
        N = rnd.next(3, 20);
        int Kmax = min(N - 1, 6);
        K = rnd.next(2, Kmax);
        edges.clear();
        int center = 1;
        for (int i = 1; i <= N; ++i) {
            if (i == center) continue;
            edges.push_back({center, i});
        }
        S.assign(N + 1, 1);
        // Ensure each state 1..K used at least once
        for (int i = 2; i <= K; ++i) {
            S[i] = i;
        }
        for (int i = K + 1; i <= N; ++i) {
            S[i] = rnd.next(1, K);
        }
    } else if (mode == 3) {
        // Random tree, moderate K, generic assignment
        N = rnd.next(2, 20);
        int Kmax = min(N, 6);
        K = rnd.next(1, Kmax);
        edges.clear();
        for (int i = 2; i <= N; ++i) {
            int p = rnd.next(1, i - 1);
            edges.push_back({p, i});
        }
        S.assign(N + 1, 0);
        vector<int> idx;
        for (int i = 1; i <= N; ++i) idx.push_back(i);
        shuffle(idx.begin(), idx.end());
        // Ensure each state used once
        for (int s = 1; s <= K; ++s) {
            S[idx[s - 1]] = s;
        }
        // Remaining cities: random states
        for (int t = K; t < N; ++t) {
            S[idx[t]] = rnd.next(1, K);
        }
    } else if (mode == 4) {
        // Path, alternating two states
        N = rnd.next(2, 20);
        K = 2;
        edges.clear();
        for (int i = 2; i <= N; ++i) {
            edges.push_back({i - 1, i});
        }
        S.assign(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            S[i] = (i % 2 ? 1 : 2);
        }
    } else if (mode == 5) {
        // Binary-like tree, DFS-contiguous state blocks
        N = rnd.next(2, 20);
        K = rnd.next(1, min(6, N));
        edges.clear();
        for (int i = 2; i <= N; ++i) {
            int p = i / 2;
            edges.push_back({p, i});
        }
        vector<vector<int>> g(N + 1);
        for (auto &e : edges) {
            g[e.first].push_back(e.second);
            g[e.second].push_back(e.first);
        }
        vector<int> order;
        dfs_order(1, 0, g, order);
        S.assign(N + 1, 0);
        if (K == 1) {
            for (int v : order) S[v] = 1;
        } else {
            // Choose K-1 distinct cut positions in [1, N-1]
            vector<int> pos;
            for (int i = 1; i <= N - 1; ++i) pos.push_back(i);
            shuffle(pos.begin(), pos.end());
            pos.resize(K - 1);
            sort(pos.begin(), pos.end());
            int cur = 0;
            for (int s = 1; s <= K; ++s) {
                int endPos = (s == K ? N : pos[s - 1]);
                while (cur < endPos) {
                    int v = order[cur];
                    S[v] = s;
                    ++cur;
                }
            }
        }
    } else if (mode == 6) {
        // Random tree, K=N, states are a permutation
        N = rnd.next(2, 20);
        K = N;
        edges.clear();
        for (int i = 2; i <= N; ++i) {
            int p = rnd.next(1, i - 1);
            edges.push_back({p, i});
        }
        vector<int> permStates;
        for (int i = 1; i <= N; ++i) permStates.push_back(i);
        shuffle(permStates.begin(), permStates.end());
        S.assign(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            S[i] = permStates[i - 1];
        }
    } else {
        // mode == 7: Random tree, states clustered by depth
        N = rnd.next(2, 20);
        edges.clear();
        for (int i = 2; i <= N; ++i) {
            int p = rnd.next(1, i - 1);
            edges.push_back({p, i});
        }
        vector<vector<int>> g(N + 1);
        for (auto &e : edges) {
            g[e.first].push_back(e.second);
            g[e.second].push_back(e.first);
        }
        vector<int> depth(N + 1, -1);
        queue<int> q;
        depth[1] = 0;
        q.push(1);
        int maxDepth = 0;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            maxDepth = max(maxDepth, depth[v]);
            for (int to : g[v]) if (depth[to] == -1) {
                depth[to] = depth[v] + 1;
                q.push(to);
            }
        }
        // At least depth 0 and 1 should exist since N >= 2
        K = rnd.next(2, min(4, maxDepth + 1));
        S.assign(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            int d = depth[i];
            int st = d + 1;
            if (st > K) st = K;
            S[i] = st;
        }
    }

    // Optionally permute city labels
    if (rnd.next(0, 1) == 1) {
        vector<int> perm(N + 1);
        for (int i = 1; i <= N; ++i) perm[i] = i;
        shuffle(perm.begin() + 1, perm.end());
        vector<pair<int,int>> newEdges;
        newEdges.reserve(edges.size());
        for (auto &e : edges) {
            int u = perm[e.first];
            int v = perm[e.second];
            newEdges.push_back({u, v});
        }
        vector<int> newS(N + 1);
        for (int i = 1; i <= N; ++i) {
            newS[perm[i]] = S[i];
        }
        edges.swap(newEdges);
        S.swap(newS);
    }

    // Optionally shuffle edges
    if (rnd.next(0, 1) == 1) {
        shuffle(edges.begin(), edges.end());
    }

    // Output
    println(N, K);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    for (int i = 1; i <= N; ++i) {
        println(S[i]);
    }

    return 0;
}
